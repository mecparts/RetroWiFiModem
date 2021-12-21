//
// ATA manually answer an incoming call
//
char *answerCall(char *atCmd) {
   tcpClient = tcpServer.available();
   digitalWrite(RI, !ACTIVE); // we've picked up so ringing stops
   ringing = false;
   ringCount = 0;
   connectTime = millis();
   sendResult(R_CONNECT);
   digitalWrite(DCD, ACTIVE); // we've got a carrier signal
   state = ONLINE;
   Serial.flush();
   return atCmd;
}

//
// ATC? query WiFi connection status
// ATC0 disconnect from WiFi network
// ATC1 connect to WiFi network
//
char *wifiConnection(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(WiFi.status() == WL_CONNECTED ? '1' : '0');
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
         ++atCmd;
      case NUL:
         WiFi.disconnect();
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         digitalWrite(DSR, !ACTIVE);  // modem is not ready
         break;
      case '1':
         ++atCmd;
         if( settings.ssid[0] && settings.wifiPassword[0] ) {
            if( !settings.quiet && settings.extendedCodes ) {
               Serial.print(F("CONNECTING TO SSID "));
               Serial.print(settings.ssid);
            }
            WiFi.begin(settings.ssid, settings.wifiPassword);
            for( int i = 0; i < 50; ++i ) {
               delay(500);
               if( !settings.quiet && settings.extendedCodes ) {
                  Serial.print('.');
               }
               if( WiFi.status() == WL_CONNECTED ) {
                  break;
               }
            }
            if( !settings.quiet && settings.extendedCodes ) {
               Serial.println();
            }
            if( WiFi.status() != WL_CONNECTED ) {
               sendResult(R_ERROR);
            } else {
               digitalWrite(DSR, ACTIVE);  // modem is ready
               yield();
               if( !settings.quiet && settings.extendedCodes ) {
                  Serial.printf("CONNECTED TO %s IP ADDRESS: %s\r\n",
                     settings.ssid, WiFi.localIP().toString().c_str());
               }
               if( !atCmd[0] ) {
                  sendResult(R_OK);
               }
            }
         } else {
            if( !settings.quiet && settings.extendedCodes ) {
               Serial.println(F("Congigure SSID and password. Type AT? for help."));
            }
            sendResult(R_ERROR);
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// ATDSn speed dial a number
//
char *dialNumber(char *atCmd);

char *speedDialNumber(char *atCmd) {
   char number[MAX_SPEED_DIAL_LEN + 1];
   char slot = atCmd[0];

   if( isDigit(slot) && settings.speedDial[slot - '0'][0] ) {
      ++atCmd;
      strncpy(number, settings.speedDial[slot - '0'], MAX_SPEED_DIAL_LEN);
      number[MAX_SPEED_DIAL_LEN] = NUL;
      dialNumber(number);
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}

//
// ATDThost[:port] dial a number
//
char *dialNumber(char *atCmd) {
   char *host, *port, *ptr;
   char tempNumber[MAX_SPEED_DIAL_LEN + 1];
   int portNum;

   getHostAndPort(atCmd, host, port, portNum);
   if( !port ) {
      // check for host names that are 7 identical digits long
      // and dial from the corresponding speed dial slot
      bool speedDial = true;
      if( strlen(host) == MAGIC_SPEED_LEN && isdigit(host[0]) ) {
         for( int i = 0; i < MAGIC_SPEED_LEN; ++i ) {
            if( host[0] != host[i] ) {
               speedDial = false;
               break;
            }
         }
      } else {
         speedDial = false;
      }
      if( speedDial && settings.speedDial[host[0] - '0'][0] ) {
         strncpy(tempNumber, settings.speedDial[host[0] - '0'], MAX_SPEED_DIAL_LEN);
         tempNumber[MAX_SPEED_DIAL_LEN] = NUL;
         getHostAndPort(tempNumber, host, port, portNum);
      } else {
         // now check all the speed dial aliases for a match
         for( int i = 0; i < SPEED_DIAL_SLOTS; ++i ) {
            if( !strcasecmp(host, settings.alias[i]) ) {
               strncpy(tempNumber, settings.speedDial[i], MAX_SPEED_DIAL_LEN);
               tempNumber[MAX_SPEED_DIAL_LEN] = NUL;
               getHostAndPort(tempNumber, host, port, portNum);
               break;
            }
         }
      }
   }

   sessionTelnetType = settings.telnet;
   switch( host[0] ) {
      case '-':
         ++host;
			sessionTelnetType = NO_TELNET;
         break;
      case '=':
         ++host;
			sessionTelnetType = REAL_TELNET;
         break;
      case '+':
         ++host;
			sessionTelnetType = FAKE_TELNET;
         break;
   }

   yield();
   if( !settings.quiet && settings.extendedCodes ) {
      Serial.printf("DIALLING %s:%u\r\n", host, portNum);
      Serial.flush();
   }
   delay(2000);   // delay for ZMP to be able to detect CONNECT
   if( !Serial.available() && tcpClient.connect(host, portNum) ) {
      connectTime = millis();
      sendResult(R_CONNECT);
      digitalWrite(DCD, ACTIVE);
      state = ONLINE;
      yield();
   } else {
      sendResult(R_NO_CARRIER);
      digitalWrite(DCD, !ACTIVE);
   }
   atCmd[0] = NUL;
   return atCmd;
}

//
// ATE? query command mode echo status
// ATE0 disable command mode local echo
// ATE1 enable command mode local echo
//
char *doEcho(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.echo);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
      case '1':
      case NUL:
         settings.echo = atCmd[0] == '1';
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
// ATGEThttp://host[/path]: fetch a web page
//
// NOTE: http only: no https support
//
char *httpGet(char *atCmd) {
   char *host, *path, *port;
   int portNum;
   port = strrchr(atCmd, ':');
   host = strstr(atCmd, "http://");
   if( !port || port == host + 4) {
      portNum = HTTP_PORT;
   } else {
      portNum = atoi(port + 1);
      *port = NUL;
   }
   if( !host ) {
      sendResult(R_ERROR);
      return atCmd;
   } else {
      host += 7; // skip over http://
      path = strchr(host, '/');
   }
   if( path ) {
      *path = NUL;
      ++path;
   }
#if DEBUG
   Serial.print(F("Getting path /"));
   if( path ) {
      Serial.print(path);
   }
   Serial.printf(" from port %u of host %s...\r\n", portNum, host);
#endif
   // Establish connection
   if( !tcpClient.connect(host, portNum) ) {
      sendResult(R_NO_CARRIER);
      digitalWrite(DCD, !ACTIVE);
   } else {
      connectTime = millis();
      sendResult(R_CONNECT);
      digitalWrite(DCD, ACTIVE);
      state = ONLINE;

      // Send a HTTP request before continuing the connection as usual
      bytesOut += tcpClient.print(F("GET /"));
      if( path ) {
         bytesOut += tcpClient.print(path);
      }
      bytesOut += tcpClient.print(F(" HTTP/1.1\r\nHost: "));
      bytesOut += tcpClient.print(host);
      bytesOut += tcpClient.print(F("\r\nConnection: close\r\n\r\n"));
   }
   atCmd[0] = NUL;
   return atCmd;
}

//
// ATH go offline (if connected to a host)
//
char *hangup(char *atCmd) {
   if( atCmd[0] ) {
      ++atCmd;
   }
   if( tcpClient.connected() ) {
      endCall();
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}

//
// AT? help: paged output, uses dual columns if defined screen width
// is at least 80 characters, single columns if less.
//
// There must be an even number of help strings defined. If you end up
// with an odd number of strings, add an empty string ("") at the end
// to pad things out.
//
const char helpStr01[] PROGMEM = "Help..........: AT?";
const char helpStr02[] PROGMEM = "Repeat command: A/";
const char helpStr03[] PROGMEM = "Answer call...: ATA";
const char helpStr04[] PROGMEM = "WiFi connect..: ATCn";
const char helpStr05[] PROGMEM = "Speed dial....: ATDSn";
const char helpStr06[] PROGMEM = "Dial host.....: ATDThost[:port]";
const char helpStr07[] PROGMEM = "Command echo..: ATEn";
const char helpStr08[] PROGMEM = "HTTP get......: ATGEThttp://host[/page]";
const char helpStr09[] PROGMEM = "Hang up.......: ATH";
const char helpStr10[] PROGMEM = "Network info..: ATI";
const char helpStr11[] PROGMEM = "Handle Telnet.: ATNETn";
const char helpStr12[] PROGMEM = "Leave cmd mode: ATO";
const char helpStr13[] PROGMEM = "Quiet mode....: ATQn";
const char helpStr14[] PROGMEM = "NIST date.time: ATRD/ATRT";
const char helpStr15[] PROGMEM = "Auto answer...: ATS0=n";
const char helpStr16[] PROGMEM = "Verbose mode..: ATVn";
const char helpStr17[] PROGMEM = "Extended codes: ATXn";
const char helpStr18[] PROGMEM = "Modem reset...: ATZ";
const char helpStr19[] PROGMEM = "Fact. defaults: AT&F";
const char helpStr20[] PROGMEM = "Flow control..: AT&Kn";
const char helpStr21[] PROGMEM = "Server passwd.: AT&R=server password";
const char helpStr22[] PROGMEM = "Show settings.: AT&Vn";
const char helpStr23[] PROGMEM = "Update NVRAM..: AT&W";
const char helpStr24[] PROGMEM = "Set speed dial: AT&Zn=host[:port],alias";
const char helpStr25[] PROGMEM = "Auto execute..: AT$AE=AT command";
const char helpStr26[] PROGMEM = "Busy message..: AT$BM=busy message";
const char helpStr27[] PROGMEM = "mDNS name.....: AT$MDNS=mDNS name";
const char helpStr28[] PROGMEM = "WiFi password.: AT$PASS=WiFi password";
const char helpStr29[] PROGMEM = "Serial speed..: AT$SB=n";
const char helpStr30[] PROGMEM = "Server port...: AT$SP=n";
const char helpStr31[] PROGMEM = "WiFi SSID.....: AT$SSID=ssid";
const char helpStr32[] PROGMEM = "Data config...: AT$SU=dps";
const char helpStr33[] PROGMEM = "Location......: AT$TTL=telnet location";
const char helpStr34[] PROGMEM = "Terminal size.: AT$TTS=WxH";
const char helpStr35[] PROGMEM = "Terminal type.: AT$TTY=terminal type";
const char helpStr36[] PROGMEM = "Startup wait..: AT$W=n";
const char helpStr37[] PROGMEM = "";
const char helpStr38[] PROGMEM = "";
const char helpStr39[] PROGMEM = "Query most commands followed by '?'";
const char helpStr40[] PROGMEM = "e.g. ATQ?, AT&K?, AT$SSID?";

const char* const helpStrs[] PROGMEM = {
	helpStr01, helpStr02, helpStr03, helpStr04, helpStr05, helpStr06,
	helpStr07, helpStr08, helpStr09, helpStr10, helpStr11, helpStr12,
	helpStr13, helpStr14, helpStr15, helpStr16, helpStr17, helpStr18,
	helpStr19, helpStr20, helpStr21, helpStr22, helpStr23, helpStr24,
	helpStr25, helpStr26, helpStr27, helpStr28, helpStr29, helpStr30,
	helpStr31, helpStr32, helpStr33, helpStr34, helpStr35, helpStr36,
	helpStr37, helpStr38, helpStr39, helpStr40
};
#define NUM_HELP_STRS (sizeof(helpStrs) / sizeof(helpStrs[0]))

char *showHelp(char *atCmd) {
	char helpLine[80], helpLine1[80], helpLine2[80];

   PagedOut(F("AT Command Summary:"), true);
   if( settings.width >= 80 ) {
		// dual columns
		for( int i=0; i<NUM_HELP_STRS/2; ++i ) {
			strncpy_P(helpLine1, helpStrs[i], (sizeof helpLine1)-1);
			helpLine[(sizeof helpLine1)-1] = 0;
			strncpy_P(helpLine2, helpStrs[i+NUM_HELP_STRS/2], sizeof helpLine2);
			helpLine[(sizeof helpLine2)-1] = 0;
			snprintf(
				helpLine,
				sizeof helpLine,
				"%-40s%s",
				helpLine1,
				helpLine2);
			if( PagedOut(helpLine) ) {
				break;				// user responded with ^C, quit
			}
		}
	} else {
		// single column
		for( int i=0; i<NUM_HELP_STRS; ++i ) {
			strncpy_P(helpLine,helpStrs[i], (sizeof helpLine)-1);
			helpLine[(sizeof helpLine)-1] = 0;
			if( PagedOut(helpLine) ) {
				break;				// user responded with ^C, quit
			}
		}
	}
   if( !atCmd[0] ) {
      sendResult(R_OK);
   }
   return atCmd;
}

//
// ATI: show network info
//
char *showNetworkInfo(char *atCmd) {
   char infoLine[80];
   size_t maxCatChars;

	do {		// a Q&D hack to allow ^C to terminate the output at the
		      // end of a page
		if( PagedOut(F("Retro WiFi modem"), true) ) break;
		if( PagedOut("Build......: " __DATE__ " " __TIME__) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Baud.......: %lu"), settings.serialSpeed);
		if( PagedOut(infoLine) ) break;
		strncpy_P(infoLine, PSTR("WiFi status: "), (sizeof infoLine)-1);
		infoLine[(sizeof infoLine)-1] = 0;
		maxCatChars = (sizeof infoLine) - strlen(infoLine);
		switch( WiFi.status() ) {
			case WL_CONNECTED:
				strncat_P(infoLine, PSTR("CONNECTED"), maxCatChars);
				break;
			case WL_IDLE_STATUS:
				strncat_P(infoLine, PSTR("OFFLINE"), maxCatChars);
				break;
			case WL_CONNECT_FAILED:
				strncat_P(infoLine, PSTR("CONNECT FAILED"), maxCatChars);
				break;
			case WL_NO_SSID_AVAIL:
				strncat_P(infoLine, PSTR("SSID UNAVAILABLE"), maxCatChars);
				break;
			case WL_CONNECTION_LOST:
				strncat_P(infoLine, PSTR("CONNECTION LOST"), maxCatChars);
				break;
			case WL_DISCONNECTED:
				strncat_P(infoLine, PSTR("DISCONNECTED"), maxCatChars);
				break;
			case WL_SCAN_COMPLETED:
				strncat_P(infoLine, PSTR("SCAN COMPLETED"), maxCatChars);
				break;
			default:
				snprintf_P(infoLine, sizeof infoLine, PSTR("WiFi status: UNKNOWN (%u)"), WiFi.status());
				break;
		}
		infoLine[(sizeof infoLine)-1] = 0;
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("SSID.......: %s"), WiFi.SSID().c_str());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("MAC address: %s"), WiFi.macAddress().c_str());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("IP address.: %s"), WiFi.localIP().toString().c_str());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Gateway....: %s"), WiFi.gatewayIP().toString().c_str());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Subnet mask: %s"), WiFi.subnetMask().toString().c_str());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("mDNS name..: %s.local"), settings.mdnsName);
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Server port: %u"), settings.listenPort);
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Bytes in...: %lu"), bytesIn);
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Bytes out..: %lu"), bytesOut);
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Heap free..: %lu"), ESP.getFreeHeap());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Sketch size: %lu"), ESP.getSketchSize());
		if( PagedOut(infoLine) ) break;
		snprintf_P(infoLine, sizeof infoLine, PSTR("Sketch free: %lu"), ESP.getFreeSketchSpace() % (1024L * 1024L));
		if( PagedOut(infoLine) ) break;
		if( tcpClient.connected() ) {
			snprintf_P(infoLine, sizeof infoLine, PSTR("Call status: CONNECTED TO %s"), tcpClient.remoteIP().toString().c_str());
			if( PagedOut(infoLine) ) break;
			snprintf_P(infoLine, sizeof infoLine, PSTR("Call length: %s"), connectTimeString());
			if( PagedOut(infoLine) ) break;
		} else {
			if( PagedOut(F("Call status: NOT CONNECTED")) ) break;
		}
	} while( false );
   if( !atCmd[0] ) {
      sendResult(R_OK);
   }
   return atCmd;
}

