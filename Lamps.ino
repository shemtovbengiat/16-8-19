/*
    ----- LAMPS routine   - timers to drive  slow or fast rate  for the swithces lamp 12v
	----- starter sw lights sw and raspberry sw, called form action routine/
	---- 
*/

int starterSwLampState		= 0;                   
int swLampState				= 0;
int lightsLampState			= 0;
int waterSwLampState		= 0;
int airSwLampState			= 0;


unsigned long previousStrtSwLampMs		 = 0;
unsigned long previousSwLampMs			 = 0;
unsigned long previousLightsSwLampMS	 = 0;
unsigned long previousWaterSwLampMS		 = 0;
unsigned long previousAirSwLampMS		 = 0;


unsigned long currentStrtSwLampMs   = 0;
unsigned long currentSwLampMs       = 0;
unsigned long currentLightsSwLampMS = 0;
unsigned long currentWaterSwLampMS  = 0;
unsigned long currentAirSwLampMS    = 0;


long starterLampRate ;				   // for internal use       
long swLampRate      ;				   // for internal use       
long lightsLampRate  ;			       // for internal use       
long waterLampRate   ;			       // for internal use       
long airLampRate     ;			       // for internal use       

									   
// ---------------  Lamps in switchs   Initialization  in SETUP routine    --------

void lampsIni()
{
	pinMode(startEngineLampPin,  OUTPUT);             
	pinMode(swRaspPiLampPin,	 OUTPUT);
	pinMode(lightsSwLampPin,     OUTPUT);
	pinMode(waterSwLampPin,      OUTPUT);
	pinMode(airSwLampPin,        OUTPUT);
}
//  ----- end of Ini routine 

// Water and AIR switch pumps lamps are connected to motors relays direct 


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
		else
		{
			swLampState = LOW;
		}
	digitalWrite(swRaspPiLampPin, swLampState);
	}
}//  ----  end of SW rasberry pi  Lamp routine ---


//  ----- LIGHTS LAMP routine  **************************
void lightsLamp(int rate)   // - rate = 0-off, 1-On
{
	if (rate == 0) {
		digitalWrite(lightsSwLampPin, 0);
		return;
	}
	else if (rate == 1) {
		digitalWrite(lightsSwLampPin, 1);
		return;
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


//  ----  Water switch LAMP routine    *****************************************
void swWaterLamp(int swRate)   // ---- rate = 0-off, 1-on, 2-slow, 3-mid, 4-fast   
{
	if (swRate == 0) {
		digitalWrite(waterSwLampPin, 0);
		return;
	}
	else if (swRate == 1) {
		digitalWrite(waterSwLampPin, 1);
		return;
	}
	else if (swRate == 2)   waterLampRate = lampTimerSlow;
	else if (swRate == 3)   waterLampRate = lampTimerMid;


	unsigned long currentWaterSwLampMS = millis();
	if (currentWaterSwLampMS - previousWaterSwLampMS >= waterLampRate)
	{
		previousWaterSwLampMS = currentWaterSwLampMS;

		if (waterSwLampState == LOW)	waterSwLampState = HIGH;
		else
		{
			waterSwLampState = LOW;
		}
		digitalWrite(waterSwLampPin, waterSwLampState);
	}
}//  ----  end of  Water SW Lamp routine ---

//  ----  Air switch LAMP routine    *****************************************
void swAirLamp(int swRate)   // ---- rate = 0-off, 1-on, 2-slow, 3-mid, 4-fast   
{
	if (swRate == 0) {
		digitalWrite(airSwLampPin, 0);
		return;
	}
	else if (swRate == 1) {
		digitalWrite(airSwLampPin, 1);
		return;
	}
	else if (swRate == 2)   airLampRate = lampTimerSlow;
	else if (swRate == 3)   airLampRate = lampTimerMid;


	unsigned long currentAirSwLampMS = millis();
	if (currentAirSwLampMS - previousAirSwLampMS >= airLampRate)
	{
		previousAirSwLampMS = currentAirSwLampMS;

		if (airSwLampState == LOW)	airSwLampState = HIGH;
		else
		{
			airSwLampState = LOW;
		}
		digitalWrite(airSwLampPin, airSwLampState);
	}
}//  ----  end of  Air SW Lamp routine ---


