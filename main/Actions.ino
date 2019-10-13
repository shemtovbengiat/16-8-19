

/*          ---------    Actions routine ------------
 here we make decisions on what to do with the inputs and outputs based on global variables on the main file
 */

void action()
{
	// --------  Drive Motors  section  -------------------------

	// ----  drive enable section  ------- 
	driveEnable = 0;
	if (drivePedalOn = 1 && motorOn == 1 && (forwardOn == 1 || reverseOn == 1))
		{
			driveEnable = 1;    // S A F A T Y  fleg !!!
		}
		else driveEnable = 0;

	//   --- motor section -----
	if (motorOn == 0)         // start bottom not pushed  yet.. - DO Nothing
	{
		pumps(0, 0);                              // water and air pumps fan motor (0=off 1=on slow, 1=fast 0=slow)
		neoInteriorShow(0);
		valves(1, 0); 
		neoMotorShow();
		set3Lamps(1, 0, 1);   // sw, lights, starter 0-off 1-on 2-slow 3-mid 4-fast rate
	}
// ==========================================================================
	if (motorOn == 1 && driveEnable == 0)         
									//   START bottom pushed motorOn ==1
	{
		pumps(1, 0);                // water and air pumps fan motor (0=off 1=on slow, 1=fast 0=slow)
		//neoMotorShow();
		neoInteriorShow(1);
		
		valves(1, 1);
		//switchLamp(4);
		//starterLamp(2);
		//lightsLamp(3);
		set3Lamps(1,1,1);    // sw, lights, starter 0-off 1-on 2-slow 3-mid 4-fast rate
		//  ---- starter switch -  check to see if pushed again   ----------------------
		if (startBtmNumber != startBtmNumberOld)
		{
			Serial.println(startBtmNumber);
			startBtmNumberOld = startBtmNumber;
			nextStarter(startBtmNumber);
		}

		if (lightsOn = 1) {
			lightsLamp(4); // flash slow
		}
		
	}
//=============================================================================
	if (motorOn == 1 && driveEnable == 1)        // verify that no driving if first set F or R and only then drive pedal push
	{
		//musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
		valves(1, 1);                     //rpm  = fast
		pumps(1, 1);                           //rpm  = fast

		


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