//
// ATNET? query Telnet handling status
// ATNET0 turn off Telnet handling
// ATNET1 turn on true Telnet handling
// ATNET2 turn on BBS (fake) Telnet handling
//
char *doTelnetMode(char* atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.telnet);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case NUL:
      case '0':   // no Telnet processing
      case '1':   // real Telnet (double IACs, add NUL after CR)
      case '2':   // fake (BBS) Telnet (double IACs)
         if( atCmd[0] ) {
            settings.telnet = atCmd[0] - '0';
            ++atCmd;
         } else {
            settings.telnet = NO_TELNET;
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
// ATO go online (if connected to a host)
//
char *goOnline(char *atCmd) {
   if( tcpClient.connected() ) {
      state = ONLINE;
      sendResult(R_CONNECT);
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}

//
// ATQ? query quiet mode status
// ATQ0 disable quiet mode (results issued)
// ATQ1 enable quiet mode (no results issued)
//
char *doQuiet(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.quiet);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
      case '1':
      case NUL:
         settings.quiet = atCmd[0] == '1';
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
// ATRD Displays the UTC date and time from NIST in the format
// ATRT "YY-MM-DD HH:MM:SS"
//
char *doDateTime(char *atCmd) {
   bool ok = false;
   if( !tcpClient.connected() ) {
      char result[80], *ptr;
      if( tcpClient.connect(NIST_HOST, NIST_PORT) ) {
         digitalWrite(DCD, ACTIVE);
         // read date/time from NIST
         size_t len = tcpClient.readBytes(result, 1);
         if( len == 1 && result[0] == '\n' ) {  // leading LF
            len = tcpClient.readBytesUntil('\n', result, (sizeof result) - 1);
            if( len ) {                      // string read?
               result[len] = NUL;
               ptr = strtok(result, " ");
               if( ptr ) {                   // found Julian day?
                  ptr = strtok(NULL, " ");
                  if( ptr ) {                // found date?
                     Serial.print(ptr);
                     Serial.print(' ');
                     ptr = strtok(NULL, " ");
                     if( ptr ) {             // found time?
                        Serial.println(ptr);
                        ok = true;
                     }
                  }
               }
            }
         }
         tcpClient.stop();
         digitalWrite(DCD, !ACTIVE);
      }
   }
   if( ok ) {
      if( !atCmd[0] ) {
         sendResult(R_OK);
      }
   } else {
      sendResult(R_ERROR);
   }
   return atCmd;
}

//
// ATS0?  query auto answer configuration
// ATS0=0 disable auto answer
// ATS0=n enable auto answer after n rings
//
char *doAutoAnswerConfig(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.autoAnswer);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         if( isDigit(atCmd[0]) ) {
            settings.autoAnswer = atoi(atCmd);
            while( isDigit(atCmd[0]) ) {
               ++atCmd;
            }
            if( !atCmd[0] ) {
               sendResult(R_OK);
            }
         } else {
            sendResult(R_ERROR);
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// ATV? query verbose mode status
// ATV0 disable verbose mode (results are shown as numbers)
// ATV1 enable verbose nmode (results are shown as text)
//
char *doVerbose(char* atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.verbose);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
      case '1':
      case NUL:
         settings.verbose = atCmd[0] == '1';
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
// ATX? query extended results
// ATX0 disable extended results
// ATX1 enable extended results
//
char *doExtended(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.extendedCodes);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '0':
      case '1':
      case NUL:
         settings.extendedCodes = atCmd[0] == '1';
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
// ATZ restart the sketch
//
char *resetToNvram(char *atCmd) {
   Serial.flush();                     // allow for CR/LF to finish
   digitalWrite(TXEN, HIGH);           // before disabling the TX output
   ESP.restart();
   return atCmd;                       // should never actually get here...
}

