volatile boolean rtyTurnDetected;  // need volatile for Interrupts
volatile boolean up;

//  -----   rotary sw initilization routine -----------
void rtySwIni()
{
	pinMode(rtyPinB,  INPUT);
	pinMode(rtyPinA,  INPUT);
	pinMode(rtyPinSw, INPUT);
	
	digitalWrite(rtyPinSw, HIGH); // Pull-Up resistor for switch

	attachInterrupt(4, isr, FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
	Serial.println("Rotary Sw Started");
}


//  ----------  Interrupt routine runs if CLK goes from HIGH to LOW when sw rotats
void isr()
{
	delay(4);  // delay for Debouncing
	if (digitalRead(rtyPinB))
		up = digitalRead(rtyPinA);
	else
		up = !digitalRead(rtyPinA);
	rtyTurnDetected = true;
}

void checkRotarySw() 
{
	static long RotaryPosition = 0;    // STATIC to count correctly

	if (!(digitalRead(rtyPinSw))) {   // check if button is pressed
		if (RotaryPosition == 0) {  // check if button was already pressed
		}
		else {
			RotaryPosition = 0; // if YES, then reset position to ZERO
			Serial.print("Reset = ");
			Serial.println(RotaryPosition);
		}
	}

	// Runs if rotation was detected
	if (rtyTurnDetected) {
		if (up) {
			if (RotaryPosition >= 100) { // Max value set to 100
				RotaryPosition = 100;
			}
			else {
				RotaryPosition = RotaryPosition + 2;
			}
		}
		else {
			if (RotaryPosition <= -100) {
				// Max value set to -100        
				RotaryPosition = -100;
			}
			else {
				RotaryPosition = RotaryPosition - 2;
			}
		}
		rtyTurnDetected = false;  // do NOT repeat IF loop until new rotation detected
		Serial.print("volume = ");
		Serial.println(RotaryPosition);

		// if Rotation is Clockwise    
		if (RotaryPosition > 0 && RotaryPosition < 11) {
		}
		if (RotaryPosition > 10 && RotaryPosition < 21) {
		}
		if (RotaryPosition > 20 && RotaryPosition < 31) {
		}
		if (RotaryPosition > 30 && RotaryPosition < 41) {
		}
		if (RotaryPosition > 40 && RotaryPosition < 51) {
		}
		if (RotaryPosition > 50 && RotaryPosition < 61) {
		}
		if (RotaryPosition > 60 && RotaryPosition < 71) {
		}
		if (RotaryPosition > 70 && RotaryPosition < 81) {
		}
		if (RotaryPosition > 80 && RotaryPosition < 91) {
		}
		if (RotaryPosition > 90) {
		}


		// if Rotation is Counter-Clockwise 

		if (RotaryPosition < 0 && RotaryPosition > -11) {
		}
		if (RotaryPosition < -10 && RotaryPosition > -21) {
		}
		if (RotaryPosition < -20 && RotaryPosition > -31) {
		}
		if (RotaryPosition < -30 && RotaryPosition > -41) {
		}
		if (RotaryPosition < -40 && RotaryPosition > -51) {
		}
		if (RotaryPosition < -50 && RotaryPosition > -61) {
		}
		if (RotaryPosition < -60 && RotaryPosition > -71) {
		}
		if (RotaryPosition < -70 && RotaryPosition > -81) {
		}
		if (RotaryPosition < -80 && RotaryPosition > -91) {
		}
		if (RotaryPosition < -90) {
		}
	}
}

