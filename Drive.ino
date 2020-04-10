

/*
Drive.ino - controls  43A BTS-7960 MOTOR DRIVERs.

Drive in enabled only if motorOn=1 - START Engine pushed, drive handle  pushed forward or reverse  and  pedalOn=1 DRIVE / pedalOn=0 stop.
Code for BTS7960 Motor driver uses CLASS - BTS7960MotorDriver at: http://wordpress.bonairetec.com/?p=75
The class has 4 commands: stop() - all 4 pins go 0,
						  ready() [drive Eenable] - enable pins 1 and 2 go high,
						  turnleft(0-255) motor clockwise = forwared at speed 0-255 to be set by user 
						  turnRight(0-255) motor counter clockwise = reverse  at speed 0-255 to be set user 
*/

//BTS7960MotorDriver driveMotors(drvMotorEnPin1, drvMotorEnPin2, drvMotorPwmPin1, drvMotorPwmPin2);     //constructor for Motors class

int				redBrakeState		  = 0;
unsigned long	previousRedLghtMillis = 0;    // will store last time redBrakeLight was updated
long			redBrakeLghtTiming    = 0;                // interval at which to blink (10 fast 200 slowest in milliseconds)

											
//  ---------    initilization routine
void driveIni()
{
	pinMode(drvMotorEnPin1,     OUTPUT);        // Set motor pins as output at config  - PWM PINS !
	pinMode(drvMotorEnPin2,     OUTPUT);

	pinMode(drvMotorPwmPin1,    OUTPUT);
	pinMode(drvMotorPwmPin2,    OUTPUT);

	pinMode(revLightPin,        INPUT_PULLUP);
	pinMode(redLightDrivePin,   INPUT_PULLUP);

	pinMode(revLightPin,        OUTPUT);
	pinMode(redLightDrivePin,   OUTPUT);


	digitalWrite(drvMotorEnPin1, 0);        // Varify motor stops at startup 
	digitalWrite(drvMotorEnPin2, 0);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, 0);

} //--- END of Ini routine 

// ----------    drive motors routine ---------------------------------
void Drive(int drvFlag,  int speed)   //0 =stop, 1 = forward, 2 = reverse, speed set at main routin 0 -255 max speed 
{
	if (drvFlag == 0)
	{
		stopMotors();
		//digitalWrite(redLightDrivePin, 1);		// turn off=1 red light - not driving
		digitalWrite(revLightPin, 1);			// turn off=1 reverse   - not driving
	}
	if (drvFlag == 1)			// FORWARD
	{
		driveForward(speed);

		digitalWrite(revLightPin, 1);		// turn off reverse 
		redBrakeLghtTiming = 60;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}
	if (drvFlag == 2)			// REVERSE
	{
		driveReverse(speed);

		digitalWrite(revLightPin, 0);		// turn on  reverse 
		redBrakeLghtTiming = 160;			// 50-200 miliseconds = fast 2 slow 200 see in beggining of this routine 
		lightRedBrake();					// red brake light blinking
	}
}

// **********    stop motors   *******************
void stopMotors() 
{					     
	digitalWrite(drvMotorEnPin1, 0);
	digitalWrite(drvMotorEnPin2, 0);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, 0);

	lightRedBrake();					// while stop -  flash Red lights as if braking...
}

// **********    forward   **********************
void driveForward(int pwm) 
{		     
	digitalWrite(drvMotorEnPin1, 1);
	digitalWrite(drvMotorEnPin2, 1);

	analogWrite(drvMotorPwmPin1, 0);
	analogWrite(drvMotorPwmPin2, pwm);
}

// ***********   reverse  *************************
void driveReverse(int pwm) 
{			
	digitalWrite(drvMotorEnPin1, 1);
	digitalWrite(drvMotorEnPin2, 1);

	analogWrite(drvMotorPwmPin1, pwm);
	analogWrite(drvMotorPwmPin2, 0);
}

//  **********   light red brake  sub routine *************
void lightRedBrake()		
{
	unsigned long currentRedBrakeMillis = millis();
	if (currentRedBrakeMillis - previousRedLghtMillis >= redBrakeLghtTiming) {    // 50-200 miliseconds = fast=2 slow=200  
		previousRedLghtMillis = currentRedBrakeMillis;   // save the last time you blinked the LED
											
		if (redBrakeState == 1) redBrakeState = 0;      // if the LED is off turn it on and vice-versa  
		else redBrakeState = 1;
		//digitalWrite(redLightDrivePin, redBrakeState);
	}
}
