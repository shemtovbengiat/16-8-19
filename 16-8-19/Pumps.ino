

/*
there are 3 motors -air & water pumps and 1 fan motor
all connected to Adafruit Motor Shield v2 ---->	http://www.adafruit.com/products/1438
shild uses with th I2C protocol
*/

Adafruit_MotorShield PUMPS = Adafruit_MotorShield(); // Construct the motor shield object PUMPS with the default I2C address
// Or, create it with a different I2C address (say for stacking) Adafruit_MotorShield PUMPS = Adafruit_MotorShield(0x61); 

Adafruit_DCMotor *fanMotor = PUMPS.getMotor(2);
Adafruit_DCMotor *waterPump = PUMPS.getMotor(3);     // Select which 'port' M2, M3 or M4. 
Adafruit_DCMotor *airPump = PUMPS.getMotor(4);


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


