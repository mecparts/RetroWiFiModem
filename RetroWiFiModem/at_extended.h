//
// AT&F reset NVRAM to defaults and load them into current settings
//
char *factoryDefaults(char *atCmd) {
   settings.magicNumber = MAGIC_NUMBER;
   settings.ssid[0] = NUL;
   settings.wifiPassword[0] = NUL;
   settings.serialSpeed = DEFAULT_SPEED;
   settings.dataBits = 8;
   settings.parity = 'N';
   settings.stopBits = 1;
   settings.rtsCts = false;
   settings.width = 80;
   settings.height = 24;
   settings.escChar = ESC_CHAR;
   for( int i=0; i < SPEED_DIAL_SLOTS; ++i ) {
      settings.alias[i][0] = NUL;
      settings.speedDial[i][0] = NUL;
   }
   strcpy(settings.mdnsName, "espmodem");
   settings.autoAnswer = 0;
   settings.listenPort = 0;
   strcpy(settings.busyMsg, "Sorry, the system is currently busy. Please try again later.");
   settings.serverPassword[0] = NUL;
   settings.echo = true;
   settings.telnet = REAL_TELNET;
   settings.autoExecute[0] = NUL;
   strcpy(settings.terminal, "ansi");
   strcpy(settings.location, "Computer Room");
   settings.startupWait = false;
   settings.extendedCodes = true;
   settings.verbose = true;
   settings.quiet = false;

   strcpy(settings.alias[0], "particles");
   strcpy(settings.speedDial[0], "+particlesbbs.dyndns.org:6400");
   strcpy(settings.alias[1], "altair");
   strcpy(settings.speedDial[1], "altair.virtualaltair.com:4667");
   strcpy(settings.alias[2], "heatwave");
   strcpy(settings.speedDial[2], "heatwave.ddns.net:9640");

   EEPROM.put(0, settings);
   EEPROM.commit();
   if( WiFi.status() == WL_CONNECTED ) {
      WiFi.disconnect();
   }

   if( atCmd ) {
      atCmd += 2;
      if( !atCmd[0] ) {
         sendResult(R_OK);
      }
   }
   return atCmd;
}

//
// AT&K? query flow control setting
// AT&K0 disable RTS/CTS flow control
// AT&K1 enable RTS/CTS flow control
//
char *doFlowControl(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.rtsCts);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
      case '1':
      case NUL:
         settings.rtsCts = atCmd[0] == '1';
         if( atCmd[0] ) {
            ++atCmd;
         }
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// AT&R? query incoming password
// AT&R=set incoming password
//
char *doServerPassword(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.serverPassword);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.serverPassword, atCmd, MAX_PWD_LEN);
         settings.serverPassword[MAX_PWD_LEN] = NUL;
         atCmd[0] = NUL;
         sendResult(R_OK);
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// AT&V  display current settings
// AT&V0 display current settings
// AT&V1 display NVRAM settings
//
char *displayAllSettings(char* atCmd) {
   switch( atCmd[0]) {
      case '0':
         ++atCmd;
      case NUL:
         displayCurrentSettings();
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '1':
         ++atCmd;
         displayStoredSettings();
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// AT&W: update NVRAM from current settings
//
char *updateNvram(char *atCmd) {
   EEPROM.put(0, settings);
   if( EEPROM.commit() ) {
      if( !atCmd[0] ) {
         sendResult(R_OK);
      }
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}

//
// AT&Zn? show contents of speed dial slot n
// AT&Zn=host,alias set speed dial slot n
//
char *doSpeedDialSlot(char *atCmd) {
   int slot;

   if( isDigit(atCmd[0]) ) {
      slot = atCmd[0] - '0';
      ++atCmd;
      switch( atCmd[0] ) {
         case '?':
            ++atCmd;
            if( settings.speedDial[slot][0] ) {
               Serial.printf("%s,%s\r\n",
                  settings.speedDial[slot], settings.alias[slot]);
               if( !atCmd[0] ) {
                  sendResult(R_OK);
               }
            } else {
               sendResult(R_ERROR);
            }
            break;
         case '=':
            ++atCmd;
            if( !atCmd[0] ) {
               // erase slot
               settings.speedDial[slot][0] = NUL;
               settings.alias[slot][0] = NUL;
               sendResult(R_OK);
            } else {
               char *comma = strchr(atCmd, ',');
               if( !comma ) {
                  sendResult(R_ERROR);
               } else {
                  *comma++ = NUL;
                  strncpy(settings.speedDial[slot], atCmd, MAX_SPEED_DIAL_LEN);
                  settings.speedDial[slot][MAX_SPEED_DIAL_LEN] = NUL;
                  strncpy(settings.alias[slot], comma, MAX_ALIAS_LEN);
                  settings.alias[slot][MAX_ALIAS_LEN] = NUL;
                  atCmd[0] = NUL;
                  sendResult(R_OK);
               }
            }
            break;
         default:
            sendResult(R_ERROR);
            break;
      }
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}
