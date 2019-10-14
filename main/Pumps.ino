/*
 ------  new Pumps Routine --   No shiled ----- 
 --- There are 3 motors - air pump, water pump and radiator fan.
 --- All 3 motors connected dirct to relay 12 volt
 --- There are 3 more bottoms that toggel each motor on/off independentally while turning engine turn 3 on/off automatically. 
 --- There is also one bottom to switch relay (out of 8) designeated to front lingts (was direct from battary!) 
 */

// --- Initilatziotion Routine from SETUP 
void pumpsIni()
{
	Serial.println("Pumps initiated");
	pinMode(waterPumpRelayPin,   OUTPUT);            
	pinMode(airPumpRelayPin,     OUTPUT);
	pinMode(fanMotorRelayPin,    OUTPUT);

}//----END of PUMP Initilatziotion Routine

//   ********************** Water, Air  & Fan motor routine, *********    speed --  0-off, 1 -on, 2-slow 3-fast 

int waterPumpState = 0;                         // state used to set the pumps, motors
int airPumpState = 0;
int fanMotorState = 0;

unsigned long previousWaterStateMs = 0;     // privious time pumps  where updated
unsigned long previousAirStateMs = 0;
unsigned long previousFanStateMS = 0;

unsigned long currentStrtWaterMs = 0;           // current time pumps where updated
unsigned long currentStateAirMs = 0;
unsigned long currentStateFanMS = 0;

long waterRate;									// for internal use       
long airRate;									// for internal use       
long fanRate;									// for internal use       

long timingWaterFast = waterTimerFast;          // set at main routine - 10 fast 200 slow / ms
long timingWaterSlow = waterTimerSlow;          // set at main routine - 10 fast 200 slow / ms

long timingAirFast   = airTimerFast;
long timingAirSlow   = airTimerSlow;

long timingFanFast   = fanTimerFast;          // set at main routine - 10 fast 200 slow / ms
long timingFanSlow   = fanTimerSlow;
//  ----  end of declering variables ----------

//  ***************************   Fan Motor routine  ***********************
void fanMotor   (int fanSpeed){                //  0-Off, 1 -On, 2-Slow,  3-Fast.
	if (fanSpeed == 0){
		digitalWrite(fanMotorRelayPin, 0);
		return;
	}
	else if (fanSpeed == 1) {
		digitalWrite(fanMotorRelayPin, 1);
		return;
	}
	else if (fanSpeed == 2) fanRate = timingFanSlow;  // set at main routine 
	else if (fanSpeed == 3) fanRate = timingFanFast;

	unsigned long currentStateFanMS = millis();
	
	if (currentStateFanMS - previousFanStateMS >= fanRate)
		{
			previousFanStateMS = currentStateFanMS;

			if (fanMotorState == LOW)
			{
				fanMotorState = HIGH;
			}
			else {
				fanMotorState = LOW;
			}
			digitalWrite(fanMotorRelayPin, fanMotorState);
		}

}//  ----  end of Fan Motor  routine ---

//  ******************************  Water Motor routine  **************
void waterMotor(int waterSpeed) {
	if (waterSpeed == 0) {						//  0-Off, 1 -On, 2-Slow,  3-Fast.
		digitalWrite(waterPumpRelayPin, 0);
		return;
	}
	else if (waterSpeed == 1) {
		digitalWrite(waterPumpRelayPin, 1);
		return;
	}
	else if (waterSpeed == 2) waterRate = timingWaterSlow;  // set at main routine 
	else if (waterSpeed == 3) waterRate = timingWaterFast;

	unsigned long currentStrtWaterMs = millis();

	if (currentStrtWaterMs - previousWaterStateMs >= waterRate)
	{
		previousWaterStateMs = currentStrtWaterMs;

		if (waterPumpState == LOW)
		{
			waterPumpState = HIGH;
		}
		else {
			waterPumpState = LOW;
		}
		digitalWrite(waterPumpRelayPin, waterPumpState);
	}
}//  ----  end of Water Motor  routine ---

//  *************************   Air Motor routine  **********************
void airMotor(int airSpeed) {
	if (airSpeed == 0) {							//  0-Off, 1 -On,  2-Slow,  3-Fast.
		digitalWrite(airPumpRelayPin, 0);
		return;
	}
	else if (airSpeed == 1) {
		digitalWrite(airPumpRelayPin, 1);
		return;
	}
	else if (airSpeed == 2) airRate = timingAirSlow;  // set at main routine 
	else if (airSpeed == 3) airRate = timingAirFast;

	unsigned long currentStateAirMs = millis();

	if (currentStateAirMs - previousAirStateMs >= airRate)
	{
		previousAirStateMs = currentStateAirMs;

		if (airPumpState == LOW)
		{
			airPumpState = HIGH;
		}
		else {
			airPumpState = LOW;
		}
		digitalWrite(airPumpRelayPin, airPumpState);
	}
}//  ----  end of Air Motor  routine ---