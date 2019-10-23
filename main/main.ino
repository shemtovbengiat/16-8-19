//  ------------   main file --------------------


#include "config.h"
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>


#include <Wire.h>


//   -----   MP 3 -----------
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(mp3ResetPin, mp3CsPin, mp3DcsPin, mp3DreqPin, mp3SDCardsPin);

// ------  NeoPixles -  constructing 6 classs for each neopixle, ---      pin # of strip in config !!! ----
#define neoMotorNo		10     // 42  temp 19 number of leds for engine NeoPixel ;
#define neoTurnLNo	  	12
#define neoTurnRNo	  	12
#define neoInteriorNo   12     //number of leds for interior NeoPixel

Adafruit_NeoPixel neoMotor =    Adafruit_NeoPixel(neoMotorNo,    neoMotorPin,    NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoTurnL =    Adafruit_NeoPixel(neoTurnLNo,    neoTurnLPin,    NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoTurnR =    Adafruit_NeoPixel(neoTurnRNo,    neoTurnRPin,    NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoInterior = Adafruit_NeoPixel(neoInteriorNo, neoInteriorPin, NEO_GRB + NEO_KHZ800);


// ----- G L O B A L    V A R I A B L E S  ----------------

volatile int motorOn =           0;       // 1 ! true = start engine slow, light valves, pumps, fan and running mp3 starter sound. motorOn=0 all OFF
volatile int drivePedalOn =      0;       // pedal on = 1=driving FRW REV 0= STOP 

volatile int startBtmNumber =    0;       // starter sounds file # 0-18  in sd card, randomly selected when start bottom pushed
volatile int startBtmNumberOld = 0;       // to avoide repeting

volatile int forwardOn = 0;               // forward on = 1 = drive with pedalOn = 1 together
volatile int reverseOn = 0;               // reverse on = 1 = drive with pedalOn = 1 together

volatile int turnROn =      0;			  // right signal "vinker" = 1 = blinking,     0> off
volatile int turnLOn =      0;			  // left signal "vinker" = 1 = blinking,     0> off
volatile int turnFast =     0;

volatile bool driveEnable = 0;            // safty switch both first d or r and pedal will allow driving.!!   action routine

volatile int wheelBottom1Pushed = 0;      // wheel Bottom  # 1 Pushed > play random file from 1/ librery
volatile int wheelBottom2Pushed = 0;      // wheel Bottom  # 2 Pushed > play random file from 2/ librery
volatile int wheelBottom3Pushed = 0;      // wheel Bottom  # 3 Pushed > play random file from 3/ librery

volatile int steeringBtmBlueNumber =  0;
volatile int steeringBtmRedNumber =   0;
volatile int steeringBtmBlackNumber = 0;

volatile int steeringBtmBlueOld =   0;
volatile int steeringBtmRedOld =    0;
volatile int steeringBtmBlackOld =  0;

volatile int hornPushed =    0;           // each time horn bottom pushed we get random number to play MP3 another file from horn librery
volatile int hornBtmNumber = 0;
volatile int hornBtm =       0;
volatile int hornBtmOld =    0;


volatile bool isMP3On =      0;
int songCount =              0;

										// 8-2019 added 7  functions motor, switchs 
volatile bool airPumpOn =       0;
volatile bool waterPumpOn =     0;
volatile bool battaryDeadOn =   0;
volatile bool fanMotorOn =      0;
volatile bool neoPixleMotorOn = 0;
volatile bool lightsOn =        0;
volatile bool swRasbPiOn =		0;

volatile int neoMotorNumber =	 0;     // no. of times bottom to pushed in a second to  decide patern of behavieor
volatile int airPumpNumber =     0;
volatile int waterPumpNumber =   0;
volatile int fanMotorNumber =    0;


volatile int airSpeed =   0;				//   -----   variable to set beeps of Pumps air,  water and fan
volatile int fanSpeed =   0;
volatile int waterSpeed = 0;

volatile bool shutDownRelayOn =    0;			// 1=shut down, xx min. passed no action !! 0= system good
volatile bool doSomethingCrazy =   0;			// 1=do somthing random 1-10 at random time ,  0= do all the rest

//  ------   Timing / Twicking 
volatile int  driveSpeed     =   100;		// to be set by the speed encoder potentiometer 0 - 255 full speed
 
volatile int  volume		 =    20;		// 0- max volume   80 - min volume 

volatile int  shutDownTimer  =     1;		// 5 min. ~ time (min.)if no action --> shutdown & disconnect power. recycle key needed !
volatile int  maxTimeToInterupt = 10;		// 120 sec. ~ maxTimeToInterupt (seconds) to make RANDOM crazy things see shutdown routine
volatile int  crazyNumber		=  0;		// 1-10 "x"-massage # X --> in sd\massages\x.mp3 


volatile int  lampTimerFast  =    50;	    // 60  ms  fast
volatile int  lampTimerMid   =    50;	    // 120 ms  middle speed  
volatile int  lampTimerSlow  =  1000;    	// 200 ms  slow

volatile int  waterTimerFast =     50;      // fine tuning of the motor beeps beep beep...
volatile int  waterTimerSlow =    200;      // 10 fast 200 slow / ms
volatile int  airTimerFast	 =     50;
volatile int  airTimerSlow   =    200;
volatile int  fanTimerFast   =     50;    
volatile int  fanTimerSlow   =    200;

//  ************************************************
//  -------   S E T U  P      routine  -------------
//  ************************************************
void setup()
{
	Serial.begin(115200);
	randomSeed(analogRead(A0));    // for not requering random numbers
	Serial.println(analogRead(A0));
	/*
	#if defined(DEBUG)
		Serial.println("DEBUG mode!");
	#endif
*/
	shutDownIni();		//  --------O N L Y  initilazition routins in SETUP 
	mp3Ini();       
	valvesIni();
	readBottomsIni();
	pumpsIni();
	turnIni();
	driveIni();
	neopixleIni();
	lampsIni();
	
	playSound("TRACK02.MP3");

};//---  end of  SETUP routine  ---

//  **************************************
//  -------   Main LOOP  routine  ---=----
//  **************************************
void loop() 
{
	readBottoms();
	action();
	shutDown();
};// ---  END of loop routine  -----

