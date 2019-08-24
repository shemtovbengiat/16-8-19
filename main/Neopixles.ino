
/*
  --------------  NeoPixels on the tractor -----------
	   ===================8-2019 ------------

	   ------  numbers of leds in each strip and pin # of strip in config !!! ---------
*/

int i = 0;
int diplayColor = 0;     // diplay on wheel 0-red 1=green 3=yellow fault
int c = 0;

unsigned long previousInteriorMillis = 0;      // will store last time LED was updated
long interiorTiming = 100;                // interval at which to blink (10 fast 200 slowest in milliseconds)
unsigned long previousMotorMillis = 0;
long motorTiming = 0;


// ----------------   neopixle INITIALIZATION routine  -----------------
void neopixleIni()
{

	neoMotor.begin();           // initilaze the 5 classe
	neoTurnL.begin();
	neoTurnR.begin();
	neoInterior.begin();
	neoExhaost.begin();

	neoStopAll();
}//---END of INITIALIZATION routine


// ************** Main routine to handle NEOPIXLES *************
void runNeoPixles()
{
	if (motorOn == 1)
	{
		unsigned long currentInteriorMillis = millis();

		if (currentInteriorMillis - previousInteriorMillis >= interiorTiming)   // delay for auto-test the engine
		{
			previousInteriorMillis = currentInteriorMillis;
			neoInteriorShow(1);		// turn the red into green function by function
			neoMotorShow();		// play leds in the motor	
			//neoTurnLshow(2);			
			//neoTurnRshow(3);
			neoExhaostShow();
		}

	}
	else
	{
		neoInteriorShow(0);		// inetirior goes RED=0 - malfunction!!
		neoStopAll();
	}
}

// 0-no light  1-yellow-warning light = 255,120,0  2-red 3-green 4-blue 5-random
void neoTurnLshow(int c)
{
	if (i < neoTurnL.numPixels())
	{
		if (c == 0)
		{
			neoTurnL.setPixelColor(i, 0, 0, 0);
		}
		else if (c == 1)
		{
			neoTurnL.setPixelColor(i, 220, 120, 0);
		}
		else if (c == 2)
		{
			neoTurnL.setPixelColor(i, 100, 0, 0);
		}
		else if (c == 3)
		{
			neoTurnL.setPixelColor(i, 0, 150, 0);
		}
		else if (c == 4)
		{
			neoTurnL.setPixelColor(i, 0, 0, 150);
		}
		else if (c == 5)
		{
			neoTurnL.setPixelColor(i, random(0, 100), random(0, 250), random(0, 250));
		}

		neoTurnL.show();
		i++;
	}
	else
	{
		i = 0;
	}
}


void neoTurnRshow(int c)			// interior light - RED motor OFF    GREEN - motor ON
{
	if (i < neoTurnR.numPixels())
	{
		if (c == 0)				// 0-no light    1-yellow-warning light = 255,120,0       2-red    3-green   4-blue    5-random
		{
			neoTurnR.setPixelColor(i, 0, 0, 0);
		}
		else if (c == 1)
		{
			neoTurnR.setPixelColor(i, 255, 120, 0);
		}
		else if (c == 2)
		{
			neoTurnR.setPixelColor(i, 100, 0, 0);
		}
		else if (c == 3)
		{
			neoTurnR.setPixelColor(i, 0, 150, 0);
		}
		else if (c == 4)
		{
			neoTurnR.setPixelColor(i, 0, 0, 150);
		}
		else if (c == 5)
		{
			neoTurnR.setPixelColor(i, random(100), random(150), random(150));
		}

		neoTurnR.show();
		i++;
	}
	else
	{
		i = 0;
	}
}




void neoInteriorShow(int c)	// interior light - 0 = RED = motor OFF   1 = GREEN = motor ON
{
	if (i < neoInterior.numPixels())
	{
		if (c == 0) //RED = motor OFF
		{
			neoInterior.setPixelColor(i, 10, 0, 0);
		}
		else if (c == 1) 	//GREEN = motor ON
		{
			neoInterior.setPixelColor(i, 0, 10, 0);
		}
		neoInterior.show();
		i++;
	}
	else
	{
		i = 0;
	}
}

void neoMotorShow()
{
	if (i < neoMotor.numPixels())
	{
		neoMotor.setPixelColor(i, random(60, 100), random(10, 100), random(40, 100));
		neoMotor.show();
		i++;
	}
	else
	{
		i = 0;
	}
}

//  Head lights   -------------

void neoHeadShow()
{
	if (i < neoHead.numPixels())
	{
		neoHead.setPixelColor(i, random(0, 155), 0, random(0, 155));
		neoHead.show();
		i++;
	}
	else
	{
		i = 0;
	}
}

//exhaost

void neoExhaostShow()
{
	if (i < neoExhaost.numPixels())
	{
		neoExhaost.setPixelColor(i, random(0, 155), 0, random(0, 155));
		neoExhaost.show();
		i++;
	}
	else
	{
		i = 0;
	}
}



//*********** STOP routines -  turn OFF the NeoPixles***************
//   S T O P   A L L but not neoInteriorStop the only light that  stays on  

void neoStopAll()
{
	neoMotorStop   ();
	neoTurnRStop   ();
	neoTurnLStop   ();
	neoExhaostStop ();
	neoHeadStop    ();
	neoInteriorStop();
}

void neoMotorStop()  //  motor
{
	for (int i = 0; i < neoMotor.numPixels(); i++)
	{
		neoMotor.setPixelColor(i, 0, 0, 0);
	}
	neoMotor.show();
}
void neoTurnLStop()	// turn l
{
	for (int i = 0; i < neoTurnL.numPixels(); i++)
	{
		neoTurnL.setPixelColor(i, 0, 0, 0);
	}
	neoTurnL.show();
}
void neoTurnRStop()	// turn R
{
	for (int i = 0; i < neoTurnR.numPixels(); i++)
	{
		neoTurnR.setPixelColor(i, 0, 0, 0);
	}
	neoTurnR.show();
}
void neoExhaostStop()    // exhaost
{
	for (int i = 0; i < neoExhaost.numPixels(); i++)
	{
		neoExhaost.setPixelColor(i, 0, 0, 0);
	}
	neoExhaost.show();
}
void neoInteriorStop()	// intirior 
{
	for (int i = 0; i < neoInterior.numPixels(); i++)
	{
		neoInterior.setPixelColor(i, 0, 0, 0);
	}
	neoInterior.show();
}
void neoHeadStop()  //  headlights 
{
	for (int i = 0; i < neoHead.numPixels(); i++)
	{
		neoHead.setPixelColor(i, 0, 0, 0);
	}
	neoHead.show();
}
// ******     End of stop neoPixles routineS


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


