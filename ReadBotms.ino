/*
  -----  READ BOTTOMS and setS global variables for the ACTIONS routine
*/
//     ------   States ------
bool btmStartState =		  0;        // Strater On / Off
bool btmHornState =			  0;         // horn
bool wheelBtm1State =		  0;       // wheel bottom # 1 clockwise from 12 oclock
bool wheelBtm2State =		  0;       // whee2 bottom # 2 clockwise from 12 oclock
bool wheelBtm3State =		  0;       // whee3 bottom # 3 clockwise from 12 oclock
bool btm_lState =			  0;           // Left turn signal
bool btm_rState =			  0;           // Right turn signal
bool btm_Fw_state =			  0;         // Forward drive
bool btm_Rev_state =		  0;        // Reverse drive
bool drivePedalState =		  0;      // Foot Pedal for drive FRW. & REV.

bool btmAirPumpState =		  0;			// ---------- 8-2019 ---------
bool btmWaterPumpState =	  0;
bool battaryDeadState =	      0;
bool btmFunMotorState =		  0;
bool btmLightsState =		  0;
bool btmRaspPiState =		  0;
bool btmNeoPixleMotorState =  0;

//    -------- Last xx state ------
bool lastbtmStartState =      0;
bool lastbtmHornState =       0;
bool lastWheelBtm1State =	  0;
bool lastWheelBtm2State =     0;
bool lastWheelBtm3State =	  0;
bool lastbtm_lState =		  0;
bool lastbtm_rState =		  0;
bool lastbtm_Fw_state =	  	  0;
bool lastbtm_Rev_state = 	  0;
bool lastDrivePedalState=	  0;
bool lastBtmLightsState =	  0;
bool lastBtmRaspPiState =	  0;

bool lastAirPumpState =       0;			// 8-2019 added push bottoms paralel function with motor commands
bool lastWaterPumpState =     0;
bool lastBattaryDeadState =   0;
bool lastFunMotorState =      0;
bool lastNeoPixleMotorState = 0;


// ---  INI routine called from within SETUP routine ----
void readBottomsIni()
{
	pinMode(btmStartEngPin,	 INPUT_PULLUP);    // define all bottoms with pullup resistor      
	pinMode(btmLightsPin,    INPUT_PULLUP);
	pinMode(btmHornPin,		 INPUT_PULLUP);
	pinMode(wheelBtm1Pin,	 INPUT_PULLUP);
	pinMode(wheelBtm2Pin,	 INPUT_PULLUP);
	pinMode(wheelBtm3Pin,	 INPUT_PULLUP);
	pinMode(sw_L_turnPin,	 INPUT_PULLUP);
	pinMode(sw_R_turnPin,	 INPUT_PULLUP);
	pinMode(gearFwPin,		 INPUT_PULLUP);
	pinMode(gearRevPin,		 INPUT_PULLUP);
	pinMode(drivePedalPin,	 INPUT_PULLUP);
	pinMode(btmRaspbryPin,   INPUT_PULLUP);
	
	pinMode(btm_AirPin ,	 INPUT_PULLUP);    // motor panel  all bottoms with pullup resistor      
	pinMode(btm_WaterPin ,	 INPUT_PULLUP);
	pinMode(battaryDeadPin,  INPUT_PULLUP);
	pinMode(btm_FanPin ,     INPUT_PULLUP);
	pinMode(btm_neoMotorPin, INPUT_PULLUP);

//*****************************************
}// --- END of readBottoms INI rotine
//*****************************************



//*****************************************
// ---- Read Bottoms called from within Main routine ( in the loop ) --------------------
//*****************************************

