/*
    ----- LAMPS routine   - timers to drive  slow or fast rate  for the swithces lamp 12v
	----- called form action routine/
	---- 
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
/*
long timingLampFast =  lampTimerFast;                 // set at main routine - 10 fast 200 slow / ms
long timingLampSlow =  lampTimerSlow;
long timingLampMid =   lampTimerMid;
*/
long starterLampRate;				   // for internal use       
long swLampRate;				       // for internal use       
long lightsLampRate;			       // for internal use       



void lampsIni()
{// ----  Lamps in switchs   Initialization  in SETUP routine    --------
	pinMode(startEngineLampPin,  OUTPUT);             // set the lamps within switchs  pin as output:
	pinMode(swRaspPiLampPin,	 OUTPUT);
	pinMode(lightsSwLampPin,     OUTPUT);
}//  ----- end of Ini routine 

// ***************************************************************
// light all lamps in one comand on off slow mid or fast 0-4 --------
//*****************************************************************

void set3Lamps(int sw , int lght , int  start  ) 
{
	swRasbPiLamp   (sw);
	lightsLamp     (lght);
	starterLamp    (start);
}
// -------------------------   end setting lamps of switcges ----



// ******************************** SWITCH LAMP routine  ***********************************
void swRasbPiLamp(int swRate)   // ---- rate = 0-off, 1-on, 2-slow, 3-mid, 4-fast   
{
	if (swRate == 0) {
		digitalWrite(swRaspPiLampPin, 0);
		return;
	}
	else if (swRate == 1) {
		digitalWrite(swRaspPiLampPin, 1);
		return;
	}
	else if (swRate == 2)   swLampRate = lampTimerSlow;
	else if (swRate == 3)   swLampRate = lampTimerMid;
	else if (swRate == 4)   swLampRate = lampTimerFast;

	unsigned long currentSwLampMs = millis();
	if (currentSwLampMs - previousSwLampMs >= swLampRate)
	{
		previousSwLampMs = currentSwLampMs;

		if (swLampState == LOW)	swLampState = HIGH;
		else swLampState = LOW;
		digitalWrite(swRaspPiLampPin, swLampState);
	}
}//  ----  end of SW rasberry pi  Lamp routine ---


//  ----- LIGHTS LAMP routine  **************************
void lightsLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{
	if (rate == 0) {
		digitalWrite(lightsSwLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(lightsSwLampPin, 1);
		return;
	}

	else if (rate == 2)          lightsLampRate = lampTimerSlow;
	else if (rate == 3)          lightsLampRate = lampTimerMid;
	else if (rate == 4)          lightsLampRate = lampTimerFast;


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
		digitalWrite(lightsSwLampPin, lightsLampState);
	}
}//  ----  end of LIGHTS Lamp routine ---




//  ----  STARTER LAMP routine    *****************************************
void starterLamp(int rate)   // ---- rate - 0 off, 1 fast, 2  slow, 3 middle  
{

	if (rate == 0) {
		digitalWrite(startEngineLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(startEngineLampPin, 1);
		return;
	}

	else if (rate == 2)          starterLampRate = lampTimerSlow;
	else if (rate == 3)          starterLampRate = lampTimerMid;
	else if (rate == 4)          starterLampRate = lampTimerFast;


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
		digitalWrite(startEngineLampPin, starterSwLampState);
	}
}//  ----  end of starter Lamp routine ---


