

//  ***********************    Actions routine     ************************************************************
//  here we make decisions on what to do with the inputs and outputs based on global variables on the main file
//  ***********************************************************************************************************
void action()
{
	// *************************  battry empty -  drive motors routine  **********************************
	// if bat less the 11 volts, relay switch on and connects battaryDeadPin to ground
	// all motors actions > off no drive unless horn sw  and pedal are pushed together.  
	// interior led go red  all lamps off, second battary is ok for all the rest 
	// ************************************

	if (battaryDeadOn == 1) {  //0= battary  empty = ground motor's fuction off,  intirior leds yellow flashing
		// driving home -->> pedal + start engine pushbottom together!! 

		valves(0, 0);
		fanMotor(0);
		airMotor(0);
		waterMotor(0);
		//neoStopAll();
		
		neoMotorShow    (0);        // 0-off, 1-3 RGB, 4-random
		neoInteriorShow (4);		// 0=red, 1=green, 4=battary dead = yellow flasing 2=forward midlle leds blue, 3=reverse 2x4 sides blue, 
		nextCommand     (99);    	//sound worning /cmnd/99.mp3 subdirectory in sd card
	}
	
	//   ************************* crazy thing random time routine   ********************************
	if (doSomethingCrazy == 1)
	{
		Serial.println("  crazy number: ");
		Serial.println(crazyNumber);
	}
	//   ***********************  set Drive ENABLE  ********************
	//driveEnable = 0;
	if (drivePedalOn = 1 && motorOn == 1 && (forwardOn == 1 || reverseOn == 1))
	{
		/*if (battaryDeadOn == 1) {									// battary empty 
			if (digitalRead(btmStartEngPin) == 0) driveEnable = 1;  // battary low relay on ==0  and start engine bottom pushed with all the above 
			}*/
		driveEnable = 1;											// S A F A T Y  fleg !!!
		Serial.println(" [ drive enabled  ] ");
	}		
	else driveEnable = 0;

	//  **********************   motor section   **************
// **************************************************************
	if (motorOn == 0)							 // Motor OFF -  start engine not pushed  yet.. - DO Nothing
	{
		Drive(0, 0);			// no driving
		
		valves		(0, 0);
		fanMotor	(0);
		airMotor	(0);
		waterMotor	(0);
		
		//musicPlayer.pausePlaying(false);
		//neoStopAll;
		neoInteriorShow (0);    // 0=red, 1=green, 2=forward midlle leds blue, 3=reverse 2x4 sides blue, 4=battary dead = yellow flasing 
		neoMotorShow    (1);    // 0-off, 1-3 RGB, 4-random
		starterLamp     (2);    //  0-off 1-on 2-slow 3-mid 4-fast rate
	}
	//  *********************   Start Engine   ****************
	if (motorOn == 1 && driveEnable == 0)	    // start engine bottom pushed   motorOn ==1
	{
		Drive(0, 0);			// no driving

		valves	   (1, 1);		// 1=on, 1= slow rate blinking
		fanMotor   (2);			// 0=off, 1=on,  2=slow,   3=fast
		airMotor   (2);
		waterMotor (2);
		//musicPlayer.pausePlaying(false);

		neoMotorShow	(2);    // 0-off, 1-red, 2-green, 3-blue, 4-random
		neoInteriorShow	(1);    // 0=red, 1=green, 2=forward midlle leds blue, 3=reverse 2x4 sides blue, 4=battary dead = yellow flasing 

		lightsLamp		(lightsOn);
		swRasbPiLamp	(swRasbPiOn);
		starterLamp		(1);
		
		


		//  **************************   start engine  -  check to see if pushed again  ****************
		if (startBtmNumber != startBtmNumberOld)		
		{
			Serial.println(startBtmNumber);
			startBtmNumberOld = startBtmNumber;
			nextStarter(startBtmNumber);				// mp3 play starter sound random 
		}

		if (lightsOn = 1) {
			lightsLamp(4);								// flash slow led inside light switch
		}
		
	}
//=============================================================================
	if (motorOn == 1 && driveEnable == 1)    // verify that no driving if first set F or R and only then drive pedal push
	{
		// drive section
		
		Drive(1, 0);			//0 =stop, 1 = forward, 2 = reverse, speed set at main routine 0 -255 max speed 
	

		valves(1, 1);						//rpm  = fast
		fanMotor(3);						// 0=off, 1=on,  2=slow,   3=fast
		airMotor(3);
		waterMotor(3);
		// display

		set3Lamps(1, 1, 4);		//sw, lights, starter       
		neoInteriorShow(4);		// 0-red,  1-green, 2-frw, 3- rev, 4-yellow flasing battary empty  
		starterLamp(4);			// 0-off, 1-on 2-slow 3-mid 4-fast rate
		neoMotorShow(3);		// 0-off, 1-red, 2-green, 3-blue, 4-random

	}

	//  ----  Blue  switch -   routine   ----------------------
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

	// ----------- Turn Signal Section ---------------

	if (turnLOn == 0 && turnROn == 0)         //no start bottom pushed DO Nothing
	{
		vinkers(0, 0, 0);
		return;                           // no vinkers
	}

	if ((turnLOn == 1 && turnROn == 0) && motorOn == 1)         //left vinker (slow)
	{
		vinkers(1, 0, 0);                        // no vinkers
		return;
	}
	if ((turnLOn == 0 && turnROn == 1) && motorOn == 1)         //right vinker (slow)
	{
		vinkers(0, 1, 0);                        // no vinkers
		return;
	}

	if ((turnLOn == 1 || turnROn == 1) && motorOn == 0)
	{
		vinkers(1, 1, 1);                        // no vinkers
		return;
	}
	else if ((turnLOn == 1 && turnROn == 0) && motorOn == 0) vinkers(0, 0, 0);
	
}//---END of Action routine