void readBottoms()
{
		noSwitchPushed = 1;  // 1= no switchs pushed, 0 = one or more pushed lately
		// --------------------------------------------- btm  START ENGINE - MOTOR ON-------------------------
		btmStartState = digitalRead(btmStartEngPin);
		if (btmStartState != lastbtmStartState)
		{
			if (btmStartState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ start ] ");
				delay(15);
				motorOn = !motorOn;
				neopixleIntirior.Color1 = neopixleIntirior.Color(0, 100, 0);
				neopixleMotor.Color1 = neopixleMotor.Color(0, 100, 0);
				nextStarter(motorOn);				// mp3 play starter sound random 
				noSwitchPushed = 0;
			}
		}
		lastbtmStartState = btmStartState;
		// ----------------------------  ------------------ btm HORN - HORN PUSHED-------------------------
		btmHornState = digitalRead(btmHornPin);
		if (btmHornState != lastbtmHornState)
		{
			if (btmHornState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ HORN  ] ");
				delay(20);
				hornBtmNumber = random(1, 5);
			}
		}
		lastbtmHornState = btmHornState;

		// -------------------------------------------------- btm  RIGHT SIGNAL- -turnROn------------------------

		btm_rState = digitalRead(sw_R_turnPin);
		if (btm_rState != lastbtm_rState)
		{
			if (btm_rState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ Right Turn ] ");
				delay(15);
				turnROn = 1;
				nextCommand(5);             // play sounf right in the /cmnd/x.mp3 subdirectory in sd card  - prerecorded
				neopixleIntirior.Color1 = neopixleIntirior.Color(20, 200, 0);
				noSwitchPushed = 0;
			}
			else turnROn = 0;
			neopixleIntirior.Color1 = neopixleIntirior.Color(80, 100, 0);
		}
		lastbtm_rState = btm_rState;

		// -------------------------------------------------- btm  LEFT SIGNAL-turnLOn-------------------------

		btm_lState = digitalRead(sw_L_turnPin);
		if (btm_lState != lastbtm_lState)
		{
			if (btm_lState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ Left Turn ] ");
				delay(15);
				turnLOn = 1;       // toggel switch !!!
				nextCommand(4);		// play sound left
				neopixleIntirior.Color1 = neopixleIntirior.Color(200, 30, 0);
				noSwitchPushed = 0;
			}
			else turnLOn = 0;
			neopixleIntirior.Color1 = neopixleIntirior.Color(200, 120, 0);
		}
		lastbtm_lState = btm_lState;

		// ------------------------------------------- btm   REVERSE -- reverseOn------------------------
		btm_Rev_state = digitalRead(gearRevPin);
		if (btm_Rev_state != lastbtm_Rev_state)
		{
			if (btm_Rev_state == LOW)
			{	// each time pushbottom pressed this is what will happand
				delay(15);
				Serial.println("[ REVERSE ]");
				reverseOn = 1;			    // toggel switch !!!
				Serial.print("[ REVERSE ]");
				nextCommand(3);				// play sound reverse 
				if (musicPlayer.stopped())  nextReverse(4);
				neopixleIntirior.Color1 = neopixleIntirior.Color(200, 0, 0);
			}
			else	reverseOn = 0;
			neopixleIntirior.Color1 = neopixleIntirior.Color( 200,0, 0);
		}
		lastbtm_Rev_state = btm_Rev_state;

		// ------------------------------------------- btm  FORWARD -- forwardOn-----------------------
		btm_Fw_state = digitalRead(gearFwPin);
		if (btm_Fw_state != lastbtm_Fw_state)
		{
			if (btm_Fw_state == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println("[ FORWARD ]");
				delay(15);
				forwardOn = 1;          
				nextCommand(2);		// play sound forward 
				neopixleIntirior.Color1 = neopixleIntirior.Color(0, 200, 0);
			}
			else 
			{
				forwardOn = 0;
				neopixleIntirior.Color1 = neopixleIntirior.Color(0, 200, 0);
				//nextCommand(1);            // Nutral massege  comnd/1.mp3
			}
		}
		lastbtm_Fw_state = btm_Fw_state;

		// ------------------------WHEEL BOTTOM # 1  ----wheelBottom1Pushed----------------------

		wheelBtm1State = digitalRead(wheelBtm1Pin);
		if (wheelBtm1State != lastWheelBtm1State)
		{
			if (wheelBtm1State == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ WHEEL SW  1  ] ");
				delay(15);
				wheelBottom1Pushed = random(1, 11);         // random switch (x, y) y # of files in sd card subdirectory
			}
		}
		lastWheelBtm1State = wheelBtm1State;

		// -------------------------------------------------- WHEEL BOTTOM # 2  ----- wheelBottom2Pushed ---------------------

		wheelBtm2State = digitalRead(wheelBtm2Pin);
		if (wheelBtm2State != lastWheelBtm2State)
		{
			if (wheelBtm2State == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ WHEEL SW  2  ] ");
				delay(15);
				wheelBottom2Pushed = random(2, 12);       // random switch (x, y) y # of files in sd card subdirectory
			}
		}
		lastWheelBtm2State = wheelBtm2State;

		// -------------------------------------------------- WHEEL BOTTOM # 3  ---- wheelBottom3Pushed ----------------------

		wheelBtm3State = digitalRead(wheelBtm3Pin);
		if (wheelBtm3State != lastWheelBtm3State)
		{
			if (wheelBtm3State == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ WHEEL SW  3  ] ");
				delay(15);
				wheelBottom3Pushed = random(3, 13);       // random switch (x, y) y # of files in sd card subdirectory
			}
		}
		lastWheelBtm3State = wheelBtm3State;

		// -------------------------------------------------- Drive Pedal  -- drivePedalOn -----------------------

		drivePedalState = digitalRead(drivePedalPin);
		if (drivePedalState != lastDrivePedalState)
		{
			if (drivePedalState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println(" [ Drive Pedal  ] ");
				delay(15);
				drivePedalOn = 1;                 //  S A F T Y   switch 
				neopixleIntirior.Color1 = neopixleIntirior.Color(40, 255, 100);

			}
			else drivePedalOn = 0;              // only MOMENTARY witch  on when pushed OFF when not pushed
		}
		lastDrivePedalState = drivePedalState;

		//**************************    8-2019    **********************************
		// ------------------------------------------- btm  Air Pump  -- airPumpOn  ----------------------------

		btmAirPumpState = digitalRead(btm_AirPin);
		if (btmAirPumpState != lastAirPumpState)
		{
			if (btmAirPumpState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println("[ Air Pump ]");
				delay(15);
				airPumpNumber += 1;          // 0-off,  1-on,  2-slow,   3-fast 
				Serial.println(airPumpNumber);
				if (airPumpNumber >=2)
				{
					airPumpNumber = -1;
					nextCommand(6);
				}
				else nextCommand(10);
			}
		}
		lastAirPumpState = btmAirPumpState;


		// ------------------------------------------- btm  Water Pump  -- waterPumpOn  ----------------------------

		btmWaterPumpState = digitalRead(btm_WaterPin);
		if (btmWaterPumpState != lastWaterPumpState)
		{
			if (btmWaterPumpState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println("[ Water Pump ]");
				delay(15);
				waterPumpNumber +=1 ;          // 0-off,  1-on,  2-slow,   3-fast 
				Serial.println(waterPumpNumber);
				if (waterPumpNumber >= 2)
				{
					waterPumpNumber = -1;
					nextCommand(6);
				}
				else nextCommand(11);
			}
		}
		lastWaterPumpState = btmWaterPumpState;

		// ------------------------------------------- Battary Dead cut out relay  ----------------------------

		battaryDeadState = digitalRead(battaryDeadPin);
		if (battaryDeadState != lastBattaryDeadState)
		{
			if (battaryDeadState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println("[ Battary for motors finished ]");
				delay(15);
				battaryDeadOn = 1;      // no battry !! for drive motors unless push engine start also while driving !!!
				//nextCommand(99);    	//sound worning /cmnd/99.mp3 subdirectory in sd card
			}
			else battaryDeadOn = 0;			// battry good normal functions
		}
		lastBattaryDeadState = battaryDeadState;

		// ------------------------------------------- btm  Fan Radiator on motor   -- fanMotorOn  ----------------------------
		
		btmFunMotorState = digitalRead(btm_FanPin);
		if (btmFunMotorState != lastFunMotorState)
		{
			if (btmFunMotorState == LOW)
			{	// each time pushbottom pressed this is what will happand
				Serial.println("[  Fan Radiator  ]");
				delay(15);
				fanMotorNumber += 1;          // 0-off,  1-on,  2-slow,   3-fast 
				Serial.println(fanMotorNumber);
				
				if (fanMotorNumber >= 2)
				{
					fanMotorNumber = -1;
					nextCommand(6);
				}
				else nextCommand(12);
			}
		}
		lastFunMotorState = btmFunMotorState;



		// ------------------------------------------- btm  NeoPixles on motor   -- neo Motor number 1-3 rgb 4 random  ----------------------------



		btmNeoPixleMotorState = digitalRead(btm_neoMotorPin);
		if (btmNeoPixleMotorState != lastNeoPixleMotorState)
		{
			if (btmNeoPixleMotorState == LOW)
			{	// each time pushbottom pressed this is what will happand
		
				delay(15);
				Serial.print(" [  NeoPixles in motor mode = ");
				Serial.print ( neoMotorNumber);
				Serial.println(" ] ");
				neoMotorNumber += 1; 

				if (neoMotorNumber >= 4)		// switch from 0-4 agian 
				{
					neoMotorNumber = 0;
					nextCommand(6);				// off massage
				}
				else nextCommand(13);			// led in motor massage
			}
		}
		lastNeoPixleMotorState = btmNeoPixleMotorState;


		// --------------------------------- btm  L I G H T S on off -- lightsOn lightsLamp ------------------------

		btmLightsState = digitalRead(btmLightsPin);
		if (btmLightsState != lastBtmLightsState)
		{
			if (btmLightsState == LOW)
			{
				neopixleIntirior.Color1 = neopixleIntirior.Color(0, 0,100);  // blue intirior
				Serial.println(lightsOn);
				delay(15);
				lightsOn =!lightsOn;						// on off switch
				if ( lightsOn == 1) 
				{
					nextCommand(7); 							// mp3 play lights on  massage				
				}
				else
				{
					nextCommand(8);							// mp3 play lights off massage
	//				digitalWrite(redLightDrivePin, 0);		// turn Red lights on
				}
			}
		}
		lastBtmLightsState = btmLightsState;

		// ------------------------------------------- Battary Dead cut out relay  ----------------------------

		battaryDeadState = digitalRead(battaryDeadPin);
//		Serial.println(lastBattaryDeadState);
		if (battaryDeadState != lastBattaryDeadState)
		{
			if (battaryDeadState == LOW)
			{
				Serial.println("[ motors Battary-finished ! ]");
				delay(15);
				battaryDeadOn = 1;
			}
			else battaryDeadOn =0;
		}
		lastBattaryDeadState = battaryDeadState;

		// ----------------------------------- Switch  RasberryPi screen right side ------------------------

		btmRaspPiState = digitalRead(btmRaspbryPin);
		if (btmRaspPiState != lastBtmRaspPiState)
		{
			if (btmRaspPiState == LOW)
			{
				delay(15);
				//swRasbPiOn = 1;
				Serial.println(swRasbPiOn);
				swRasbPiNumber += 1;
				if (swRasbPiNumber > 4) swRasbPiNumber = 0;
			}
			else swRasbPiOn = 0;
		}
		lastBtmRaspPiState = btmRaspPiState;

		//*****************************************************
}// ----END read bottoms routine   ---------------------  
//*****************************************************


