

//  ***********************    Actions routine     ************************************************************
//  here we make decisions on what to do with the inputs and outputs based on global variables on the main file
//  ***********************************************************************************************************
void action()
{
	//   ***********************  set Drive ENABLE  ********************
	driveEnable = 0;
	if (drivePedalOn = 1 && motorOn == 1 && (forwardOn == 1 || reverseOn == 1))
		{
			driveEnable = 1;				 // S A F A T Y  fleg !!!
		}
		else driveEnable = 0;

	//  **********************   motor section   **************
	if (motorOn == 0)							 // Motor OFF -  start engine not pushed  yet.. - DO Nothing
	{
		valves(0, 0);
		fanMotor(0);
		
		neoMotorShow();
		neoInteriorShow(0);
		
		set3Lamps(1, 0, 1);						// sw, lights, starter 0-off 1-on 2-slow 3-mid 4-fast rate
	}
	//  *********************   Start Engine   ****************
	if (motorOn == 1 && driveEnable == 0)	    // start engine bottom pushed   motorOn ==1
	{
		set3Lamps(1,1,2);		//sw, lights, starter       0-off 1-on 2-slow 3-mid 4-fast rate
									           
		neoMotorShow();
		neoInteriorShow(1);
		
		valves	   (1, 1);		// 1=on, 1= slow rate blinking
		
		fanMotor   (2);			// 0=off, 1=on,  2=slow,   3=fast
		airMotor   (2);
		waterMotor (2);


		
		if (startBtmNumber != startBtmNumberOld)		//  ---- starter switch -  check to see if pushed again   ----------------------
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
	if (motorOn == 1 && driveEnable == 1)        // verify that no driving if first set F or R and only then drive pedal push
	{
		valves(1, 1);							//rpm  = fast
		fanMotor (3);                           //1 = on
		waterMotor(1);
		


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


