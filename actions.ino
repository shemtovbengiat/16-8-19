

//  ***********************    Actions routine     ************************************************************
//  here we make decisions on what to do with the inputs and outputs based on global variables on the main file
//  ***********************************************************************************************************
void action()
{
	// *************************  battry empty -  drive motors routine  **********************************
	// If main batttary (12V) goes down less the 11.0 volts, relay switch  go on and connects battaryDeadPin to ground
	// all motors actions go off no drive unless start engine sw  and pedal are pushed together.  
	// interior led go red  all lamps off, neopixles battary (6V)is out of this game 
	// ************************************

	//  ***********************************************************
	//  ********************   shut down *******************
	//  ***********************************************************
	if (shutDownRelayOn == 1) 
	{  //0=battary empty=ground. motor fuction's off,  intirior leds yellow flashing
		// driving home -->> pedal + start engine pushbottom together!! 
		valves(0, 0);
		fanMotor(0);
		airMotor(0);
		waterMotor(0);
		//neoStopAll();
		
		//neoMotorShow    (0);        // 0-off, 1-3 RGB, 4-random
		neoInteriorShow (4);		// 0=red, 1=green, 4=battary dead = yellow flasing 2=forward midlle leds blue, 3=reverse 2x4 sides blue, 

		if (massagePlayed == 0)		//sound worning /cmnd/99.mp3  battary finish in order to get back...
		{
			digitalWrite(shutDownRelayPin, 0);		// turn on (0=on 1=off) and cut driving power relay , all the rest is good
			//digitalWrite(redLightDrivePin, 1);		// turn off red  light (1=0FF 0=ON) while driving with dead battary
			Serial.println("I am going to rest for a while");
			nextCommand(99);    	//sound worning /cmnd/99.mp3 subdirectory in sd card
			massagePlayed = 1;
		}
		//starterLamp(2);			// 0-off, 1-on 2-slow 3-mid 4-fast rate

	}
	else digitalWrite(shutDownRelayPin, 1);		//1= battary is good lets continue relay off  (8 module) off=nc cottect 12v to motors 
	//  ***********************************************************
	//   **************** Crazy thing random time routine   ********
	//  ***********************************************************
	if (doSomethingCrazy ==1)
	{
		Serial.print("  crazy number = ");
		Serial.print(crazyNumber);
		nextStory(crazyNumber);			// serprise sound
	}
	//   ***********************  set Drive ENABLE  ********************
	if (drivePedalOn = 1 && motorOn == 1 && (forwardOn == 1 || reverseOn == 1))
	{
		/*if (battaryDeadOn == 1) {									// battary empty 
			if (digitalRead(btmStartEngPin) == 0) driveEnable = 1;  // battary low relay on ==0  and start engine bottom pushed with all the above 
			}*/
		driveEnable = 1;											// S A F A T Y  fleg !!!
		//Serial.println(" [ drive enabled  ] ");
	}		
	else driveEnable = 0;

	// **********************************************************
	//  **********************   motor section   **************
    // **********************************************************
	if (motorOn == 0)								 // Motor OFF -  start engine not pushed  yet.. - DO Nothing
	{
		Drive(0, 0);								// no driving
		starterLamp (0);							// turn lamp  0-off 1-on 2-slow 3-mid 4-fast rate
		
		neopixleIntirior.Scanner(neopixleIntirior.Color(0, 0, 0),60);		//turn off intirior neopixles
		neopixleMotor.Scanner(neopixleMotor.Color(0, 0, 0),40) ;	// turn off neopixle in  motor
		neopixleRturn.Scanner(neopixleRturn.Color(0,0,0), 70);
		neopixleLturn.Scanner(neopixleLturn.Color(0,0,0), 70);
		
		valves		(0, 0);							//turn valve off
		fanMotorNumber	= 0;
		fanMotor	(fanMotorNumber);
		//airPumpNumber	= 0; 
		airMotor(0);
		airMotor(airPumpNumber);	
		waterPumpNumber = 0;
		waterMotor	(waterPumpNumber);	
							//neoMotorNumber	= 0;
	}
	//  ***********************************************************
	//  *********************   Start Engine   ****************
	//  ***********************************************************
	
	if (motorOn == 1 && driveEnable == 0)	    // start engine bottom pushed   motorOn ==1
	{
		Drive(0, 0);			// no driving
		starterLamp		(1);
		valves	   (1, 1);		// 1=on, 1= slow rate blinking


		fanMotor   (1+fanMotorNumber);			// 0=off, 1=on,  2=slow,   3=fast
		airMotor   (1+airPumpNumber);
		waterMotor (1+waterPumpNumber);

		//neopixleMotor.Scanner(neopixleMotor.Color(0, 100, 0), 50);			// turn off neopixle in  motor

		//neoMotorNumber = 1;
		//neoMotorShow	(2);    // 0-off, 1-red, 2-green, 3-blue, 4-random
		//neoInteriorShow	(swRasbPiNumber);    // 0=red, 1=green, 2=forward midlle leds blue, 3=reverse 2x4 sides blue, 4=battary dead = yellow flasing 

		//swRasbPiLamp	(swRasbPiNumber);
		
		
		
/*

		//  **************************   start engine  -  check to see if pushed again  ****************
		if (startBtmNumber != startBtmNumberOld)		
		{
			Serial.println(startBtmNumber);
			startBtmNumberOld = startBtmNumber;
			nextStarter(motorOn);				// mp3 play starter sound random 
		}
*/
	}
	//neoInteriorStop;
	//  ***********************************************************
	//=======================================================
	//  ***********************************************************
	
	if (motorOn == 1 && driveEnable == 1)    // verify that no driving if first set F or R and only then drive pedal push
	{
		// drive section
		
		Drive(1, 0);			//0 =stop, 1 = forward, 2 = reverse, speed set at main routine 0 -255 max speed 
	

		valves(1, 1);						//rpm  = fast
		fanMotor	(2 + fanMotorNumber);			// 0=off, 1=on,  2=slow,   3=fast
		airMotor	(2 + airPumpNumber);
		waterMotor	(2 + waterPumpNumber);
		// display

		//set3Lamps(1, 1, 4);		//sw, lights, starter       
		//neoInteriorShow(4);		// 0-red,  1-green, 2-frw, 3- rev, 4-yellow flasing battary empty  
		starterLamp(2);			// 0-off, 1-on 2-slow 3-mid 4-fast rate
		//neoMotorShow(3);		// 0-off, 1-red, 2-green, 3-blue, 4-random

	}
	//  ***********************************************************

	// ----------------- Turn Signal Section ---------------
	vinkers(turnLOn,turnROn, 0);
	//neoTurn_Lshow(1);
	//neoTurn_Rshow(1);
	
	//  *********************************************************
	//  --------------  LIGHTS  on off routing     --------------
	//  **********************************************************
	if (lightsOn == 0)     // consider adding timer to cut off power to head lights !!!!!!!! save battary  
	{
		//digitalWrite(LightsRelayPin, 1);		// On=0 relay module --> 12 v to lamps in front
		lightsLamp(0);					        // rate = 0-off, 1-On, 2-slow, 3-mid, 4-fast
		//digitalWrite(redLightDrivePin, 1);		// turn Red lights off (1=0FF 0=ON)

	}
	else if(lightsOn == 1)
	{
		//digitalWrite(LightsRelayPin, 0);		// Off =1  relay module --> 12 v to lamps in front
		lightsLamp(1);		  					// rate = 0-off, 1-On, 2-slow, 3-mid, 4-fast
		//digitalWrite(redLightDrivePin, 0);		// turn Red lights on (1=0FF 0=ON)
	}

	
	//  ---------------  Blue  switch -   routine   ----------------------
	if (steeringBtmBlueNumber != steeringBtmBlueOld)
	{
		steeringBtmBlueNumber = steeringBtmBlueOld;
		nextSong(steeringBtmBlueNumber);
	}

	//  ----  Red switch -   routine   ----------------------
	if (steeringBtmRedNumber != steeringBtmRedOld)
	{
		steeringBtmRedOld = steeringBtmRedNumber;
		nextVocal(steeringBtmRedNumber);
	}

	//  ----  Black switch -    routine   ----------------------
	if (steeringBtmBlackNumber != steeringBtmBlackOld)
	{
		Serial.println(steeringBtmBlackNumber);
		steeringBtmBlackOld = steeringBtmBlackNumber;
		nextSong(steeringBtmBlackNumber);
	}

	//  ---- Horn switch -    routine   ----------------------
	if (hornBtmNumber != hornBtmOld)
	{
		Serial.println(hornBtmNumber);
		hornBtmOld = hornBtmNumber;
		nextHorn(hornBtmNumber);
	}

	// ------   sw raspberry Pi routine --------------------------
	swRasbPiLamp(swRasbPiNumber);	//1-4 to set blinking rate of led inside bottom 

}//---END of Action routine


