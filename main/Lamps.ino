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

long starterLampRate;				   // for internal use       
long swLampRate;				   // for internal use       
long lightsLampRate;			   // for internal use       



void lampsIni()
{// ----  Lamps in switchs   Initialization  in SETUP routine    --------
	pinMode(starterSwLampPin,  OUTPUT);             // set the lamps within switchs  pin as output:
	pinMode(swLampPin,		 OUTPUT);
	pinMode(lightSwLampPin,  OUTPUT);
}//  ----- end of Ini routine 

// ***************************************************************
// light all lamps in one comand on off slow mid or fast 0-4 --------
//*****************************************************************

void set3Lamps(int sw , int lght , int  start  ) 
{
	int lamp1 = sw;
	int lamp2 = lght;
	int lamp3 = start;

	switchLamp(lamp1);
	lightsLamp(lamp2);
	starterLamp(lamp3);
}
//  ----- SWITCH LAMP routine  ***********************************
void switchLamp(int rate)   // ---- rate = 0-off, 1-on, 2-slow, 3-mid, 4-fast   
{
	if (rate == 0) {
		digitalWrite(swLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(swLampPin, 1);
		return;
	}
	else if (rate == 2)          swLampRate = timingSlow;
	else if (rate == 3)          swLampRate = timingMid;
	else if (rate == 4)          swLampRate = timingFast;


	unsigned long currentSwLampMs = millis();
	if (currentSwLampMs - previousSwLampMs >= swLampRate)
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


//  ----- LIGHTS LAMP routine  **************************
void lightsLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{


	if (rate == 0) {
		digitalWrite(lightSwLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(lightSwLampPin, 1);
		return;
	}

	else if (rate == 2)          lightsLampRate = timingSlow;
	else if (rate == 3)          lightsLampRate = timingMid;
	else if (rate == 4)          lightsLampRate = timingFast;


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




//  ----  STARTER LAMP routine    *****************************************
void starterLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{

	if (rate == 0) {
		digitalWrite(starterSwLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(starterSwLampPin, 1);
		return;
	}

	else if (rate == 2)          starterLampRate = timingSlow;           
	else if (rate == 3)          starterLampRate = timingMid;
	else if (rate == 4)          starterLampRate = timingFast;


	unsigned long currentStrterSwLampMs = millis();
	if (currentStrterSwLampMs - previousStrtSwLampMs >= starterLampRate)
	{
		previousStrtSwLampMs = currentStrterSwLampMs;  
		if (starterSwLampState == LOW)
		{
			starterSwLampState = HIGH;
		}
		else {
			starterSwLampState = LOW;
		}
		digitalWrite(starterSwLampPin, starterSwLampState);
	}
}//  ----  end of starter Lamp routine ---


