/*
  --------------  NeoPixels on the tractor -----------
  # of leds in each strip declered in main routine  !!! ---------/
*/
int i = 0;
int colorVar = 0;
int diplayColor = 0;     // diplay on wheel 0-red 1=green 3=yellow fault

unsigned long previousInteriorMillis = 0;      // will store last time LED was updated
unsigned long previousMotorMillis = 0;
long interiorTiming = 100;                     // interval at which to blink (10 fast 200 slowest in ms)
long motorTiming = 0;

// *******   neopixle INI  ruotine  ********************
void neopixleIni()
{
	neopixleLturn.    begin();
	neopixleRturn.    begin();
	neopixleMotor.    begin();
	neopixleIntirior. begin();
}//---END of INIT routine

//  ----  Update all neopixles routines  -------
void neopixlesUpdate()
{
	neopixleRturn.		Update();
	neopixleLturn.		Update();
	neopixleMotor.		Update();
	neopixleIntirior.	Update();
} // --- END of update neopixles routine   -------------------

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
			neoInteriorShow(swRasbPiNumber);		// turn the red into green function by function
			//neoMotorShow();		    // play leds in the motor	
			//neoTurnLshow(2);			
			//neoTurnRshow(3);
			Serial.println(swRasbPiNumber);
		}
	}
	else
	{
		neoInteriorShow(0);		// inetirior goes RED=0 - malfunction!!

												//neoStopAll();
	}
}


//*******************    turn left show     ************************************
void neoTurn_Lshow(int colorVar){

	if (i < neoTurnL.numPixels())
	{
		if      (colorVar == 0)	neoTurnL.setPixelColor(i,     0, 0, 0);

		else if (colorVar == 1)	neoTurnL.setPixelColor(i,   220,120,0);
		else if (colorVar == 2)	neoTurnL.setPixelColor(i,   100, 0, 0);
		else if (colorVar == 3)	neoTurnL.setPixelColor(i,   0, 150, 0);
		else if (colorVar == 4) neoTurnL.setPixelColor(i,   0, 0, 150);
		else if (colorVar == 5)	neoTurnL.setPixelColor(i,   random(0, 150), random(0, 100), random(0, 100));
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
		if		(colorVar == 0) neoInterior.setPixelColor(i, 200, 0, 0);
		else if (colorVar == 1)	neoInterior.setPixelColor(i, 0, 100, 0);
		else if (colorVar == 2)	neoInterior.setPixelColor(i, 0, 10, 100);
		else if (colorVar == 3)	neoInterior.setPixelColor(i, 0, 100, 100);
		else if (colorVar == 4)	neoInterior.setPixelColor(i, random(210), random(150), random(150));

		neoInterior.show();
		i++;
	}
	else i = 0;
}
// *****************   Motor  show  ruoyine *********
void neoMotorShow(int neoNumber)
{
	if (i < neoMotor.numPixels())
	{
		if		(neoNumber == 0) neoMotor.setPixelColor(i, 20, 0, 0);							// 0-   off
		else if (neoNumber == 1) neoMotor.setPixelColor(i, 20, 0, 0);							// 1-3  rgb
		else if (neoNumber == 2) neoMotor.setPixelColor(i, 0, 40, 0);
		else if (neoNumber == 3) neoMotor.setPixelColor(i, 0, 0, 40);
		else if (neoNumber == 4) neoMotor.setPixelColor(i, random(40), random(40), random(40));  // 4-random
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


// turn left Completion Callback
void neopixleLturnComplete()
{
	if (turnLOn == 1) neopixleLturn.Color1 = neopixleLturn.Color(80, 70, 0); // turn scanner yellow
	else  neopixleLturn.Scanner(neopixleLturn.Color(0, 0, 0), 120);			 // turn off
}

// turn right Completion Callback
void neopixleRturnComplete()
{
	//	neopixleRturn.RainbowCycle(random(0, 10));
	if (turnROn == 1) neopixleRturn.Color1 = neopixleRturn.Color(80, 70, 0); // turn scanner yellow
	else  neopixleRturn.Scanner(neopixleRturn.Color(0, 0, 0), 120);       // turn off
}

// intirior Completion Callback
void neopixleIntiriorComplete()
{
	// Random color change for next scan
	//Stick.Color1 = Stick.Wheel(random(255));
	neopixleIntirior.Color1 = neopixleIntirior.Color(40,40,140);
}

// motor complition callback
void neopixleMotorComplete()
{
	neopixleMotor.Color1 = neopixleMotor.Color(random(0, 250), random(0, 100), random(0, 100));

	switch (neoMotorNumber)
	{
	case 0:
		neopixleMotor.Color1 = neopixleMotor.Color(0, 0, 0);
		break;
	case 1:
		neopixleMotor.Color1 = neopixleMotor.Color(0, 200, 0);//defualt-60  0-fatest 255-slowest)
		break;
	case 2:
		neopixleMotor.Color1 = neopixleMotor.Color(200, 0, 0);//defualt-60  0-fatest 255-slowest)
		break;
	case 3:
		neopixleMotor.Color1 = neopixleMotor.Color(0, 0, 200);
		break;
	}

}


