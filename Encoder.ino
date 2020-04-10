

/*
 Rotary Encoder Demo
 rot-encode-demo.ino
 Demonstrates operation of Rotary Encoder
 Displays results on Serial Monitor
 DroneBot Workshop 2019
 https://dronebotworkshop.com

int  maxVolume =100;
int minVolume = 0;
uint8_t volume =10;

// Rotary Encoder Inputs
#define inputCLK 3
#define inputDT  2

int counter;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void encoderIni() {

	// Set encoder pins as inputs  
	pinMode(inputCLK, INPUT);
	pinMode(inputDT, INPUT);

	// Read the initial state of inputCLK
	// Assign to previousStateCLK variable
	previousStateCLK = digitalRead(inputCLK);

}

void readEncoder() 
{
	// Read the current state of inputCLK
	currentStateCLK = digitalRead(inputCLK);

	// If the previous and the current state of the inputCLK are different then a pulse has occured
	if (currentStateCLK != previousStateCLK)
	{

		// If the inputDT state is different than the inputCLK state then 
		// the encoder is rotating counterclockwise
		if (digitalRead(inputDT) != currentStateCLK) {
			counter = counter -5;
			if (counter < minVolume)	counter = minVolume;
		}
		else {
			// Encoder is rotating clockwise
			counter=counter+5;
			if (counter > maxVolume)	counter = maxVolume;
		}
	}
		Serial.print(" conter = ");
		Serial.println(counter);
		volume = counter;
	
	// Update previousStateCLK with the current state
	previousStateCLK = currentStateCLK;
}








int pulses, A_SIG = 0, B_SIG = 1;



void encoderIni() {
	attachInterrupt(pinA, A_RISE, RISING);
	attachInterrupt(pinB, B_RISE, RISING);
//	Serial.begin(115200);
}//setup




void readEncoder() {

	if (pulses < 0)		pulses = 0;
	if (pulses > 100)	pulses = 100;

	Serial.println(pulses);
	//volume = angle;
}

void A_RISE() {
	detachInterrupt(pinA);
	A_SIG = 1;

	if (B_SIG == 0)
		pulses++;//moving forward
	if (B_SIG == 1)
		pulses--;//moving reverse
	//Serial.println(pulses);
	attachInterrupt(pinA, A_FALL, FALLING);
}

void A_FALL() {
	detachInterrupt(pinA);
	A_SIG = 0;

	if (B_SIG == 1)
		pulses++;//moving forward
	if (B_SIG == 0)
		pulses--;//moving reverse
	//Serial.println(pulses);
	attachInterrupt(pinA, A_RISE, RISING);
}

void B_RISE() {
	detachInterrupt(pinB);
	B_SIG = 1;

	if (A_SIG == 1)
		pulses++;//moving forward
	if (A_SIG == 0)
		pulses--;//moving reverse
	//Serial.println(pulses);
	attachInterrupt(pinB, B_FALL, FALLING);
}

void B_FALL() {
	detachInterrupt(pinB);
	B_SIG = 0;

	if (A_SIG == 0)
		pulses++;//moving forward
	if (A_SIG == 1)
		pulses--;//moving reverse
	//Serial.println(pulses);
	attachInterrupt(pinB, B_RISE, RISING);
}


*/






/*

//https://github.com/RalphBacon/RotaryEncoderUpdate/blob/master/RotaryEncoderDualInterrruptsPulseCount.ino

#define maxVolume				 100	   // sound Loudest 
#define minVolume				 0    // No sound at all
volatile int pinACount;			// Updated by ISR for each pin
volatile int pinBCount;
int volume;
char bounce = 15;				// Delay to counteract switch bounce (milliseconds)

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void isrA() {
	static unsigned long lastInterruptTimeA = 0;
	unsigned long interruptTimeA = millis();

	// If interrupts come faster than Xms, assume it's a bounce and ignore
	if (interruptTimeA - lastInterruptTimeA > bounce) {

		pinACount++;

		// Keep track of when we were here last
		lastInterruptTimeA = interruptTimeA;
	}
}

void isrB() {
	static unsigned long lastInterruptTimeB = 0;
	unsigned long interruptTimeB = millis();

	// If interrupts come faster than Xms, assume it's a bounce and ignore
	if (interruptTimeB - lastInterruptTimeB > bounce) {

		pinBCount--;

		// Keep track of when we were here last
		lastInterruptTimeB = interruptTimeB;
	}
}

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
//------------------------------------------------------------------
void encoderIni(){
	// Just whilst we debug, view output on serial monitor
	//serial.begin(115200);

	// Rotary pulses are INPUTs
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);

	// Attach the routine to service the interrupts
	attachInterrupt(digitalPinToInterrupt(pinA), isrA, CHANGE);
	attachInterrupt(digitalPinToInterrupt(pinB), isrB, CHANGE);

	// Ready to go!
	Serial.println("S   t    a   r   t");
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------


void checkEncoder()
{
	
	if (pinACount > maxVolume) pinACount = maxVolume;
	
	if (pinACount < minVolume) pinACount = minVolume;
			
	
	static long lastPrintTime = millis();
	
	if (millis() > lastPrintTime + 50)	 // Print the total every XXX seconds
	{
	
		Serial.print("A="); Serial.print(pinACount);
		Serial.print(" B="); Serial.println(pinBCount);	// Write out to serial monitor the value and direction
		
		lastPrintTime = millis();			// Keep track of print time
	}
}

*/






