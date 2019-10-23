// ---- MP-3   Initialization  routine --------

void mp3Ini() 
{
	Serial.println("MP3 inishlized");

	if (!musicPlayer.begin()) 
	{ // initialise the music player
		Serial.println("Couldn't find VS1053, do you have the right pins defined?");
		isMP3On = false;
		return;
	}
	Serial.println("MP 3  working");
	if (!SD.begin(mp3SDCardsPin)) 
	{
		Serial.println("SD failed, or not present");
		isMP3On = false;
		return;
	}
	isMP3On = true;  //  initialise the music player and SD in SETUP routine
	
	if (isMP3On) 
	{
	//printDirectory(SD.open("/"), 0);		// list files at setup time 
	// Set Volume for left, right channels.  0 == Max volume ,  80 == Min volume
	musicPlayer.setVolume(volume,volume);
	
	musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);  
	}
}
//-------  END of MP -3  inisilaztion routine ------------

/*
  ******************   this is to start a sound,  give it the path to the file   ************
*/
void playSound(char* path)
{

	Serial.print("playing file - ");
	Serial.println(path);

	if (musicPlayer.playingMusic)  musicPlayer.stopPlaying();
	
	if (musicPlayer.stopped()) {
		// Start playing a file, then we can do stuff while waiting for it to finish
		if (!musicPlayer.startPlayingFile(path)) {
			Serial.print("Could not open file:");
			Serial.println(path);
		}
		Serial.println("Started playing");
		musicPlayer.setVolume(volume, volume);

	}
	else Serial.println("=== Error: cant stop last file! ===");
	
	return;
}    //  ------ end of MP-3 routine 





void nextSong(int i) {				// blcsk weel sw - Song
	char str[12];
//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "songs/%d.mp3", i);
	playSound(str);
}
void nextVocal(int i) {
	char str[12];
//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "vocal/%d.mp3", i);
	playSound(str);
}
void nextStarter(int i) {					// starter sw.
	char str[12];
//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "starter/%d.mp3", i);
	playSound(str);
}
void nextHorn(int i) {					// horn sw,
	char str[11];
//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "vocal/%d.mp3", i);
	playSound(str);
}
void nextCommand(int i) {			// instructions
	char str[13];
//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "comnd/%d.mp3", i);
	playSound(str);
}
void nextStory(int i) {			// instructions
	char str[13];
	//	musicPlayer.setVolume(volume, volume);
	sprintf(str, "stories/%d.mp3", i);
	playSound(str);
}


// ------------  File listing routine -------
void printDirectory(File dir, int numTabs) 
{
	while (true) 
	{

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