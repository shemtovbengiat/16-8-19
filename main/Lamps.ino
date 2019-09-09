/*
    ----- LAMPS routine   - timers to drive  slow or fast rate  for the swithces lamp 12v
	----- called form action routine 
*/

int starterSwLampState		= 0;                   // state used to set the lamps
int swLampState				= 0;
int lightsLampState			= 0;

unsigned long previousStrtSwLampMs		 = 0;      // privious time lamps where updated
unsigned long previousSwLampMs			 = 0;
unsigned long previousLightsSwLampMS	 = 0;

unsigned long currentStrtSwLampMs   = 0;          // current time lamps where updated
unsigned long currentSwLampMs       = 0;
unsigned long currentLightsSwLampMS = 0;

long timingFast =  lampTimerFast;                 // set at main routine - 10 fast 200 slow / ms
long timingSlow =  lampTimerSlow;
long timingMid =   lampTimerMid;

long startLamprate;				   // for internal use       
long swLamprate;				   // for internal use       
long lightsLampRate;			   // for internal use       



void lampsIni()
{// ----  Lamps in switchs   Initialization  in SETUP routine--------
	pinMode(startSwLampPin,  OUTPUT);             // set the lamps within switchs  pin as output:
	pinMode(swLampPin,		 OUTPUT);
	pinMode(lightSwLampPin,  OUTPUT);
}//  ----- end of Ini routine 


//  ----- SWITCH LAMP routine
void switchLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{
	if (rate == 0)  		digitalWrite(swLampPin, 0);

	else if (rate == 1)          swLamprate = timingFast;
	else if (rate == 2)          swLamprate = timingSlow;
	else if (rate == 3)          swLamprate = timingMid;


	unsigned long currentSwLampMs = millis();
	if (currentSwLampMs - previousSwLampMs >= swLamprate)
	{
		previousSwLampMs = currentSwLampMs;

		if (swLampState == LOW)
		{
			swLampState = HIGH;
		}
		else {
			swLampState = LOW;
		}
		digitalWrite(swLampPin, swLampState);
	}
}//  ----  end of SWITCH Lamp routine ---


//  ----- LIGHTS LAMP routine
void lightsLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{
	if (rate == 0) { lightsLampRate = timingMid; }
		
// digitalWrite(lightSwLampPin, 0);

	else if (rate == 1)          lightsLampRate = timingFast;
	else if (rate == 2)          lightsLampRate = timingSlow;
	else if (rate == 3)          lightsLampRate = timingMid;


	unsigned long currentLightsSwLampMS = millis();
	if (currentLightsSwLampMS - previousLightsSwLampMS >= lightsLampRate)
	{
		previousLightsSwLampMS = currentLightsSwLampMS;   
		
		if (lightsLampState == LOW)
		{
			lightsLampState = HIGH;
		}
		else {
			lightsLampState = LOW;
		}
		digitalWrite(lightSwLampPin, lightsLampState);
	}
}//  ----  end of LIGHTS Lamp routine ---




//  ----  STARTER LAMP routine
void starterLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{
	if (rate == 0) { 
		digitalWrite(startSwLampPin, 0);
	}
	
	else if (rate == 1)          startLamprate = timingFast;           
	else if (rate == 2)          startLamprate = timingSlow;
	else if (rate == 3)          startLamprate = timingMid;


	unsigned long currentStrtSwLampMs = millis();
	if (currentStrtSwLampMs - previousStrtSwLampMs >= startLamprate)
	{
		previousStrtSwLampMs = currentStrtSwLampMs;  
		if (starterSwLampState == LOW)
		{
			starterSwLampState = HIGH;
		}
		else {
			starterSwLampState = LOW;
		}
		digitalWrite(startSwLampPin, starterSwLampState);
	}
}//  ----  end of starter Lamp routine ---


