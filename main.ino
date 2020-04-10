//  ------------   main file --------------------

#include "config.h"  // must have decleration of ALL void(XX) functions in ALL ino parts !!
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

//   -----   MP 3 -----------
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(mp3ResetPin, mp3CsPin, mp3DcsPin, mp3DreqPin, mp3SDCardsPin);



// ------  NeoPixles -  constructing 4 classs for each neopixle, ---      pin # of strip in config !!! ----
#define neoMotorNo		12     // number of leds in engine = 42  temp-12 pc.  19/11/19 
#define neoTurnLNo	  	5
#define neoTurnRNo	  	6
#define neoInteriorNo   12     //number of leds for interior NeoPixel


Adafruit_NeoPixel neoMotor =	 Adafruit_NeoPixel(neoMotorNo, neoMotorPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoTurnL =	 Adafruit_NeoPixel(neoTurnLNo, neoTurnLPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoTurnR =	 Adafruit_NeoPixel(neoTurnRNo, neoTurnRPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neoInterior =	 Adafruit_NeoPixel(neoInteriorNo, neoInteriorPin, NEO_GRB + NEO_KHZ800);


// ----- G L O B A L    V A R I A B L E S  ----------------

volatile int motorOn				= 0;       // 1 ! true = start engine slow, light valves, pumps, fan and running mp3 starter sound. motorOn=0 all OFF
volatile int drivePedalOn			= 0;       // pedal on = 1=driving FRW REV 0= STOP 

volatile int startBtmNumber			= 0;       // starter sounds file # 0-18  in sd card, randomly selected when start bottom pushed
volatile int startBtmNumberOld		= 0;       // to avoide repeting

volatile int forwardOn				= 0;               // forward on = 1 = drive with pedalOn = 1 together
volatile int reverseOn				= 0;               // reverse on = 1 = drive with pedalOn = 1 together

volatile int reverseNumber			= 0;		  // 1-4 reverse sounds MP# in reverse sd card diractory
volatile int turnROn				= 0;			  // right signal "vinker" = 1 = blinking,     0> off
volatile int turnLOn				= 0;			  // left signal "vinker" = 1 = blinking,     0> off
volatile int turnFast				= 0;

volatile bool driveEnable			= 0;            // safty switch both first d or r and pedal will allow driving.!!   action routine

volatile int wheelBottom1Pushed		= 0;      // wheel Bottom  # 1 Pushed > play random file from 1/ librery
volatile int wheelBottom2Pushed		= 0;      // wheel Bottom  # 2 Pushed > play random file from 2/ librery
volatile int wheelBottom3Pushed		= 0;      // wheel Bottom  # 3 Pushed > play random file from 3/ librery

volatile int steeringBtmBlueNumber	= 0;
volatile int steeringBtmRedNumber	= 0;
volatile int steeringBtmBlackNumber	= 0;

volatile int steeringBtmBlueOld		= 0;
volatile int steeringBtmRedOld		= 0;
volatile int steeringBtmBlackOld	= 0;

volatile int hornPushed				= 0;           // each time horn bottom pushed we get random number to play MP3 another file from horn librery
volatile int hornBtmNumber			= 0;
volatile int hornBtm				= 0;
volatile int hornBtmOld				= 0;

volatile bool noSwitchPushed   = 0;		  // 1 = long time no action time to go to sleep, 0= a switch was pushed within time to shut down 
volatile bool isMP3On				= 0;
int songCount						= 0;

// 8-2019 added 7  functions motor, switchs 
volatile bool airPumpOn			= 0;
volatile bool waterPumpOn		= 0;
volatile bool battaryDeadOn		= 0;
volatile bool fanMotorOn		= 0;
volatile bool neoPixleMotorOn	= 0;
volatile bool lightsOn			= 0;
volatile bool swRasbPiOn		= 0;

volatile int neoMotorNumber		= 0;     // no. of times bottom to pushed in a second to  decide patern of behavieor
volatile int airPumpNumber		= 0;
volatile int waterPumpNumber	= 0;
volatile int fanMotorNumber		= 0;
volatile int swRasbPiNumber		= 0;

volatile int airSpeed			= 0;				//   -----   variable to set beeps of Pumps air,  water and fan
volatile int fanSpeed			= 0;
volatile int waterSpeed			= 0;

volatile bool shutDownRelayOn	= 0;			// 1=shut down, xx min. passed no action !! 0= system good
volatile bool doSomethingCrazy	= 0;			// 1=do somthing random 1-10 at random time ,  0= do all the rest
volatile bool massagePlayed		= 0;			// 

//  ------   Timing / Twicking 
volatile int  driveSpeed		= 100;		// 0- stop   255- full speed

volatile int  volume			= 20;		// 0- max volume   80 - min volume 

volatile int  shutDownTimer		= 2;		// 5 min. ~ time (min.)if no action --> shutdown & disconnect power. recycle key needed !see shutdown routine
volatile int  maxTimeToInterupt = 100;		// 120 sec. ~ time in seconds to make RANDOM crazy things 
volatile int  crazyNumber		= 0;		// 1-10 "x"-massage # X --> in sd\massages\x.mp3 


volatile int  lampTimerFast		= 50;	    // 60  ms  fast
volatile int  lampTimerMid		= 50;	    // 120 ms  middle speed  
volatile int  lampTimerSlow		= 1000;    	// 200 ms  slow

volatile int  waterTimerFast	= 50;      // fine tuning of the motor beeps beep beep...
volatile int  waterTimerSlow	= 500;      // 10 fast 200 slow / ms
volatile int  airTimerFast		= 50;
volatile int  airTimerSlow		= 500;
volatile int  fanTimerFast		= 50;
volatile int  fanTimerSlow		= 500;

volatile int  neoMotorScanRate	= 50;

//  ************************************************
//  -------   S E T U  P      routine  -------------
//  ************************************************
void setup()
{
	Serial.begin(115200);
	randomSeed(analogRead(A0));			// for not requering random numbers
	Serial.println(analogRead(A0));		

	shutDownIni();		//  --------O N L Y  initilazition routins in SETUP 
	mp3Ini();
	valvesIni();
	readBottomsIni();
	pumpsIni();
	turnIni();
	driveIni();
	neopixleIni();
	lampsIni();

	nextCommand(0);  //comnd/0.mp3 opening massage - Shalom Yuval... Tokyo 

};//---  end of  SETUP routine  ---

//  **************************************
//  -------   Main LOOP  routine  ---=----
//  **************************************
void loop()
{
	readBottoms();
	action();
	neopixlesUpdate();
	shutDown();
};// ---  END of loop routine         check below for neopixles !!!!!!! -----




// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE };
// Patern directions supported:
enum  direction { Forward, Revrs };

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class NeoPatterns : public Adafruit_NeoPixel
{
public:

	// Member Variables:  
	pattern  ActivePattern;  // which pattern is running
	direction Direction;     // direction to run the pattern

	unsigned long Interval;   // milliseconds between updates
	unsigned long lastUpdate; // last update of position

	uint32_t Color1, Color2;  // What colors are in use
	uint16_t TotalSteps;  // total number of steps in the pattern
	uint16_t Index;  // current step within the pattern

	void(*OnComplete)();  // Callback on completion of pattern

	// Constructor - calls base-class constructor to initialize strip
	NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void(*callback)())
		:Adafruit_NeoPixel(pixels, pin, type)
	{
		OnComplete = callback;
	}

	// Update the pattern
	void Update()
	{
		if ((millis() - lastUpdate) > Interval) // time to update
		{
			lastUpdate = millis();
			switch (ActivePattern)
			{
			case RAINBOW_CYCLE:
				RainbowCycleUpdate();
				break;
			case THEATER_CHASE:
				TheaterChaseUpdate();
				break;
			case COLOR_WIPE:
				ColorWipeUpdate();
				break;
			case SCANNER:
				ScannerUpdate();
				break;
			case FADE:
				FadeUpdate();
				break;
			default:
				break;
			}
		}
	}

	// Increment the Index and reset at the end
	void Increment()
	{
		if (Direction == Forward)
		{
			Index++;
			if (Index >= TotalSteps)
			{
				Index = 0;
				if (OnComplete != NULL)
				{
					OnComplete(); // call the comlpetion callback
				}
			}
		}
		else // Direction == REVERSE
		{
			--Index;
			if (Index <= 0)
			{
				Index = TotalSteps - 1;
				if (OnComplete != NULL)
				{
					OnComplete(); // call the comlpetion callback
				}
			}
		}
	}

	// Reverse pattern direction
	void Revrs()
	{
		if (Direction == Forward)
		{
			//Direction = Reverse;
			Index = TotalSteps - 1;
		}
		else
		{
			Direction = Forward;
			Index = 0;
		}
	}

	// Initialize for a RainbowCycle
	void RainbowCycle(uint8_t interval, direction dir = Forward)
	{
		ActivePattern = RAINBOW_CYCLE;
		Interval = interval;
		TotalSteps = 255;
		Index = 0;
		Direction = dir;
	}

	// Update the Rainbow Cycle Pattern
	void RainbowCycleUpdate()
	{
		for (int i = 0; i < numPixels(); i++)
		{
			setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
		}
		show();
		Increment();
	}

	// Initialize for a Theater Chase
	void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = Forward)
	{
		ActivePattern = THEATER_CHASE;
		Interval = interval;
		TotalSteps = numPixels();
		Color1 = color1;
		Color2 = color2;
		Index = 0;
		Direction = dir;
	}

	// Update the Theater Chase Pattern
	void TheaterChaseUpdate()
	{
		for (int i = 0; i < numPixels(); i++)
		{
			if ((i + Index) % 3 == 0)
			{
				setPixelColor(i, Color1);
			}
			else
			{
				setPixelColor(i, Color2);
			}
		}
		show();
		Increment();
	}

	// Initialize for a ColorWipe
	void ColorWipe(uint32_t color, uint8_t interval, direction dir = Forward)
	{
		ActivePattern = COLOR_WIPE;
		Interval = interval;
		TotalSteps = numPixels();
		Color1 = color;
		Index = 0;
		Direction = dir;
	}

	// Update the Color Wipe Pattern
	void ColorWipeUpdate()
	{
		setPixelColor(Index, Color1);
		show();
		Increment();
	}

	// Initialize for a SCANNNER
	void Scanner(uint32_t color1, uint8_t interval)
	{
		ActivePattern = SCANNER;
		Interval = interval;
		TotalSteps = (numPixels() - 1) * 2;
		Color1 = color1;
		Index = 0;
	}

	// Update the Scanner Pattern
	void ScannerUpdate()
	{
		for (int i = 0; i < numPixels(); i++)
		{
			if (i == Index)  // Scan Pixel to the right
			{
				setPixelColor(i, Color1);
			}
			else if (i == TotalSteps - Index) // Scan Pixel to the left
			{
				setPixelColor(i, Color1);
			}
			else // Fading tail
			{
				setPixelColor(i, DimColor(getPixelColor(i)));
			}
		}
		show();
		Increment();
	}

	// Initialize for a Fade
	void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = Forward)
	{
		ActivePattern = FADE;
		Interval = interval;
		TotalSteps = steps;
		Color1 = color1;
		Color2 = color2;
		Index = 0;
		Direction = dir;
	}

	// Update the Fade Pattern
	void FadeUpdate()
	{
		// Calculate linear interpolation between Color1 and Color2
		// Optimise order of operations to minimize truncation error
		uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
		uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
		uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;

		ColorSet(Color(red, green, blue));
		show();
		Increment();
	}

	// Calculate 50% dimmed version of a color (used by ScannerUpdate)
	uint32_t DimColor(uint32_t color)
	{
		// Shift R, G and B components one bit to the right
		uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
		return dimColor;
	}

	// Set all pixels to a color (synchronously)
	void ColorSet(uint32_t color)
	{
		for (int i = 0; i < numPixels(); i++)
		{
			setPixelColor(i, color);
		}
		show();
	}

	// Returns the Red component of a 32-bit color
	uint8_t Red(uint32_t color)
	{
		return (color >> 16) & 0xFF;
	}

	// Returns the Green component of a 32-bit color
	uint8_t Green(uint32_t color)
	{
		return (color >> 8) & 0xFF;
	}

	// Returns the Blue component of a 32-bit color
	uint8_t Blue(uint32_t color)
	{
		return color & 0xFF;
	}

	// Input a value 0 to 255 to get a color value.
	// The colours are a transition r - g - b - back to r.
	uint32_t Wheel(byte WheelPos)
	{
		WheelPos = 255 - WheelPos;
		if (WheelPos < 85)
		{
			return Color(255 - WheelPos * 3, 0, WheelPos * 3);
		}
		else if (WheelPos < 170)
		{
			WheelPos -= 85;
			return Color(0, WheelPos * 3, 255 - WheelPos * 3);
		}
		else
		{
			WheelPos -= 170;
			return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
		}
	}
};

NeoPatterns neopixleLturn(neoTurnLNo, neoTurnLPin, NEO_GRB + NEO_KHZ800, &neopixleLturnComplete);
NeoPatterns neopixleRturn(neoTurnRNo, neoTurnRPin, NEO_GRB + NEO_KHZ800, &neopixleRturnComplete);
NeoPatterns neopixleIntirior(neoInteriorNo, neoInteriorPin, NEO_GRB + NEO_KHZ800, &neopixleIntiriorComplete);
NeoPatterns neopixleMotor(neoMotorNo, neoMotorPin, NEO_GRB + NEO_KHZ800, &neopixleMotorComplete);

