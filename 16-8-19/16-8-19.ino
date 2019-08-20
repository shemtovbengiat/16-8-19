//  ------------   main file --------------------

#define DEBUG

#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <btsmotordriver.h>
#include <Adafruit_NeoPixel.h>

// ----- G L O B A L    V A R I A B L E S  ----------------

volatile int motorOn = 0;              // 1 ! true = start engine slow, light valves, pumps, fan and running mp3 starter sound. motorOn=0 all OFF
volatile int drivePedalOn = 0;         // pedal on = 1=driving FRW REV 0= STOP 

volatile int startBtmNumber = 0;            // starter sounds file # 0-18  in sd card, randomly selected when start bottom pushed

volatile int forwardOn = 0;            // forward on = 1 = drive with pedalOn = 1 together
volatile int reverseOn = 0;            // reverse on = 1 = drive with pedalOn = 1 together

volatile int turnROn = 0;        // right signal "vinker" = 1 = blinking,     0> off
volatile int turnLOn = 0;         // left signal "vinker" = 1 = blinking,     0> off
volatile int turnFast = 0;

volatile bool driveEnable = 0;         // safty switch both first d or r and pedal will allow driving.!!   action routine

volatile int wheelBottom1Pushed = 0;   // wheel Bottom  # 1 Pushed > play random file from 1/ librery
volatile int wheelBottom2Pushed = 0;   // wheel Bottom  # 2 Pushed > play random file from 2/ librery
volatile int wheelBottom3Pushed = 0;   // wheel Bottom  # 3 Pushed > play random file from 3/ librery

volatile int steeringBtmBlueNumber = 0;
volatile int steeringBtmRedNumber = 0;
volatile int steeringBtmBlackNumber = 0;

volatile int steeringBtmBlueOld = 0;
volatile int steeringBtmRedOld = 0;
volatile int steeringBtmBlackOld = 0;

volatile int hornPushed = 0;           // each time horn bottom pushed we get random number to play MP3 another file from horn librery
volatile int hornBtmNumber = 0;
volatile int hornBtm = 0;
volatile int hornBtmOld = 0;

volatile bool isMP3On = false;
volatile int  driveSpeed = 100;				// to be set by the speed encoder potentiometer 0 - 255 full speed

int songCount = 0;

//  -------   S E T U  P      ROUTINE  -------------

void setup()
{
	Serial.begin(9600);
	randomSeed(analogRead(0));    // for not requering random numbers

#if defined(DEBUG)
	Serial.println("DEBUG mode!");
#endif

	mp3Ini();       //  --------O N L Y  initilazition routins in SETUP 
	motorValvesIni();
	readBottomsIni();
	pumpsIni();
	turnIni();
	vinkers(0, 0, 0);                        // no vinkers
	driveIni();
	neopixleIni();

	playSound("TRACK02.MP3");
}
//---  end of  SETUP routine  ---

//  -------   LOOP     ROUTINE  ---------------
void loop() {

	readBottoms();
	action();
	runNeoPixles();

}
// ---  END of loop routine  -----

