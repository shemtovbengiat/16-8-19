

/*    ----------- Valves Routine -----------
 Turns on and off 2 (LED) connected to "" valves " on the motor,
 without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

bool valvesOn = 0;                  // 0-leds off 1 leds on fast or slow to be changed by calling routine !
bool valvesFast = 0;                // 0-slow 1 fast       -    motorVales(valvesOn,valesFast)

int valve1State = LOW;                  // ledState used to set the LED
int valve2State = LOW;
unsigned long previous1Millis = 0;      // will store last time LED was updated
unsigned long previous2Millis = 0;
long valve1Timing = 0;                // interval at which to blink (10 fast 200 slowest in milliseconds)
long valve2Timing = 0;

// ----valves   Initialization  in SETUP routine--------
void motorValvesIni()
{
	pinMode(valve1Pin, OUTPUT);              // set the motor  Valves digital pin as output:
	pinMode(valve2Pin, OUTPUT);
	return;
}
//  ----- end of Ini routine 


// ------------------- Motor Valves routine  -----------------------

void motorValves(bool valvesOn, bool valvesFast)
{
	bool _valvesOn = valvesOn;                     // for internal use                   
	bool _valvesFast = valvesFast;

	if (_valvesOn == 0)
	{
		valve1Timing = 0;                  // interval at which to blink (10 fast 200 slowest in milliseconds)
		valve2Timing = 0;
		digitalWrite(valve1Pin, 0);
		digitalWrite(valve2Pin, 0);
	}
	else if (_valvesFast == 0)  // motor on slow valves 
	{
		valve1Timing = 200;                 //  slow 200 milliseconds)
		valve2Timing = 200;
		lightValves();                     // service routine next peragaph 
	}
	else if (_valvesOn == 1 && _valvesFast == 1)
	{
		valve1Timing = 60;               //  fast 60 milliseconds)
		valve2Timing = 80;
		lightValves();                  // service routine next peragaph 
	}
	return;                                             // do nothing with the leds go back empty
}


void lightValves()   // ---- light valve sub routine according to fast=1 or slow=0 (1/2 speed)
{
	unsigned long current1Millis = millis();
	if (current1Millis - previous1Millis >= valve1Timing)
	{
		previous1Millis = current1Millis;   // save the last time you blinked the LED
		// if the LED is off turn it on and vice-versa  --- valve 1 *********************************
		if (valve1State == LOW)
		{
			valve1State = HIGH;
		}
		else {
			valve1State = LOW;
		}
		digitalWrite(valve1Pin, valve1State);
	}

	unsigned long current2Millis = millis();            //  valve 2 *********************************
	if (current2Millis - previous2Millis >= valve2Timing)
	{
		previous2Millis = current2Millis;   // save the last time you blinked the LED
		if (valve2State == LOW)
		{
			valve2State = HIGH;
		}
		else {
			valve2State = LOW;
		}
		digitalWrite(valve2Pin, valve2State);   // set the LED with the ledState of the variable
	}
	return;
}
  //  ----  end of light valves routine 




