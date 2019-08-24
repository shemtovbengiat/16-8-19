// ---- MP-3   Initialization  routine --------

void mp3Ini() {

#if defined(DEBUG)
	Serial.println("MP3 inishlizing");
#endif
	if (!musicPlayer.begin()) { // initialise the music player
#if defined(DEBUG)
		Serial.println("Couldn't find VS1053, do you have the right pins defined?");
#endif
		isMP3On = false;
		return;
	}
#if defined(DEBUG)
	Serial.println("VS1053 found");
#endif
	if (!SD.begin(CARDCS)) {
#if defined(DEBUG)
		Serial.println("SD failed, or not present");
#endif
		isMP3On = false;
		return;
	}
	isMP3On = true;  //  initialise the music player and SD in SETUP routine
	// list files
	if (isMP3On) {
#if defined(DEBUG)
		printDirectory(SD.open("/"), 0);
#endif
		// Set volume for left, right channels. lower numbers == louder volume!
		musicPlayer.setVolume(volume,volume);
		musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);  
	}
}
//-------  END of MP -3  inisilaztion routine ------------

/*
   -----------this is to start a sound,  give it the path to the file
*/
void playSound(char* path)
{
#if defined(DEBUG)
	Serial.print("playing file: -- ");
	Serial.println(path);
#endif
	if (musicPlayer.playingMusic) {
		musicPlayer.stopPlaying();
	}
	if (musicPlayer.stopped()) {
		// Start playing a file, then we can do stuff while waiting for it to finish
		if (!musicPlayer.startPlayingFile(path)) {
			Serial.print("Could not open file:");
			Serial.println(path);
		}
		Serial.println("Started playing");
	}
	else {
#if defined(DEBUG)
		Serial.println("=== Error: cant stop last file! ===");
#endif
	}
	return;
}
 //  ------ end of MP-3 routine 

void nextSong(int i) {				// blcsk weel sw - Song
	char str[12];
	sprintf(str, "songs/%d.mp3", i);
	playSound(str);
}

void nextVocal(int i) {
	char str[12];
	sprintf(str, "vocal/%d.mp3", i);
	playSound(str);
}
void nextStarter(int i) {					// starter sw.
	char str[12];
	sprintf(str, "starter/%d.mp3", i);
	playSound(str);
}
void nextHorn(int i) {					// horn sw,
	char str[11];
	sprintf(str, "vocal/%d.mp3", i);
	playSound(str);
}
void nextCommand(int i) {			// instructions
	char str[13];
	sprintf(str, "comnd/%d.mp3", i);
	playSound(str);
}



// ------------  File listing routine -------
void printDirectory(File dir, int numTabs) {
	while (true) {

		File entry = dir.openNextFile();
		if (!entry) {
			// no more files
			//Serial.println("**nomorefiles**");
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
			Serial.print('\t');
		}
		Serial.print(entry.name());
		if (entry.isDirectory()) {
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		}
		else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
			songCount++;
		}
		entry.close();
	}
}  