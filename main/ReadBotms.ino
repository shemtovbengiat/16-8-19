

/*

  -----  reads all the bottoms and set global variables for the Actions routine
*/

bool btmStartState = 0;        // Strater On / Off
bool btmHornState = 0;         // horn
bool wheelBtm1State = 0;       // wheel bottom # 1 clockwise from 12 oclock
bool wheelBtm2State = 0;       // whee2 bottom # 2 clockwise from 12 oclock
bool wheelBtm3State = 0;       // whee3 bottom # 3 clockwise from 12 oclock
bool btm_lState = 0;           // Left turn signal
bool btm_rState = 0;           // Right turn signal
bool btm_Fw_state = 0;         // Forward drive
bool btm_Rev_state = 0;        // Reverse drive
bool drivePedalState = 0;      // Foot Pedal for drive FRW. & REV.

bool airPumpState = 0;
bool waterPumpState = 0;
bool valvesState = 0;
bool fanMotorState = 0;
bool neoPixleMotorState = 0;

bool lastbtmStartState = 0;
bool lastbtmHornState = 0;
bool lastWheelBtm1State = 0;
bool lastWheelBtm2State = 0;
bool lastWheelBtm3State = 0;
bool lastbtm_lState = 0;
bool lastbtm_rState = 0;
bool lastbtm_Fw_state = 0;
bool lastbtm_Rev_state = 0;
bool lastDrivePedalState = 0;

bool lastAirPumpState = 0;			// 8-2019 added push bottoms paralel function with motor commands
bool lastWaterPumpState = 0;
bool lastValvesState = 0;
bool lastFanMotorState = 0;
bool lastNeoPixleMotorState = 0;


// ---   initionlized in SETUP routine ----
void readBottomsIni()
{
	pinMode(btmStartPin,	 INPUT_PULLUP);    // define all bottoms with pullup resistor      
	pinMode(btmHornPin,		 INPUT_PULLUP);
	pinMode(wheelBtm1Pin,	 INPUT_PULLUP);
	pinMode(wheelBtm2Pin,	 INPUT_PULLUP);
	pinMode(wheelBtm3Pin,	 INPUT_PULLUP);
	pinMode(btm_L_pin,		 INPUT_PULLUP);
	pinMode(btm_R_pin,		 INPUT_PULLUP);
	pinMode(btm_FwPin,		 INPUT_PULLUP);
	pinMode(btm_RevPin,		 INPUT_PULLUP);
	pinMode(drivePedalPin,	 INPUT_PULLUP);

	pinMode(btm_AirPin ,	 INPUT_PULLUP);    // front motor panel  all bottoms with pullup resistor      
	pinMode(btm_WaterPin ,	 INPUT_PULLUP);
	pinMode(btm_VlvPin ,     INPUT_PULLUP);
	pinMode(btm_FanPin ,     INPUT_PULLUP);
	pinMode(btm_neoMotrPin , INPUT_PULLUP);
}  // --- END of readBottoms INI rotine