/*

//   -------   ENCODER Rotary sw routine  ----
//   ----       pin #'s in confige.h  
//   ---  https://dronebotworkshop.com/rotary-encoders-arduino/
 


#define maxVolume				100	   // sound Loudest 
#define minVolume				 0    // No sound at all
#define shortPressTimeMs		 20    // [ms] short press
#define longPressTimeMs			 2000  // [ms] long  press
#define encoderFastSpeedMs		 10    // [ms] rotary speed fast
#define encoderSlowSpeedMs		 200   // [ms] rotary speed slow
#define encoderIncrmntSlow       1
#define encoderIncrementFast     10


int volume;
byte increment = 0;
byte pointer = 0; 
byte encoderClock = 0;
byte encoderClockOld = 0;
byte encoderSw = 0;
byte encoderSwOld = 0;
unsigned long encoderPressTime = 0;
unsigned long encoderRotatedTimeMs=0;

int angle = (maxVolume + minVolume) / 2;
int setpoint[3] = { angle - 5, angle + 5, angle };

//  -----   Encoder sw initilization routine -----------
void encoderIni(){

pinMode(encoderClockPin,    INPUT_PULLUP);
pinMode(encoderDataPin,     INPUT_PULLUP);
pinMode(encoderSwitchPin,   INPUT_PULLUP);

encoderClockOld =	 digitalRead(encoderClockPin);
encoderSwOld =		 digitalRead(encoderSwitchPin);

Serial.print("SETPOINT = ");
Serial.println(setpoint[pointer]);
} // end ini routine



// -----  Check Volume - encoder switch routine 
void checkEncoder() 
{	// ----- READ ROTARY ENCODER TO MODIFY SERVO SETPOINT

	encoderClock = digitalRead(encoderClockPin);
	if ((encoderClock == 1) && (encoderClockOld == 0))  // 0->1 transition
	{	
		if ((millis() - encoderRotatedTimeMs) > encoderSlowSpeedMs)
		{
			increment = encoderIncrmntSlow;
		}
			else if ((millis() - encoderRotatedTimeMs) > encoderFastSpeedMs) 
			{
				increment = encoderIncrementFast;
			}
				else 
					{
						Serial.println("ROT BOUNCED");
						increment = 0;
					}
			encoderRotatedTimeMs = millis();

		if (digitalRead(encoderDataPin) == 1) setpoint[pointer] = setpoint[pointer] + increment;
			else setpoint[pointer] = setpoint[pointer] - increment;
	
		if (setpoint[pointer] < minVolume) setpoint[pointer] = minVolume;
	
		if (setpoint[pointer] > maxVolume) setpoint[pointer] = maxVolume;  
	
		Serial.println(setpoint[pointer]);
	}  
	
	encoderClockOld = encoderClock; 
		Serial.println(pulses);

	if (angle < setpoint[pointer]) angle++;    
	if (angle > setpoint[pointer]) angle--;
	
	Serial.println(angle);
	volume = angle;

	//----- read ENCODER sw,  when pussed short -> center volume=40,  when pushed long -> minimum volume =80
	encoderSw = digitalRead(encoderSwitchPin);
		if (((encoderSwOld == 1) && encoderSw == 0))    encoderPressTime = millis(); // 1->0 transition
		
		if ((encoderSwOld == 0) && (encoderSw == 1))  // 0->1 transition
		{	
			if ((millis() - encoderPressTime) > longPressTimeMs)  // long press
			{	
				pointer = 2; // servo to setpoint[2] = mid angle
				Serial.print("Long press: SETPOINT = ");
				Serial.println(setpoint[pointer]);
			}
			else if ((millis() - encoderPressTime) > shortPressTimeMs)  // short press
			{	
				pointer = (pointer + 1) % 2;
				Serial.print("Short press: SETPOINT = ");
				Serial.println(setpoint[pointer]);
			}
			else Serial.println("SW BOUNCED");
		}
		encoderSwOld = encoderSw;
}// -----  end of encoder routine 

*/








/*  =====  ========== ==---- ------------
		demo from done shope site
---------- ------------- ------------- -
 // Rotary Encoder Inputs
#define inputCLK 4
#define inputDT 5

// LED Outputs
#define ledCW 8
#define ledCCW 9

int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {

	// Set encoder pins as inputs  
	pinMode(inputCLK, INPUT);
	pinMode(inputDT, INPUT);

	// Set LED pins as outputs
	pinMode(ledCW, OUTPUT);
	pinMode(ledCCW, OUTPUT);

	// Setup Serial Monitor
	Serial.begin(9600);

	// Read the initial state of inputCLK
	// Assign to previousStateCLK variable
	previousStateCLK = digitalRead(inputCLK);

}

void loop() {

	// Read the current state of inputCLK
	currentStateCLK = digitalRead(inputCLK);

	// If the previous and the current state of the inputCLK are different then a pulse has occured
	if (currentStateCLK != previousStateCLK) {

		// If the inputDT state is different than the inputCLK state then 
		// the encoder is rotating counterclockwise
		if (digitalRead(inputDT) != currentStateCLK) {
			counter--;
			encdir = "CCW";
			digitalWrite(ledCW, LOW);
			digitalWrite(ledCCW, HIGH);

		}
		else {
			// Encoder is rotating clockwise
			counter++;
			encdir = "CW";
			digitalWrite(ledCW, HIGH);
			digitalWrite(ledCCW, LOW);

		}
		Serial.print("Direction: ");
		Serial.print(encdir);
		Serial.print(" -- Value: ");
		Serial.println(counter);
	}
	// Update previousStateCLK with the current state
	previousStateCLK = currentStateCLK;
}
*/

