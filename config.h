/*
   ------------  config file - all Pins list and all functions and .INO routines  -------------

   https://content.arduino.cc/assets/Pinout-Mega2560rev3_latest.pdf

*/

// ---- MP3 shield ----------  Not flexible ----
#define mp3ResetPin		   43      // Xreset pin (unused!)
#define mp3CsPin           53      // XCS chip select pin (output)
#define mp3DcsPin          40      // XDCS   data/command select pin (output)
#define mp3SDCardsPin      49      // CS  SD Card chip select pin
#define mp3DreqPin         21      // DREQ data request, ideally an Interrupt pin
// ---  SPI ------
#define mp3ClkPin          52      // SCK SPI Clock, shared with SD card
#define mp3MisoPin         50      // MISO Input data, from VS1053/SD card
#define mp3MosiPin         51      // MOSI Output data, to VS1053/SD card

// ---  I N P U T S   Motor 2 sides  -------

#define btm_AirPin          A1     // sw Airpump
#define btm_WaterPin        A2     // sw water pamp
#define battaryDeadPin      A3     // battary cutout relay
#define btm_FanPin          A4     // fan motor radiator
#define btm_neoMotorPin     A5	   // neopixls motor 

// ---  I N P U T S  Driver panel---------------

#define btmStartEngPin     A6      // Bottom  start or second press - stop motor and all functions on the motor
#define btmHornPin         A7      // Bottom  horn each press another playing of mp3 file from horn librery 
#define wheelBtm1Pin	   A8      // Bottom  1 select file to mps from path/1 librery 
#define wheelBtm2Pin       A9      // Bottom   2 select file to mps from path/1 librery  
#define wheelBtm3Pin       A10     // Bottom    3 select file to mps from path/1 librery 
#define sw_L_turnPin       A12     // switch turn left 
#define sw_R_turnPin       A11     // switch turn right
#define gearRevPin         A13     // gear forward    
#define gearFwPin          A14     // gear reverse 
#define drivePedalPin      A15     // push pedal drive frw rev.
#define btmLightsPin	   48	   // front high lights  
#define btmRaspbryPin	   45	   // bottom rasbery pi right to the screen   

// ---  O U T P U T S   ----------
#define valve1Pin          26      // LED 1+2 pin  // blinking motor valve pin number 
#define valve2Pin          27             

#define turnL_Pin          28      // 8 relay  board - 12 volt  
#define turnR_Pin          29
#define revLightPin        30
#define waterPumpRelayPin  32
#define fanMotorRelayPin   33
#define shutDownRelayPin   34      // On by tractor key switch, Off by shut down timer  set at main routine
#define LightsRelayPin     35      // On only when motor running to save battary 
#define airPumpRelayPin	   36
#define drvMotorEnPin1     37
#define drvMotorEnPin2     37
#define drvMotorPwmPin1    38
#define drvMotorPwmPin2    39	  // 40 ocupied - MP3 


#define startEngineLampPin 41	  // led whithin lamp
#define lightsSwLampPin    42
#define swRaspPiLampPin    46     // 43 ocupied - MP3,  raspberry Pi lamp in sw right to the screen
#define	redLightDrivePin   44	  // Blink while driving for warnning from behind,  Off - while standin to save battary
#define waterSwLampPin	   22
#define airSwLampPin	   23


// ----   PWM pins 2-13  -----------

#define neoMotorPin        2     //2 data pin for engine NeoPixel   - PWM  2-13 !!!!!!!!!!!!!!!
#define neoTurnLPin        3     //3 data pin for left vinkers front and back NeoPixel- PWM
#define neoTurnRPin        4     //4 data pin for right vinkers front and back NeoPixel - PWM
#define neoInteriorPin     5     //5 data pin for interior NeoPixel - PWM
#define neoBLPin           7     //4 data pin for right vinkers front and back NeoPixel - PWM
#define neoBRPin           8     //4 data pin for right vinkers front and back NeoPixel - PWM
#define shutDownRelayPin   6	 // self maintian relay, on by tractor key and off by shut down timer 

// --- declare  All functions and .INI routines  ----

// neopixles 
void neopixleIni				();				
void neopixlesUpdate			();
void neopixleLturnComplete	    ();
void neopixleRturnComplete	    ();
void neopixleIntiriorComplete	();
void neopixleMotorComplete      ();

void neoInteriorShow(int colorVar)   ;
void neoTurn_Rshow  (int colorVar)   ;
void neoTurn_Lshow  (int colorVar)   ;
void neoMotorShow   (int neoNumber)  ;

void neoStopAll()     ;
void neoMotorStop()   ;
void neoTurnLStop()   ;
void neoTurnRStop()   ;
void neoInteriorStop();

void neopixleLturnComplete()    ;
void neopixleRturnComplete()    ;
void neopixleIntiriorComplete() ;
void neopixleMotorComplete()    ;

//  -- MP-3 
void mp3Ini			()			  ;					
void playSound		(char* path)  ;
void playTillEndSound(char* path) ;

void nextSong		(int i);
void nextVocal		(int i);
void nextStarter	(int i);
void nextHorn		(int i);
void nextCommand	(int i);
void nextStory		(int i);
void nextReverse    (int I);

// all the rest 
void valvesIni		();
void valves			(bool valvesOn, bool valvesFast);
void readBottomsIni	();
void readBottoms	();

// pumps & fan
void pumpsIni		();
void fanMotor		(int fanSpeed);
void waterMotor		(int waterSpeed);
void airMotor		(int airSpeed);

void driveIni		();
void Drive			(int drvFlag, int speed);
void stopMotors		();
void driveReverse	(int pwm);
void driveForward	(int pwm);
void lightRedBrake	();

void action			();

void shutDownIni	();
void shutDown();

void turnIni		();
void vinkers		(bool turnLOn, bool turnROn, bool turnFast);     
void turnLights		(bool L, bool R);

void lampsIni		();
void starterLamp	(int rate);
void lightsLamp		(int rate);
void swRasbPiLamp	(int swRate);
void swWaterLamp    (int swRate);
void swAirLamp      (int swRate);

//   ************  END OF CONFIG ROUTINE *************