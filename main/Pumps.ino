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
	pinMode(radiatorRelayPin,    OUTPUT);

}//----END of PUMP Initilatziotion Routine


// --- PUMPS  Water, air  & fan motor routine
void pumps(bool pumpsOn, int pumpsFast)
{
	// bool _valvesOn = valvesOn;                     // for internal use                   
	// bool _valvesFast = valvesFast;

	if (pumpsOn == 1 && pumpsFast == 1)
	{
		waterPump->  run(FORWARD);
		waterPump->  setSpeed(200);
		airPump->    run(FORWARD);
		airPump->    setSpeed(250);
		fanMotor->   run(FORWARD);
		fanMotor->   setSpeed(250);
	}
	if (pumpsOn == 1 && pumpsFast == 0)  // motor on slow valves 
	{
		waterPump->  run(FORWARD);
		waterPump->  setSpeed(80);
		airPump->    run(FORWARD);
		airPump->    setSpeed(80);
		fanMotor->   run(FORWARD);
		fanMotor->   setSpeed(80);
	}
	if (pumpsOn == 0)
	{
		waterPump-> run(RELEASE);  // stop motors RELEASE = stop 
		airPump->   run(RELEASE);
		fanMotor->  run(RELEASE);
	}
}// --- E N D of pumps routine


