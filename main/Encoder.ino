/*
   -------   rotary encoder sw routine  ----
   ---- pin #'s in confige.h  
   ---  settings for encoder routine
 */

#define maxVolume            1	   // sound Loudest 
#define minVolume            99    // No sound at all
#define shortPressTimeMs     20    // [ms] short press
#define longPressTimeMs      2000  // [ms] long  press
#define rtyFastSpeedMs       10    // [ms] rotary speed fast
#define rtySlowSpeedMs       200   // [ms] rotary speed slow
#define swIncrmntSlow        1
#define swIncrementFast      10

byte increment;
byte pointer; 
byte enc_clk, enc_clk_old;
byte enc_switch, enc_switch_old;
int angle = (maxVolume + minVolume) / 2;
int setpoint[3] = { angle - 5, angle + 5, angle };
unsigned long time_for_servo, enc_pressed_time, enc_rotated_time;


//  -----   Encoder sw initilization routine -----------
void encoderIni()
{
pinMode(encoderClockPin,    INPUT_PULLUP);
pinMode(encoderDataPin,     INPUT_PULLUP);
pinMode(encoderSwitchPin,   INPUT_PULLUP);
Serial.print("SETPOINT = ");
Serial.println(setpoint[pointer]);
enc_clk_old =	 digitalRead(encoderClockPin);
enc_switch_old = digitalRead(encoderSwitchPin);
} // end ini routine



// -----  Check Volume - encoder switch routine 
void checkEncoder() 
{// READ ROTARY ENCODER TO MODIFY SERVO SETPOINT
	enc_clk = digitalRead(encoderClockPin);
	if ((enc_clk == 1) && (enc_clk_old == 0)) { // 0->1 transition
		if ((millis() - enc_rotated_time) > rtySlowSpeedMs) {
			increment = swIncrmntSlow;
		}
		else if ((millis() - enc_rotated_time) > rtyFastSpeedMs) {
			increment = swIncrementFast;
		}
			else {
				Serial.println("ROT BOUNCED");
				increment = 0;
			}
	enc_rotated_time = millis();

			if (digitalRead(encoderDataPin) == 1) setpoint[pointer] = setpoint[pointer] + increment;
			else setpoint[pointer] = setpoint[pointer] - increment;
			if (setpoint[pointer] < minVolume) setpoint[pointer] = minVolume;
			if (setpoint[pointer] > maxVolume) setpoint[pointer] = maxVolume;     Serial.println(setpoint[pointer]);
		}   enc_clk_old = enc_clk; // INCREMENT SERVO   if (millis() > time_for_servo) {
			if (angle < setpoint[pointer]) angle++;    
			if (angle > setpoint[pointer]) angle--;
			Serial.println(angle);
			volume = angle;

 // READ SWITCH AND CHANGE center volume 	
	enc_switch = digitalRead(encoderSwitchPin);
		if (((enc_switch_old == 1) && enc_switch == 0)) enc_pressed_time = millis(); // 1->0 transition
		if ((enc_switch_old == 0) && (enc_switch == 1)) { // 0->1 transition
			if ((millis() - enc_pressed_time) > longPressTimeMs) { // long press
				pointer = 2; // servo to setpoint[2] = mid angle
				Serial.print("Long press: SETPOINT = ");
				Serial.println(setpoint[pointer]);
			}
			else if ((millis() - enc_pressed_time) > shortPressTimeMs) { // short press
				pointer = (pointer + 1) % 2;
				Serial.print("Short press: SETPOINT = ");
				Serial.println(setpoint[pointer]);
			}
			else Serial.println("SW BOUNCED");
		}
		enc_switch_old = enc_switch;

}// end of encoder routine 