// ---- called from within Main routine ( in the loop )
void readBottoms()
{
	// --------------------------------------------- btm  START ENGINE -MOTOR ON-------------------------
	btmStartState = digitalRead(btmStartPin);
	if (btmStartState != lastbtmStartState)
	{
		if (btmStartState == LOW)
		{
			Serial.println(" [ START  ] ");
			delay(20);
			motorOn = !motorOn;
			startBtmNumber = random(0, 18);
		}

	}
	lastbtmStartState = btmStartState;

	// ----------------------------  ------------------ btm HORN -HORN PUSHED-------------------------
	btmHornState = digitalRead(btmHornPin);
	if (btmHornState != lastbtmHornState)
	{
		if (btmHornState == LOW)
		{
			Serial.println(" [ HORN  ] ");
			delay(20);
			hornBtmNumber = random(1, 5);
		}
	}
	lastbtmHornState = btmHornState;

	// -------------------------------------------------- btm  RIGHT SIGNAL- -turnROn------------------------

	btm_rState = digitalRead(btm_R_pin);
	if (btm_rState != lastbtm_rState)
	{
		if (btm_rState == LOW)
		{
			Serial.println(" [ Right Turn ] ");
			delay(15);
			turnROn = !turnROn;         // toggel switch !!!
			nextCommand(4);             // play file # 4 in the /cmnd/x.mp3 subdirectory in sd card  - prerecorded

		}
	}
	lastbtm_rState = btm_rState;

	// -------------------------------------------------- btm  LEFT SIGNAL-turnLOn-------------------------

	btm_lState = digitalRead(btm_L_pin);
	if (btm_lState != lastbtm_lState)
	{
		if (btm_lState == LOW)
		{
			Serial.println(" [ Left Turn ] ");
			delay(15);
			turnLOn = !turnLOn;       // toggel switch !!!
		}
	}
	lastbtm_lState = btm_lState;

	// ------------------------------------------- btm   REVERSE -- reverseOn------------------------
	btm_Rev_state = digitalRead(btm_RevPin);
	if (btm_Rev_state != lastbtm_Rev_state)
	{
		if (btm_Rev_state == LOW)
		{
			Serial.println("[ REVERSE ]");
			delay(15);
			reverseOn = !reverseOn;         // toggel switch !!!
		}
	}
	lastbtm_Rev_state = btm_Rev_state;

	// ------------------------------------------- btm  FORWARD -- forwardOn-----------------------
	btm_Fw_state = digitalRead(btm_FwPin);
	if (btm_Fw_state != lastbtm_Fw_state)
	{
		if (btm_Fw_state == LOW)
		{
			Serial.println("[ FORWARD ]");
			delay(15);
			forwardOn = !forwardOn;          // toggel switch !!!
		}
	}
	lastbtm_Fw_state = btm_Fw_state;

	// -------------------------------------------------- WHEEL BOTTOM # 1  ----wheelBottom1Pushed----------------------

	wheelBtm1State = digitalRead(wheelBtm1Pin);
	if (wheelBtm1State != lastWheelBtm1State)
	{
		if (wheelBtm1State == LOW)
		{
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
		{
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
		{
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
		{
			Serial.println(" [ Drive Pedal  ] ");
			delay(15);
			drivePedalOn = 1;                 //  S A F T Y   switch 
		}
		else drivePedalOn = 0;              // only MOMENTARY witch  on when pushed OFF when not pushed
	}
	lastDrivePedalState = drivePedalState;

	// ------------------------------------------- btm  Air Pump  -- airPumpOn  ----------------------------

	 airPumpState= digitalRead(btm_AirPin);
	if (airPumpState != lastAirPumpState)
	{
		if (airPumpState == LOW)
		{
			Serial.println("[ Air Pump ]");
			delay(15);
			airPumpOn = !airPumpOn;          // toggel switch !!!
		}
	}
	lastAirPumpState = airPumpState;


	// ------------------------------------------- btm  Water Pump  -- waterPumpOn  ----------------------------

	waterPumpState = digitalRead(btm_WaterPin);
	if (waterPumpState != lastWaterPumpState)
	{
		if (waterPumpState == LOW)
		{
			Serial.println("[ Water Pump ]");
			delay(15);
			waterPumpOn = !waterPumpOn;          // toggel switch !!!
		}
	}
	lastWaterPumpState = waterPumpState;

	// ------------------------------------------- btm  Valve on motor   -- valvesMotorOn  ----------------------------

	valvesState = digitalRead(btm_VlvPin);
	if (valvesState != lastValvesState)
	{
		if (valvesState == LOW)
		{
			Serial.println("[ Valves on Motor ]");
			delay(15);
			valvesMotorOn = !valvesMotorOn;          // toggel switch !!!
		}
	}
	lastValvesState = valvesState;

	// ------------------------------------------- btm  Fan Radiator on motor   -- fanMotorOn  ----------------------------

	fanMotorState = digitalRead(btm_FanPin);
	if (fanMotorState != lastValvesState)
	{
		if (fanMotorState == LOW)
		{
			Serial.println("[  Fan Radiator  ]");
			delay(15);
			fanMotorOn = !fanMotorOn;          // toggel switch !!!
		}
	}
	lastValvesState = fanMotorState;
	


		// ------------------------------------------- btm  NeoPixles on motor   -- neoPixleMotorOn  ----------------------------

		neoPixleMotorState = digitalRead(btm_FanPin);
	if (neoPixleMotorState != lastNeoPixleMotorState)
	{
		if (neoPixleMotorState == LOW)
		{
			Serial.println("[  Motor neoPixles  ]");
			delay(15);
			neoPixleMotorOn = !neoPixleMotorOn;          // toggel switch !!!
		}
	}
	lastNeoPixleMotorState = neoPixleMotorState;

}// ----END read bottoms routine   ---------------------  


