/*
  --------------  NeoPixels on the tractor -----------
	   ===================8-2019 ------------
	   ------  numbers of leds in each strip and pin # of strip in config !!! ---------
*/

int i = 0;
int colorVar = 0;
int diplayColor = 0;     // diplay on wheel 0-red 1=green 3=yellow fault

unsigned long previousInteriorMillis = 0;      // will store last time LED was updated
unsigned long previousMotorMillis = 0;
long interiorTiming = 100;                     // interval at which to blink (10 fast 200 slowest in ms)
long motorTiming = 0;

// *****************************************************************
// *******************   neopixle INI  ruotine  ********************
//******************************************************************
void neopixleIni(){

	neoMotor.begin();           // initilaze the 4 classe
	neoTurnL.begin();
	neoTurnR.begin();
	neoInterior.begin();

	neoStopAll();
}//---END of INIT routine
/*
// **************************************************************
// ************** Main routine to handle NEOPIXLES *************
// **************************************************************

void runNeoPixles()
{
	if (motorOn == 1)
	{
		unsigned long currentInteriorMillis = millis();

		if (currentInteriorMillis - previousInteriorMillis >= interiorTiming)   // delay for auto-test the engine
		{
			previousInteriorMillis = currentInteriorMillis;
			neoInteriorShow(1);		// turn the red into green function by function
			//neoMotorShow();		    // play leds in the motor	
			//neoTurnLshow(2);			
			//neoTurnRshow(3);
		}
	}
	else
	{
		neoInteriorShow(0);		// inetirior goes RED=0 - malfunction!!
		//neoStopAll();
	}
}

*/// 0-no light  1-yellow-warning light = 255,120,0  2-red 3-green 4-blue 5-random



//*******************    turn left show     ************************************

void neoTurn_Lshow(int colorVar){

	if (i < neoTurnL.numPixels())
	{
		if      (colorVar == 0)	neoTurnL.setPixelColor(i,     0, 0, 0);

		else if (colorVar == 1)	neoTurnL.setPixelColor(i,   220,120,0);
		else if (colorVar == 2)	neoTurnL.setPixelColor(i,   100, 0, 0);
		else if (colorVar == 3)	neoTurnL.setPixelColor(i,   0, 150, 0);
		else if (colorVar == 4) neoTurnL.setPixelColor(i,   0, 0, 150);
		else if (colorVar == 5)	neoTurnL.setPixelColor(i,   random(0, 100), random(0, 250), random(0, 250));
		neoTurnL.show();
		i++;
	}
	else  i = 0;
} // ---------end of neo Turn Left Show routine  ------------

//  ********************   turn roght show ***************************

void neoTurn_Rshow(int colorVar)			// interior light - RED motor OFF    GREEN - motor ON
{
	if (i < neoTurnR.numPixels()){
					// 0-no light    1-yellow-warning light = 255,120,0       2-red    3-green   4-blue    5-random
		
		if (colorVar == 0)	neoTurnR.setPixelColor(i, 0, 0, 0);
		
		else if (colorVar == 1) neoTurnR.setPixelColor(i, 255, 120, 0);
		else if (colorVar == 2) neoTurnR.setPixelColor(i, 100, 0, 0);
		else if (colorVar == 3)	neoTurnR.setPixelColor(i, 0, 150, 0);
		else if (colorVar == 4)	neoTurnR.setPixelColor(i, 0, 0, 150);
		else if (colorVar == 5) neoTurnR.setPixelColor(i, random(100), random(150), random(150));	
		neoTurnR.show();
		i++;
	}
	else i = 0;
}// ---------end of neo Turn Right Show routine  ------------


//  *********************   interior show ***********************

void neoInteriorShow(int colorVar)	// interior light - 0 = RED = motor OFF   1 = GREEN = motor ON
{
	if (i < neoInterior.numPixels())
	{
		if		(colorVar == 0) neoInterior.setPixelColor(i, 20, 0, 0);
		else if (colorVar == 1)	neoInterior.setPixelColor(i, 0, 10, 0);
		else if (colorVar == 2)	neoInterior.setPixelColor(i, 0, 10, 0);
		else if (colorVar == 3)	neoInterior.setPixelColor(i, 0, 10, 0);
		else if (colorVar == 4)	neoInterior.setPixelColor(i, 20, 10, 0);
		neoInterior.show();
		i++;
	}
	else i = 0;
}
// *****************   Motor  show  ruoyine *********

void neoMotorShow(int neoMotorNumber)
{
	if (i < neoMotor.numPixels())
	{
		if		(colorVar == 0) neoMotor.setPixelColor(i, 20, 0, 0);							// 0-   off
		else if (colorVar == 1)	neoMotor.setPixelColor(i, 20, 0, 0);							// 1-3  rgb
		else if (colorVar == 2)	neoMotor.setPixelColor(i, 0, 40, 0);
		else if (colorVar == 3)	neoMotor.setPixelColor(i, 0, 0, 40);
		else if (colorVar == 4) neoMotor.setPixelColor(i, random(40), random(40), random(40));  // 4-random
		neoMotor.show();
		i++;
	}
	else i = 0;
}


//*********** STOP routines -  turn OFF the NeoPixles***************
//   S T O P   A L L but not neoInteriorStop the only light that  stays on  
//************** ************ ************ **************  ****************

void neoStopAll()
{
	neoMotorStop     ();
	neoTurnRStop     ();
	neoTurnLStop     ();
	neoInteriorStop  ();
}

void neoMotorStop()  // ************   motor   ************
{
	for (int i = 0; i < neoMotor.numPixels(); i++)
	{
		neoMotor.setPixelColor(i, 0, 0, 0);
	}
	neoMotor.show();
}
void neoTurnLStop()	// ***********  turn L ************
{
	for (int i = 0; i < neoTurnL.numPixels(); i++)
	{
		neoTurnL.setPixelColor(i, 0, 0, 0);
	}
	neoTurnL.show();
}

void neoTurnRStop()	// **********  turn R   ************
{
	for (int i = 0; i < neoTurnR.numPixels(); i++)
	{
		neoTurnR.setPixelColor(i, 0, 0, 0);
	}
	neoTurnR.show();
}

void neoInteriorStop()	//  ************* intirior    ************
{
	for (int i = 0; i < neoInterior.numPixels(); i++)
	{
		neoInterior.setPixelColor(i, 0, 0, 0);
	}
	neoInterior.show();
}
// *************************     End of stop neoPixles routineS


/*

// Slightly different, this makes the rainbow equally distributed throughout
void neoMotorShow(uint8_t wait)
{
	unsigned long currentMotorMillis = millis();

	uint16_t i, j;
	for (j = 0; j<256 * 8; j++) // 5 cycles of all colors on wheel
	{
		for (i = 0; i< neoMotor.numPixels(); i++)
		{
			neoMotor.setPixelColor(i, Wheel(((i * 256 / neoMotor.numPixels()) + j) & 255));
		}
		neoMotor.show();

		if (currentMotorMillis - previousMotorMillis >= motorTiming)   // delay for auto-test the engine
		{
			previousMotorMillis = currentMotorMillis;
		}
	}
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85)
	{
		return neoMotor.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170)
	{
		WheelPos -= 85;
		return neoMotor.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return neoMotor.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

*/


