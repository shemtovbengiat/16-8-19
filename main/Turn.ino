
/*
 Turns on and off 2 arrowa left and right (Vinkers) without using the delay() function.
 */

int turnLState = 0;                  // ledState used to set the LED
int turnRState = 0;

unsigned long previousLMillis = 0;      // will store last time LED was updated
unsigned long previousRMillis = 0;

long turnLRTiming = 0;                // interval at which to blink (10 fast 200 slowest in milliseconds)

// ----Turn -  Initialization  in SETUP routine--------
void turnIni()
{
	pinMode(turnL, OUTPUT);              // set the motor  Valves digital pin as output:
	pinMode(turnR, OUTPUT);
}
//--- END of Ini routine 



// --------  TURN signal  Vinkers  routine  ---------------------

void vinkers(bool turnLOn, bool turnROn, bool turnFast)      // turnfast -( 0=slowe 1=fast )
{
	bool _turnLOn = turnLOn;                     // for internal use                   
	bool _turnROn = turnROn;                     // for internal use                   
	bool _turnFast = turnFast;

	if (_turnLOn == 0 && _turnROn == 0)
	{
		turnLRTiming = 0;                  // interval at which to blink (10 fast 200 slowest in milliseconds)
		digitalWrite(turnL, 1);
		digitalWrite(turnR, 1);               // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
	}
	else if (_turnFast == 0)  // motor on slow valves 
	{
		turnLRTiming = 1400;                 //  slow 200 milliseconds)
		turnLights(_turnLOn, _turnROn);                     // service routine next peragaph 
	}
	else if (_turnFast == 1)
	{
		turnLRTiming = 700;               //  fast 60 milliseconds)
		turnLights(_turnLOn, _turnROn);                     // service routine next peragaph 
	}
	return;                                             // do nothing with the leds go back empty
}


// ---- servis routine to the above vinkers routine 0 

void turnLights(bool L, bool R)
{
	if (L == 1)
	{
		unsigned long currentLMillis = millis();
		if (currentLMillis - previousLMillis >= turnLRTiming)
		{
			previousLMillis = currentLMillis;   // save the last time you blinked the LED
			// if the turn light is off turn it on and vice-versa  --- valve 1 *********************************
			if (turnLState == 0)
			{
				turnLState = 1;
			}
			else {
				turnLState = 0;       // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
			}
		}
		digitalWrite(turnL, turnLState);
	}

	if (R == 1)
	{
		unsigned long currentRMillis = millis();            //  valve 2 *********************************
		if (currentRMillis - previousRMillis >= turnLRTiming)
		{
			previousRMillis = currentRMillis;   // save the last time you blinked the LED
			if (turnRState == 0)
			{
				turnRState = 1;
			}
			else {
				turnRState = 0;     // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
			}
		}
		digitalWrite(turnR, turnRState);   // set the LED with the ledState of the variable
	}
}// --- END of TURNlight  routine 


