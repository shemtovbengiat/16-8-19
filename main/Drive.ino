

/*
Drive.ino - controls 2 43A BTS-7960 MOTOR DRIVERs.
Both work together for power sake only (later will test steering with the 2 motoe but each its own direction)

Drive in enabled only if motorOn=1-START pushed, joystick pushed forward or reverse driveLOn or driveROn and then if pedalOn=1 DRIVE pedalOn=0 stop.
Code for BTS7960 Motor driver uses CLASS - BTS7960MotorDriver at: http://wordpress.bonairetec.com/?p=75
The class has 4 commands: stop() - all 4 pins go 0,
						  ready() [drive Eenable] 2 enable pins 1 and 2 go high,
						  turnleft(0-255) clockwise - forwared at speed 0-255 to be set by rotary encoder later on
						  turnRight(0-255) counter clockwise - reverse  at speed 0-255 to be set by rotary encoder later on
*/

BTS7960MotorDriver Lmotor(ldrmEn1Pin, ldrmEn2Pin, ldrmPwm1Pin, ldrmPwm2Pin);     //constructor for LEFT motor class
BTS7960MotorDriver Rmotor(rdrmEn1Pin, rdrmEn2Pin, rdrmPwm1Pin, rdrmPwm2Pin);     //constructor for RIGHT motor class

// ----DRIVE INI  -  Initialization  in SETUP routine--------
int redBrakeState = 0;
unsigned long previousRedLghtMillis = 0;      // will store last time redBrakeLight was updated
long redBrakeLghtTiming = 0;                // interval at which to blink (10 fast 200 slowest in milliseconds)

void driveIni()
{
	pinMode(ldrmEn1Pin, OUTPUT);        // Set motor pins as output  - PWM PINS !
	pinMode(ldrmEn2Pin, OUTPUT);
	pinMode(ldrmPwm1Pin, OUTPUT);
	pinMode(ldrmPwm2Pin, OUTPUT);

	pinMode(rdrmEn1Pin, OUTPUT);
	pinMode(rdrmEn2Pin, OUTPUT);
	pinMode(rdrmPwm1Pin, OUTPUT);
	pinMode(rdrmPwm2Pin, OUTPUT);
	digitalWrite(ldrmEn1Pin, 0);           // Varify motor stops at startup 
	digitalWrite(ldrmEn2Pin, 0);
	digitalWrite(rdrmEn1Pin, 0);
	digitalWrite(rdrmEn2Pin, 0);

	analogWrite(ldrmPwm1Pin, 0);
	analogWrite(ldrmPwm2Pin, 0);
	analogWrite(rdrmPwm1Pin, 0);
	analogWrite(rdrmPwm2Pin, 0);

	pinMode(reversePin, OUTPUT);
	pinMode(redBrakesPin, OUTPUT);

} //--- END of Ini routine 



// ---------  drive motors routine ---------------------------------
void Drive(int l, int r, int speedL, int speedR)   //0 =stop, 1 = forward, 2 = reverse
{

	if (l == 0)
	{
		stopMotorL();
		digitalWrite(redBrakesPin, 0);		// turn off red light not driving
		digitalWrite(reversePin, 0);		// turn off reverse not driving
	}
	else if (l == 1)			// FORWARD
	{
		driveForwardL(speedL);

		digitalWrite(reversePin, 0);		// turn off reverse 
		redBrakeLghtTiming = 60;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}
	else if (l == 2)			// REVERSE
	{
		driveReverseR(speedL);

		digitalWrite(reversePin, 1);		// turn off reverse 
		redBrakeLghtTiming = 160;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}


	if (r == 0)	stopMotorR();
	else if (r == 1) driveForwardR(speedR);
	else if (r == 2) driveReverseR(speedR);
}


void stopMotorL() {					     // stop motors
	digitalWrite(ldrmEn1Pin, 0);
	digitalWrite(ldrmEn2Pin, 0);

	analogWrite(ldrmPwm1Pin, 0);
	analogWrite(ldrmPwm2Pin, 0);
}
void stopMotorR() {
	digitalWrite(rdrmEn1Pin, 0);
	digitalWrite(rdrmEn2Pin, 0);

	analogWrite(rdrmPwm1Pin, 0);
	analogWrite(rdrmPwm2Pin, 0);
}



void driveForwardL(int pwm) {		     // forward 
	digitalWrite(ldrmEn1Pin, 1);
	digitalWrite(ldrmEn2Pin, 1);

	analogWrite(ldrmPwm1Pin, 0);
	analogWrite(ldrmPwm2Pin, pwm);
}
void driveForwardR(int pwm) {
	digitalWrite(rdrmEn1Pin, 1);
	digitalWrite(rdrmEn2Pin, 1);

	analogWrite(rdrmPwm1Pin, 0);
	analogWrite(rdrmPwm2Pin, pwm);
}


void driveReverseL(int pwm) {			// reverse
	digitalWrite(ldrmEn1Pin, 1);
	digitalWrite(ldrmEn2Pin, 1);

	analogWrite(ldrmPwm1Pin, pwm);
	analogWrite(ldrmPwm2Pin, 0);
}
void driveReverseR(int pwm) {
	digitalWrite(rdrmEn1Pin, 1);
	digitalWrite(rdrmEn2Pin, 1);

	analogWrite(rdrmPwm1Pin, pwm);
	analogWrite(rdrmPwm2Pin, 0);
}

void lightRedBrake()		 // ---- light red brake  sub routine --------
{
	unsigned long currentRedBrakeMillis = millis();
	if (currentRedBrakeMillis - previousRedLghtMillis >= redBrakeLghtTiming) {    // 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		previousRedLghtMillis = currentRedBrakeMillis;   // save the last time you blinked the LED

											// if the LED is off turn it on and vice-versa  --- valve 1 *********************************
		if (redBrakeState == 0) redBrakeState = 1;
		else
			redBrakeState = 0;
		digitalWrite(redBrakesPin, redBrakeState);
	}
}
