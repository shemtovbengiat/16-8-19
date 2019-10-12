/*
   ------------  config file - all Pins list and all functions and .INO routines  -------------
*/

// ---- MP3 shield ----------  Not flexible ----
#define mp3ResetPin		   43      // VS1053 reset pin (unused!)
#define mp3CsPin           53      // VS1053 chip select pin (output)
#define mp3DcsPin          40      // VS1053 Data/command select pin (output)
#define mp3SDCardsPin      49      // Card chip select pin
#define mp3DreqPin         20      // VS1053 Data request, ideally an Interrupt pin
// ---  SPI ------
#define mp3ClkPin          52      // SPI Clock, shared with SD card
#define mp3MisoPin         50      // Input data, from VS1053/SD card
#define mp3MosiPin         51      // Output data, to VS1053/SD card

// ---  I N P U T S  Panel on motor side plate -------
#define btm_AirPin          A15     //sw Airpump
#define btm_WaterPin        A15     //sw water pamp
#define btm_VlvPin          A15 //sw vlaves-lights red
#define btm_FanPin          A15     // rdiator fan motor 
#define btm_neoMotrPin      A15    // neopixls motor 

// ---  I N P U T S  Main driver Panel  -------

#define btmLightsPin		A13	   // front high lights 

// ---  I N P U T S  Driver panel---------------
#define btmStartPin        A8      // Bottom  start or second press - stop motor and all functions on the motor
#define btmHornPin         A7      // Bottom  horn each press another playing of mp3 file from horn librery 
#define wheelBtm1Pin     A15     // Bottom  1 select file to mps from path/1 librery 
#define wheelBtm2Pin       A2      // Bottom   2 select file to mps from path/1 librery  
#define wheelBtm3Pin       A5    // Bottom    3 select file to mps from path/1 librery 
#define btm_L_pin          30      //push bottom left joystick
#define btm_R_pin          A6      //push bottom right
#define btm_FwPin        A15     //push bottom up   
#define btm_RevPin        A14     //push bottom down 
#define drivePedalPin     A15     //push pedal drive frw rev.

/*
const unsigned int pinA = 3;	// Used for generating interrupts using CLK signal
const unsigned int pinB = 2;	// Used for reading DT signal

const unsigned int swEncoder = A9;	// Used for reading DT signal


*/
//  ----- I N P U T S  Encoder sw for Volum control
//#define encoderDataPin      3
//#define encoderClockPin     2		//all 3 flexible
//#define pinA      3
//#define pinB      2		//all 3 flexible
//#define encoderSwitchPin   A9

// ---  O U T P U T S   ----------
#define valve1Pin        A15    // LED 1+2 pin  // blinking motor valve pin number 
#define valve2Pin          27             

#define turnL_Pin          A1    // turn signal left slow standing / fast at drive / warning light both
#define turnR_Pin          30

#define ldrmEn1Pin         30
#define ldrmEn2Pin         31
#define ldrmPwm1Pin        32
#define ldrmPwm2Pin        33

#define rdrmEn1Pin         34
#define rdrmEn2Pin         35
#define rdrmPwm1Pin        36
#define rdrmPwm2Pin        37

#define reversePin         A5
#define redBrakesPin     0

#define startlampPin       A3
#define wtrPumpLampPin     A15
#define airPumpLampPin      7

#define neoMotorPin        10     //data pin for engine NeoPixel   - PWM
#define neoTurnLPin        45    //data pin for left vinkers front and back NeoPixel- PWM
#define neoTurnRPin        46    //data pin for right vinkers front and back NeoPixel - PWM
#define neoInteriorPin     10     //data pin for interior NeoPixel - PWM
#define neoExhaostPin      11     //data pin for exhaost NeoPixel ring - PWM
#define neoHeadPin	       12     //?  data pin for head NeoPixel  - PWM

#define swLampPin		   A10	  //  lamps within switches.
#define starterSwLampPin   A11
#define lightSwLampPin	   A12

// --- declare  All functions and .INO routines  ----

void neopixleIni();				// neopixles 
void neoStopAll();

void neoMotorStop();
void neoTurnRStop();
void neoTurnLStop();
void neoExhaostStop();
void neoHeadStop();
void neoInteriorStop();

void neoMotorShow();
void neoExhaostShow();
void neoHeadShow();
void neoInteriorShow(int c);

void mp3Ini();					//  -- MP-3 
void playSound(char* path);

void nextSong(int i);
void nextVocal(int i);
void nextStarter(int i);
void nextHorn(int i);
void nextCommand(int i);

void encoderIni();  // -- Encoder for volume 
void readEncoder();

void valvesIni();
void lampsIni();

// all the rest 
void valves(bool valvesOn, bool valvesFast);
void readBottomsIni();
void readBottoms();
void pumpsIni();
void pumps(bool pumpsOn, int pumpsFast);
void lightValves();
void action();
void turnIni();
void turnLights(bool L, bool R);
void vinkers(bool turnLOn, bool turnROn, bool turnFast);     
void driveIni();

void lampsIni();
void starterLamp(int rate);
void switchLamp(int rate);
void lightsLamp(int rate);
void set3Lamps(int sw, int lght, int  start);

void A_RISE();
void B_RISE();

void A_FALL();
void B_FALL();