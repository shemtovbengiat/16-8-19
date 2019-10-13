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

// ---  I N P U T S   Motor 2 sides  -------

#define btm_AirPin          A1     //sw Airpump
#define btm_WaterPin        A2      //sw water pamp
#define btm_VlvPin          A3     //sw vlaves-lights red
#define btm_FanPin          A4     // rdiator fan motor 
#define btm_neoMotrPin      A5     // neopixls motor 

// ---  I N P U T S  Driver panel---------------

#define btmStartEngPin     A6      // Bottom  start or second press - stop motor and all functions on the motor
#define btmHornPin         A7      // Bottom  horn each press another playing of mp3 file from horn librery 
#define wheelBtm1Pin	   A8      // Bottom  1 select file to mps from path/1 librery 
#define wheelBtm2Pin       A9      // Bottom   2 select file to mps from path/1 librery  
#define wheelBtm3Pin       A10     // Bottom    3 select file to mps from path/1 librery 
#define sw_L_turnPin       A11     // switch turn left 
#define sw_R_turnPin       A12     // switch turn right
#define gearFwPin          A13     // gear forward    
#define gearRevPin         A14     // gear reverse 
#define drivePedalPin      A15     // push pedal drive frw rev.
#define btmLightsPin	   48	   // front high lights 

// ---  O U T P U T S   ----------
#define valve1Pin          26      // LED 1+2 pin  // blinking motor valve pin number 
#define valve2Pin          27             

#define turnL_Pin          28      // 8 relay  board - 12 volt  
#define turnR_Pin          29
#define reversePin         30
#define redBrakesPin       31
#define waterPumpRelayPin  32
#define airPumpRelayPin    33
#define radiatorRelayPin   34
#define doNotKnowRelay        35  // fix 

#define drvMotorEnPin1     36
#define drvMotorEnPin2     37
#define drvMotorPwmPin1    38
#define drvMotorPwmPin2    39	// 40, 43  ocupied !


#define startEngineLampPin 41	  // led whithin lamp
#define lightsSwLampPin    42
#define swLampPin          44     // special sw right to screen

// ----   PWM pins 2-13  -----------

#define neoMotorPin        2     //data pin for engine NeoPixel   - PWM
#define neoTurnLPin        3    //data pin for left vinkers front and back NeoPixel- PWM
#define neoTurnRPin        4    //data pin for right vinkers front and back NeoPixel - PWM
#define neoInteriorPin     5     //data pin for interior NeoPixel - PWM

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
/*

void encoderIni();  // -- Encoder for volume
void readEncoder();

void A_RISE();
void B_RISE();

void A_FALL();
void B_FALL();
*/