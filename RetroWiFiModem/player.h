uint8_t playerVolume = 3;

typedef struct {
   uint8_t header;
   uint8_t version;
   uint8_t length;
   uint8_t command;
   uint8_t ack;
   uint8_t param[2];
   uint8_t checksum[2];
   uint8_t end;
} T_DFCMD;

T_DFCMD playTrack = {0x7E, 0xFF, 0x06, 0x03, 0x00, {0,0}, {0,0}, 0xEF};
T_DFCMD setVolume = {0x7E, 0xFF, 0x06, 0x06, 0x00, {0,0}, {0,0}, 0xEF};

void playerInit(void) {
   Serial1.begin(9600);
   pinMode(BUSY, INPUT);
}

bool playerIsBusy(void) {
   return !digitalRead(BUSY);
}

// waits while the busy signal is low or timeout
void playerBusy(uint16_t pause) {
   uint32_t startTime = millis();
   bool busyWentActive = false;

   while( playerIsBusy() || millis() - startTime < pause ) {
      if( !busyWentActive && playerIsBusy() ) {
         busyWentActive = true;
      }
      if( busyWentActive && !playerIsBusy() ) {
         break;
      }
      yield();
   }
}

void playerChecksum(T_DFCMD *cmd) {
   int16_t sum;

   sum = cmd->version + cmd->length + cmd->command
       + cmd->ack + cmd->param[0] + cmd->param[1];
   sum = -sum;
   cmd->checksum[0] = (uint8_t)(sum >> 8);
   cmd->checksum[1] = (uint8_t)(sum & 0xFF);
}

// Set volume
void playerSetVolume(uint8_t volume) {
	uint8_t val;

   playerVolume = volume;
	switch( volume ) {
		case 0:
			val = 0;
			break;
		case 1:
			val = 20;
			break;
		case 2:
			val = 25;
			break;
		default:
			val = 30;
			break;
	}
   setVolume.param[1] = val;
   playerChecksum(&setVolume);
   Serial1.write((uint8_t *)&setVolume, sizeof setVolume);
}

// Play sound asynchronously
void playSoundAsync(uint16_t trackNumber) {
   playTrack.param[0] = trackNumber >> 8;
   playTrack.param[1] = trackNumber & 0xFF;
   playerChecksum(&playTrack);
   Serial1.write((uint8_t *)&playTrack, sizeof playTrack);
}


// Play sound and block until it finishes
void playSound(uint16_t trackNumber) {
   playTrack.param[0] = trackNumber >> 8;
   playTrack.param[1] = trackNumber & 0xFF;
   playerChecksum(&playTrack);
   Serial1.write((uint8_t *)&playTrack, sizeof playTrack);
   // Wait till sound ends
   playerBusy(750);
}

// Mute sound - same as setVolume(0)
void playerMute(void) {
   uint8_t saveVolume = playerVolume;
   playerSetVolume(0);
   playerVolume = saveVolume;
}

// Unmute sound restoring the previous volume
void playerUnmute(void) {
   playerSetVolume(playerVolume);
}
