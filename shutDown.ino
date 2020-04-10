// 
// 1. shut down the tractor after xx minetuse of no action of any switchs
//    a recycle of the tractor key will be needed !! 
//
// 2. a random time routine to do crazy thing each time it is switched/
//	  maxTimeToInterupt timer is setup at the " main" routine
//
unsigned long timerToShutDownMs;
unsigned long randomTimeCrazyThingMs ;
unsigned long oldRandomTimeCrazyThingMs ;
//unsigned int  maxTimeToInterupt;

unsigned long currentTimeShutDown;
unsigned long preveiosTimeToShutDown;
unsigned long currentCrazyTime;
unsigned long preveiosCrazytime;


void shutDownIni()
{
	timerToShutDownMs = 60000 * shutDownTimer;		// set at Main routine, In minitues=60 sec/min x 1000 ms /sec/  
	pinMode(shutDownRelayPin, INPUT_PULLUP);
	pinMode(shutDownRelayPin, OUTPUT);
	randomTimeCrazyThingMs = 100000;    //  sec., setup at the " main" routine X1000ms/sec.
	oldRandomTimeCrazyThingMs = 0;		// only first at start inin riutine 
	Serial.print("time to shut down ms: ");
	Serial.println(timerToShutDownMs);
	Serial.print("Time to do somthing crazy ms: ");
	Serial.println(randomTimeCrazyThingMs);
	Serial.print("crazy number : ");
	Serial.println(crazyNumber);
}


// ****************    shut down routine   ***************************
/* ** any switch that will be pushed will also set "noSwPushForLongTime" to 0
 * ** if time passed without any switchs pushed the noSwPushForLongTime set to 1 and then power is off.
*/

void shutDown()
{
	if (noSwitchPushed == 0)// 1=long time no action, Time to start timer togo to sleep, 0=switch pushed lately
	{
		Serial.println("no switch pushed for long time = 1 ");
		unsigned long currentTimeToShutDown = millis();
			Serial.println(currentTimeShutDown);
		if (currentTimeToShutDown - preveiosTimeToShutDown <= timerToShutDownMs)
		{
			preveiosTimeToShutDown = currentTimeToShutDown;

			shutDownRelayOn = 1;		// 1=shut down power, ~6 mineunts passed with no action from the kids!! 
			Serial.println("time to shut down !");
		}
		else shutDownRelayOn = 0;		// 0= system good, power on continiues
	}

	// *************    Do something CRAZY  !! routine *******************
	// **********************************************************************
	if (randomTimeCrazyThingMs != oldRandomTimeCrazyThingMs)
	{
		randomTimeCrazyThingMs = (random(100, maxTimeToInterupt) * 1000);    //  sec., setup at the " main" routine X1000ms/sec.
//		Serial.println(randomTimeCrazyThingMs);

	}
	unsigned long currentCrazyTime = millis();
	if (currentCrazyTime - preveiosCrazytime >= randomTimeCrazyThingMs)
	{
		preveiosCrazytime = currentCrazyTime;
		oldRandomTimeCrazyThingMs = randomTimeCrazyThingMs;

		doSomethingCrazy = 1;			// 1=do something crazy in action  !!
		crazyNumber = random(1, 4);    // 1-10 "x"-massage # X --> in sd\massages\x.mp3 

	}
	else doSomethingCrazy = 0;			// 0= system normal
}

