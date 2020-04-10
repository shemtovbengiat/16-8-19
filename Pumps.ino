/*
 ------  new Pumps Routine --   No shiled ----- 
 --- There are 3 motors - air pump, water pump and radiator fan.
 --- All 3 motors connected dirct to relay +12 volt on 8 relay board, gnd common to all
 --- There are 3 more bottoms that toggel each motor on/off independentally. each may be repeated 3 times for 3 speeds.
 --- There is also one bottom to switch relay (out of 8) designeated to front lingts (was direct from battary!) 
 */

// --- Initilatziotion Routine from SETUP 
void pumpsIni()
{
	Serial.println("Pumps initiated");
//	pinMode(waterPumpRelayPin, INPUT_PULLUP);
//	pinMode(airPumpRelayPin,   INPUT_PULLUP);
//	pinMode(fanMotorRelayPin,  INPUT_PULLUP);
	
	pinMode(waterPumpRelayPin,   OUTPUT);            
	pinMode(airPumpRelayPin,     OUTPUT);
	pinMode(fanMotorRelayPin,    OUTPUT);
}//----END of PUMP Initilatziotion Routine

//   ********************** Water, Air  & Fan motor routine, *********    speed --  0-off, 1 -on, 2-slow 3-fast 

int waterPumpState = 0;                         // state used to set the pumps, motors
int airPumpState   = 0;
int fanMotorState  = 0;

unsigned long previousWaterStateMs = 0;         // privious time pumps  where updated
unsigned long previousAirStateMs   = 0;
unsigned long previousFanStateMS   = 0;

unsigned long currentStrtWaterMs   = 0;         // current time pumps where updated
unsigned long currentStateAirMs    = 0;
unsigned long currentStateFanMS    = 0;

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
void fanMotor   (int fanSpeed){                 //called from actions rutine  0-Off, 1 -On, 2-Slow,  3-Fast.
	if (fanSpeed == 0){
		digitalWrite(fanMotorRelayPin, 1);		//0= no motor so we  set to  1 instead 
		return;
	}
	else if (fanSpeed == 1) {
		digitalWrite(fanMotorRelayPin, 0);		// 1 = relay on so 0 
		return;
	}
	else if (fanSpeed == 2) fanRate = timingFanSlow;  // set at main routine 
//	else if (fanSpeed == 3) fanRate = timingFanFast;

	unsigned long currentStateFanMS = millis();
	
	if (currentStateFanMS - previousFanStateMS >= fanRate)
		{
			previousFanStateMS = currentStateFanMS;

			if (fanMotorState == HIGH)
			{
				fanMotorState = LOW;
			}
			else {
				fanMotorState = HIGH;
			}
			digitalWrite(fanMotorRelayPin, fanMotorState);
		}

}//  ----  end of Fan Motor  routine ---

//  ******************************  Water Motor routine  **************
void waterMotor(int waterSpeed) {
	if (waterSpeed == 0) {						// called from actions rutine     0-Off, 1 -On, 2-Slow,  3-Fast.
		digitalWrite(waterPumpRelayPin, 1);
		return;
	}
	else if (waterSpeed == 1) {
		digitalWrite(waterPumpRelayPin, 0);
		return;
	}
	else if (waterSpeed == 2) waterRate = timingWaterSlow;  // set at main routine 
//	else if (waterSpeed == 3) waterRate = timingWaterFast;

	unsigned long currentStrtWaterMs = millis();

	if (currentStrtWaterMs - previousWaterStateMs >= waterRate)
	{
		previousWaterStateMs = currentStrtWaterMs;

		if (waterPumpState == HIGH)
		{
			waterPumpState = LOW;
		}
		else {
			waterPumpState = HIGH;
		}
		digitalWrite(waterPumpRelayPin, waterPumpState);
	}
}//  ----  end of Water Motor  routine ---

//  *************************   Air Motor routine  **********************
void airMotor(int airSpeed) {
	if (airSpeed == 0) {							//   called from actions rutine     0-Off, 1 -On,  2-Slow,  3-Fast.
		digitalWrite(airPumpRelayPin, 1);
		return;
	}
	else if (airSpeed == 1) {
		digitalWrite(airPumpRelayPin, 0);
		return;
	}
	else if (airSpeed == 2) airRate = timingAirSlow;  // set at main routine 
//	else if (airSpeed == 3) airRate = timingAirFast;

	unsigned long currentStateAirMs = millis();

	if (currentStateAirMs - previousAirStateMs >= airRate)
	{
		previousAirStateMs = currentStateAirMs;

		if (airPumpState == HIGH)
		{
			airPumpState = LOW;
		}
		else {
			airPumpState = HIGH;
		}
		digitalWrite(airPumpRelayPin, airPumpState);
	}
}//  ----  end of Air Motor  routine ---

//////////////////////////////////////////////////////////////////////////////////////////

  /*
there are 3 motors -air & water pumps and 1 fan motor
all connected to Adafruit Motor Shield v2 ---->	http://www.adafruit.com/products/1438
shild uses with th I2C protocol


// *** pumps ***

Adafruit_MotorShield Pumps = Adafruit_MotorShield(); // Construct the motor shield object PUMPS with the default I2C address

Adafruit_DCMotor *fanRadiator	= Pumps.getMotor(2);
Adafruit_DCMotor *waterPump		= Pumps.getMotor(3);     // Select which 'port' M2, M3 or M4. 
Adafruit_DCMotor *airPump		= Pumps.getMotor(4);




// --- Initilatziotion Routine from SETUP 
void pumpsIni()
{
	Serial.println("Pumps and fan initiated");

	PUMPS.begin();            // create with the default frequency 1.6KHz

	waterPump->run(RELEASE);  //reales == STOP   at STARTtttttt
	airPump->run(RELEASE);    //reales == STOP   at STARTtttttt
	fanMotor->run(RELEASE);   //reales == STOP   at STARTtttttt
}//----END of PUMP Initilatziotion Routine


// --- PUMPS  Water + air  & fan motor routine
void pumps(bool pumpsOn, int pumpsFast)
{
	// bool _valvesOn = valvesOn;                     // for internal use                   
	// bool _valvesFast = valvesFast;

	if (pumpsOn == 1 && pumpsFast == 1)
	{
		waterPump->run(FORWARD);
		waterPump->setSpeed(200);
		airPump->run(FORWARD);
		airPump->setSpeed(250);
		fanMotor->run(FORWARD);
		fanMotor->setSpeed(250);
	}
	if (pumpsOn == 1 && pumpsFast == 0)  // motor on slow valves 
	{
		waterPump->run(FORWARD);
		waterPump->setSpeed(80);
		airPump->run(FORWARD);
		airPump->setSpeed(80);
		fanMotor->run(FORWARD);
		fanMotor->setSpeed(80);
	}
	if (pumpsOn == 0)
	{
		waterPump->run(RELEASE);  // stop motors RELEASE = stop 
		airPump->run(RELEASE);
		fanMotor->run(RELEASE);
	}
}// --- E N D of pumps routine
*/





