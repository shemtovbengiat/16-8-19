// 
// 1.shut down the tractor after xx minetuse of no action of any keyboard pushing
// a recycle of the tractor key will be needed !!
// xx timer is setup at the " main" routine
//
// 2. a random time routine to do crazy thing each time it is switched/
//
unsigned long timeTillShutDownMs;
unsigned long randomTimeToInterruptMs;

unsigned long currentTimeShutDown;
unsigned long preveiosTimetShutDown;
unsigned long currentCrazyTime;
unsigned long preveiosCrazytime;

void shutDownIni()
{
	timeTillShutDownMs = 600 * shutDownTimer;		// set at Main routine, In minitues=60 sec/min x 1000 ms /sec/  
	pinMode(shutDownRelayPin, OUTPUT);
	randomTimeToInterruptMs = (random(1, maxTimeToInterupt) * 100);    //  sec., setup at the " main" routine X1000ms/sec.
	
	Serial.print("time to shut down ms - ");
	Serial.println(timeTillShutDownMs);
	Serial.print("Time to do somthing crazy ms - ");
	Serial.println(randomTimeToInterruptMs);
	Serial.print("crazy number : ");
	Serial.println(crazyNumber);
}


// ****************    shut down routine   ***************************
void shutDown()
{
	unsigned long currentTimeShutDown = millis();

	if (currentTimeShutDown - preveiosTimetShutDown <= timeTillShutDownMs) 
	{
		preveiosTimetShutDown == currentTimeShutDown;

		shutDownRelayOn = 1;		// 1=shut down, xx min. passed no action !! 
		Serial.println("time to shut down !");
		Serial.println(currentTimeShutDown);
	}
	else shutDownRelayOn = 0;		// 0= system good


	// *************    Do something CRAZY  !! routine *******************
	unsigned long currentCrazyTime = millis();
	if (currentCrazyTime - preveiosCrazytime >= randomTimeToInterruptMs);
	{
		preveiosCrazytime == currentCrazyTime;
		
		doSomethingCrazy = 1;			// 1=do something crazy in action  !!
		crazyNumber = random(1, 11);    // 1-10 "x"-massage # X --> in sd\massages\x.mp3 
		neoInteriorShow(4);				// 4- random
	}
	doSomethingCrazy = 0;			// 0= system normal
	//neoInteriorShow(3);				// 4- random
//		randomTimeToInterruptMs = (random(100, maxTimeToInterupt) * 1000);    // setup a new random number 
}

