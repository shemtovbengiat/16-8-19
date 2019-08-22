/*
   ------------  config file - all Pins list and all functions and .INO routines  -------------
*/

// ---- MP3 shield --------------
#define SHIELD_RESET  43      // VS1053 reset pin (unused!)
#define SHIELD_CS     53      // VS1053 chip select pin (output)
#define SHIELD_DCS    40      // VS1053 Data/command select pin (output)
#define CARDCS        49      // Card chip select pin
#define DREQ          20      // VS1053 Data request, ideally an Interrupt pin
// ---  SPI ------
#define CLK           52      // SPI Clock, shared with SD card
#define MISO          50      // Input data, from VS1053/SD card
#define MOSI          51      // Output data, to VS1053/SD card

// ---  I N P U T S  Panel on motor side plate -------
#define btm_Air       A1     //sw Airpump
#define btm_Wtr       A2     //sw water pamp
#define btm_Vlv       A3     //sw vlaves-lights red
#define btm_Fan       A4     // rdiator fan motor 
#define btm_neoMtr    A5    // neopixls motor 

// ---  I N P U T S  driver panel---------------
#define btmStart      A8      // Bottom  start or second press - stop motor and all functions on the motor
#define btmHorn       A7      // Bottom  horn each press another playing of mp3 file from horn librery 
#define wheelBtm1     A3      // Bottom  1 select file to mps from path/1 librery 
#define wheelBtm2     A9      // Bottom   2 select file to mps from path/1 librery  
#define wheelBtm3     A10       // Bottom    3 select file to mps from path/1 librery 
#define btm_l         A7    //push bottom left joystick
#define btm_r         A6    //push bottom right
#define btm_Fw        A13    //push bottom up   
#define btm_Rev       A14    //push bottom down 
#define drivePedal    A15    //push pedal drive frw rev.

// ---  O U T P U T S   ----------
#define valve1          26      // LED 1+2 pin  // blinking motor valve pin number 
#define valve2          27             

#define turnL           A1     // turn signal left slow standing / fast at drive / warning light both
#define turnR           A2

#define ldrmEn1Pin      30
#define ldrmEn2Pin      31
#define ldrmPwm1Pin     32
#define ldrmPwm2Pin     33

#define rdrmEn1Pin      34
#define rdrmEn2Pin      35
#define rdrmPwm1Pin     36
#define rdrmPwm2Pin     37

#define reversePin      A1
#define redBrakesPin    A2


#define neoMotorPin     10     //data pin for engine NeoPixel   - PWM
#define neoTurnLPin     45    //data pin for left vinkers front and back NeoPixel- PWM
#define neoTurnRPin     46    //data pin for right vinkers front and back NeoPixel - PWM
#define neoInteriorPin  10     //data pin for interior NeoPixel - PWM
#define neoExhaostPin   11     //data pin for exhaost NeoPixel ring - PWM
#define neoHeadPin		12     //?  data pin for head NeoPixel  - PWM



// --- declare All functions and .INO routines  ----

void neopixleIni();
void neoStopAll();

void neoMotorStop();
void neoTurnRStop();
void neoTurnLStop();
void neoExhaostStop();
void neoHeadStop();
void neoInteriorStop();

void neoMotorShow();
void neoTurrnRShow();
void neoTurnLShow();
void neoExhaostShow();
void neoHeadShow();
void neoInteriorShow();

void mp3Ini();
void playSound(char* path);

void nextSong(int i);
void nextVocal(int i);
void nextStarter(int i);
void nextHorn(int i);
void nextCommand(int i);

void motorValvesIni();
void motorValves(bool valvesOn, bool valvesFast);
void readBottomsIni();
void readBottoms();
void pumpsIni();
void pumps(bool pumpsOn, int pumpsFast);
void lightValves();
void action();
void turnIni();
void vinkers(bool turnLOn, bool turnROn, bool turnFast);
//void turnLights();
void driveini();

