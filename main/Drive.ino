

/*
Drive.ino - controls  43A BTS-7960 MOTOR DRIVERs.

Drive in enabled only if motorOn=1 - START pushed, drive handle  pushed forward or reverse  if pedalOn=1 DRIVE / pedalOn=0 stop.
Code for BTS7960 Motor driver uses CLASS - BTS7960MotorDriver at: http://wordpress.bonairetec.com/?p=75
The class has 4 commands: stop() - all 4 pins go 0,
						  ready() [drive Eenable] - enable pins 1 and 2 go high,
						  turnleft(0-255) motor clockwise - forwared at speed 0-255 to be set by user 
						  turnRight(0-255) motor counter clockwise - reverse  at speed 0-255 to be set user 
*/

BTS7960MotorDriver driveMotors(drvMotorEnPin1, drvMotorEnPin2, drvMotorPwmPin1, drvMotorPwmPin2);     //constructor for Motors class

// ----DRIVE INI  -  Initialization  in SETUP routine--------
int redBrakeState = 0;
unsigned long previousRedLghtMillis = 0;    // will store last time redBrakeLight was updated
long redBrakeLghtTiming = 0;                // interval at which to blink (10 fast 200 slowest in milliseconds)

void driveIni()
{
	pinMode(drvMotorEnPin1,    OUTPUT);        // Set motor pins as output  - PWM PINS !
	pinMode(drvMotorEnPin2,    OUTPUT);

	pinMode(drvMotorPwmPin1,   OUTPUT);
	pinMode(drvMotorPwmPin2,   OUTPUT);

	pinMode(reversePin,        OUTPUT);
	pinMode(redBrakesPin,      OUTPUT);


	digitalWrite(drvMotorEnPin1, 0);        // Varify motor stops at startup 
	digitalWrite(drvMotorEnPin2, 0);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, 0);

} //--- END of Ini routine 



// ---------  drive motors routine ---------------------------------
void Drive(int dr,  int speed)   //0 =stop, 1 = forward, 2 = reverse, speed 0-255
{

	if (dr == 0)
	{
		stopMotor();
		digitalWrite(redBrakesPin, 0);		// turn off red light not driving
		digitalWrite(reversePin, 0);		// turn off reverse not driving
	}
	else if (dr == 1)			// FORWARD
	{
		driveForward(speed);

		digitalWrite(reversePin, 0);		// turn off reverse 
		redBrakeLghtTiming = 60;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}
	else if (dr == 2)			// REVERSE
	{
		driveReverse(speed);

		digitalWrite(reversePin, 1);		// turn off reverse 
		redBrakeLghtTiming = 160;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}


}


void stopMotor() {					     // stop motors
	digitalWrite(drvMotorEnPin1, 0);
	digitalWrite(drvMotorEnPin2, 0);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, 0);
}




void driveForward(int pwm) {		     // forward 
	digitalWrite(drvMotorEnPin1, 1);
	digitalWrite(drvMotorEnPin2, 1);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, pwm);
}

void driveReverse(int pwm) {			// reverse
	digitalWrite(drvMotorEnPin1, 1);
	digitalWrite(drvMotorEnPin2, 1);

	analogWrite(drvMotorPwmPin1, pwm);
	analogWrite(drvMotorPwmPin2, 0);
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
