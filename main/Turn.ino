/*
     Turns on and off 2 arrowa left and right (Vinkers) without using the delay() function.
 */

int turnLState = 0;                  // turn lights State 
int turnRState = 0;

unsigned long previousLms = 0;      // will store last time Lights where updated
unsigned long previousRms = 0;

long turnLRTiming = 0;                // interval at which to blink 

// ---- Turn Initialization  in SETUP routine--------
void turnIni()
{
	pinMode(turnL_Pin, OUTPUT);              // set the vinkers digital pin as output:
	pinMode(turnR_Pin, OUTPUT);
}
//--- END of Ini routine 



// --------  TURN signal  Vinkers  routine  ---------------------

void vinkers(bool turnLOn, bool turnROn, bool turnFast)      // turnfast -( 0=slowe 1=fast )
{
	bool L = turnLOn;                      // for internal use                   
	bool R = turnROn;                      // for internal use                   
	bool F = turnFast;					   // for internal use       

	if (L == 0 && R == 0)
	{
		digitalWrite(turnL_Pin, 1);
		digitalWrite(turnR_Pin, 1);           // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
	}
	else if (F == 0)                      // regular vinker - slow  
	{
		turnLRTiming = 200;              //  1400 slow 200 milliseconds)
		turnLights(L, R);                 // service routine next peragaph 
	}
	else if (F == 1)                      // both vinkers  - emergency lights - fast 
	{
		turnLRTiming = 700;               //  fast 60 milliseconds)
		turnLights(L, R);                 // service routine next peragaph 
	}
	return;                               // do nothing with the leds go back empty
}

// ---- servis routine to the above vinkers routine 0 

void turnLights(bool L, bool R)
{
	if (L == 1)
	{
		unsigned long currentLms = millis();
		if (currentLms - previousLms >= turnLRTiming)
		{
			previousLms = currentLms;  
			if (turnLState == 0)
			{
				turnLState = 1;
			}
			else {
				turnLState = 0;       // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
			}
		}
		digitalWrite(turnL_Pin, turnLState);
	}

	if (R == 1)
	{
		unsigned long currentRms = millis();          
		if (currentRms - previousRms >= turnLRTiming)
		{
			previousRms = currentRms;   
			if (turnRState == 0)
			{
				turnRState = 1;
			}
			else {
				turnRState = 0;     // 1 = RELAY OFF ,pin at 0 activate relay by going ground !!!!!!!!!!!!
			}
		}
		digitalWrite(turnR_Pin, turnRState);   // set the LED with the ledState of the variable
	}
}// --- END of TURNlight  routine 


