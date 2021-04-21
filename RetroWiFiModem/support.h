void doAtCmds(char *atCmd);             // forward delcaration

//
// We're in local command mode. Assemble characters from the
// serial port into a buffer for processing.
//
void inAtCommandMode() {
   char c;

   // get AT command
   if( Serial.available() ) {
      c = Serial.read();

      if( c == LF || c == CR ) {       // command finished?
         if( settings.echo ) {
            Serial.println();
         }
         doAtCmds(atCmd);               // yes, then process it
         atCmd[0] = NUL;
         atCmdLen = 0;
      } else if( (c == BS || c == DEL) && atCmdLen > 0 ) {
         atCmd[--atCmdLen] = NUL;      // remove last character
         if( settings.echo ) {
            Serial.print(F("\b \b"));
         }
      } else if( c == '/' && atCmdLen == 1 && toupper(atCmd[0]) == 'A' && lastCmd[0] != NUL ) {
         if( settings.echo ) {
            Serial.println(c);
         }
         strncpy(atCmd, lastCmd, sizeof atCmd);
         atCmd[MAX_CMD_LEN] = NUL;
         doAtCmds(atCmd);                  // repeat last command
         atCmd[0] = NUL;
         atCmdLen = 0;
      } else if( c >=' ' && c <= '~' ) {  // printable char?
         if( atCmdLen < MAX_CMD_LEN ) {
            atCmd[atCmdLen++] = c;        // add to command string
            atCmd[atCmdLen] = NUL;
         }
         if( settings.echo ) {
            Serial.print(c);
         }
      }
   }
}

//
// send serial data to the TCP client
//
void sendSerialData() {
   static unsigned long lastSerialData = 0;
   // in telnet mode, we might have to escape every single char,
   // so don't use more than half the buffer
   size_t maxBufSize = (sessionTelnetType != NO_TELNET) ? TX_BUF_SIZE / 2 : TX_BUF_SIZE;
   size_t len = Serial.available();
   if( len > maxBufSize) {
      len = maxBufSize;
   }
   Serial.readBytes(txBuf, len);

   if( escCount || (millis() - lastSerialData >= GUARD_TIME) ) {
      // check for the online escape sequence
      // +++ with a 1 second pause before and after
      for( size_t i = 0; i < len; ++i ) {
         if( txBuf[i] == settings.escChar ) {
            if( ++escCount == ESC_COUNT ) {
               guardTime = millis() + GUARD_TIME;
            } else {
               guardTime = 0;
            }
         } else {
            escCount = 0;
         }
      }
   } else {
      escCount = 0;
   }
   lastSerialData = millis();

   // in Telnet mode, escape every IAC (0xff) by inserting another
   // IAC after it into the buffer (this is why we only read up to
   // half of the buffer in Telnet mode)
   //
   // also in Telnet mode, escape every CR (0x0D) by inserting a NUL
   // after it into the buffer
   if( sessionTelnetType != NO_TELNET ) {
      for( int i = len - 1; i >= 0; --i ) {
         if( txBuf[i] == IAC ) {
            memmove( txBuf + i + 1, txBuf + i, len - i);
            ++len;
         } else if( txBuf[i] == CR && sessionTelnetType == REAL_TELNET ) {
            memmove( txBuf + i + 1, txBuf + i, len - i);
            txBuf[i + 1] = NUL;
            ++len;
         }
      }
   }
   bytesOut += tcpClient.write(txBuf, len);
   yield();
}

//
// Receive data from the TCP client
//
// We do some limited processing of in band Telnet commands.
// Specifically, we handle the following commanads: BINARY,
// ECHO, SUP_GA (suppress go ahead), TTYPE (terminal type),
// TSPEED (terminal speed), LOC (terminal location) and
// NAWS (terminal columns and rows).
//
int receiveTcpData() {
   static char lastc = 0;
   int rxByte = tcpClient.read();
   ++bytesIn;

   if( sessionTelnetType != NO_TELNET && rxByte == IAC ) {
      rxByte = tcpClient.read();
      ++bytesIn;
      if( rxByte != IAC ) { // 2 times 0xff is just an escaped real 0xff
         // rxByte has now the first byte of the actual non-escaped control code
#if DEBUG
         Serial.print('[');
         Serial.print(rxByte);
         Serial.print(',');
#endif
         uint8_t cmdByte1 = rxByte;
         rxByte = tcpClient.read();
         ++bytesIn;
         uint8_t cmdByte2 = rxByte;
#if DEBUG
         Serial.print(rxByte);
#endif
         switch( cmdByte1 ) {
            case DO:
               switch( cmdByte2 ) {
                  case BINARY:
                  case ECHO:
                  case SUP_GA:
                  case TTYPE:
                  case TSPEED:
                     bytesOut += tcpClient.write(IAC);      // we will say what
                     bytesOut += tcpClient.write(WILL);     // the terminal is
                     bytesOut += tcpClient.write(cmdByte2);
                     break;
                  case LOC:
                  case NAWS:
                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(WILL);
                     bytesOut += tcpClient.write(cmdByte2);

                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(SB);
                     bytesOut += tcpClient.write(cmdByte2);
                     switch( cmdByte2 ) {
                        case NAWS:     // window size
                           bytesOut += tcpClient.write((uint8_t)0);
                           bytesOut += tcpClient.write(settings.width);
                           bytesOut += tcpClient.write((uint8_t)0);
                           bytesOut += tcpClient.write(settings.height);
                           break;
                        case LOC:      // terminal location
                           bytesOut += tcpClient.print(settings.location);
                           break;
                     }
                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(SE);
                     break;
                  default:
                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(WONT);
                     bytesOut += tcpClient.write(cmdByte2);
                     break;
               }
               break;
            case WILL:
               // Server wants to do option, allow most
               bytesOut += tcpClient.write(IAC);
               switch( cmdByte2 ) {
                  case LINEMODE:
                  case NAWS:
                  case LFLOW:
                  case NEW_ENVIRON:
                  case XDISPLOC:
                     bytesOut += tcpClient.write(DONT);
                     break;
                  default:
                     bytesOut += tcpClient.write(DO);
                     break;
               }
               bytesOut += tcpClient.write(cmdByte2);
               break;
            case SB:
               switch( cmdByte2 ) {
                  case TTYPE:
                  case TSPEED:
                     while( tcpClient.read() != SE ) { // discard rest of cmd
                        ++bytesIn;
                     }
                     ++bytesIn;
                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(SB);
                     bytesOut += tcpClient.write(cmdByte2);
                     bytesOut += tcpClient.write(VLSUP);
                     switch( cmdByte2 ) {
                        case TTYPE:    // terminal type
                           bytesOut += tcpClient.print(settings.terminal);
                           break;
                        case TSPEED:   // terminal speed
                           bytesOut += tcpClient.print(settings.serialSpeed);
                           bytesOut += tcpClient.print(',');
                           bytesOut += tcpClient.print(settings.serialSpeed);
                           break;
                     }
                     bytesOut += tcpClient.write(IAC);
                     bytesOut += tcpClient.write(SE);
                     break;
                  default:
                     break;
               }
               break;
         }
         rxByte = -1;
      }
#if DEBUG
      Serial.print(']');
#endif
   }
   // Telnet sends <CR> as <CR><NUL>
   // We filter out that <NUL> here
   if( lastc == CR && (char)rxByte == 0 && sessionTelnetType == REAL_TELNET ) {
      rxByte = -1;
   }
   lastc = (char)rxByte;
   return rxByte;
}

//
// return a pointer to a string containing the connect time of the last session
//
char *connectTimeString(void) {
   unsigned long now = millis();
   int hours, mins, secs;
   static char result[9];

   if( connectTime ) {
      secs = (now - connectTime) / 1000;
      mins = secs / 60;
      hours = mins / 60;
      secs %= 60;
      mins %= 60;
   } else {
      hours = mins = secs = 0;
   }
   result[0] = (char)(hours / 10 + '0');
   result[1] = (char)(hours % 10 + '0');
   result[2] = ':';
   result[3] = (char)(mins / 10 + '0');
   result[4] = (char)(mins % 10 + '0');
   result[5] = ':';
   result[6] = (char)(secs / 10 + '0');
   result[7] = (char)(secs % 10 + '0');
   result[8] = NUL;
   return result;
}

//
// print a result code/string to the serial port
//
void sendResult(int resultCode) {
   if( !settings.quiet ) {             // quiet mode on?
      Serial.println();                // no, we're going to display something
      if( !settings.verbose ) {
         if( resultCode == R_RING_IP ) {
            resultCode = R_RING;
         }
         Serial.println(resultCode);   // not verbose, just print the code #
      } else {
         switch( resultCode ) {        // possible extra info for CONNECT and
                                       // NO CARRIER if extended codes are
            case R_CONNECT:            // enabled
               Serial.print(FPSTR(connectStr));
               if( settings.extendedCodes ) {
                  Serial.print(' ');
                  Serial.print(settings.serialSpeed);
               }
               Serial.println();
               break;

            case R_NO_CARRIER:
               Serial.print(FPSTR(noCarrierStr));
               if( settings.extendedCodes ) {
                  Serial.printf(" (%s)", connectTimeString());
               }
               Serial.println();
               break;

            case R_ERROR:
               Serial.println(FPSTR(errorStr));
               lastCmd[0] = NUL;
               memset(atCmd, 0, sizeof atCmd);
               break;

            case R_RING_IP:
               Serial.print(FPSTR(ringStr));
               if( settings.extendedCodes ) {
                  Serial.print(' ');
                  Serial.print(tcpClient.remoteIP().toString());
               }
               Serial.println();
               break;

            default:
               Serial.println(FPSTR(resultCodes[resultCode]));
               break;
         }
      }
   } else if( resultCode == R_ERROR ) {
      lastCmd[0] = NUL;
      memset(atCmd, 0, sizeof atCmd);
   }
   if( resultCode == R_NO_CARRIER || resultCode == R_NO_ANSWER ) {
      sessionTelnetType = settings.telnet;
   }
}

//
// terminate an active call
//
void endCall() {
   state = CMD_NOT_IN_CALL;
   tcpClient.stop();
   sendResult(R_NO_CARRIER);
   connectTime = 0;
   digitalWrite(DCD, !ACTIVE);
   escCount = 0;
}

//
// Check for an incoming TCP session. There are 3 scenarios:
//
// 1. We're already in a call, or auto answer is disabled and the
//    ring count exceeds the limit: tell the caller we're busy.
// 2. We're not in a call and auto answer is disabled, or the #
//    of rings is less than the auto answer count: either start
//    or continue ringing.
// 3. We're no in a call, auto answer is enabled and the # of rings
//    is at least the auto answer count: answer the call.
//
void checkForIncomingCall() {
   if( settings.listenPort && tcpServer.hasClient() ) {
      if( state != CMD_NOT_IN_CALL || (!settings.autoAnswer && ringCount > MAGIC_ANSWER_RINGS) ) {
         WiFiClient droppedClient = tcpServer.available();
         if( settings.busyMsg[0] ) {
            droppedClient.println(settings.busyMsg);
            droppedClient.print(F("Current call length: "));
            droppedClient.println(connectTimeString());
         } else {
            droppedClient.println(F("BUSY"));
         }
         droppedClient.println();
         droppedClient.flush();
         droppedClient.stop();
         digitalWrite(RI, !ACTIVE);
         ringCount = 0;
         ringing = false;
      } else if( !settings.autoAnswer || ringCount < settings.autoAnswer ) {
         if( !ringing ) {
            ringing = true;            // start ringing
            ringCount = 1;
            digitalWrite(RI, ACTIVE);
            if( !settings.autoAnswer || ringCount < settings.autoAnswer ) {
               sendResult(R_RING);     // only show RING if we're not just
            }                          // about to answer
            nextRingMs = millis() + RING_INTERVAL;
         } else if( millis() > nextRingMs ) {
            if( digitalRead(RI) == ACTIVE ) {
               digitalWrite(RI, !ACTIVE);
            } else {
               ++ringCount;
               digitalWrite(RI, ACTIVE);
               if( !settings.autoAnswer || ringCount < settings.autoAnswer ) {
                  sendResult(R_RING);
               }
            }
            nextRingMs = millis() + RING_INTERVAL;
         }
      } else if( settings.autoAnswer && ringCount >= settings.autoAnswer ) {
         digitalWrite(RI, !ACTIVE);
         tcpClient = tcpServer.available();
         if( settings.telnet != NO_TELNET ) {
            tcpClient.write(IAC);      // incantation to switch
            tcpClient.write(WILL);     // from line mode to
            tcpClient.write(SUP_GA);   // character mode
            tcpClient.write(IAC);
            tcpClient.write(WILL);
            tcpClient.write(ECHO);
            tcpClient.write(IAC);
            tcpClient.write(WONT);
            tcpClient.write(LINEMODE);
         }
         sendResult(R_RING_IP);
         if( settings.serverPassword[0]) {
            tcpClient.print(F("\r\nPassword: "));
            state = PASSWORD;
            passwordTries = 0;
            passwordLen = 0;
            password[0] = NUL;
         } else {
            delay(1000);
            state = ONLINE;
            sendResult(R_CONNECT);
         }
         connectTime = millis();
         digitalWrite(DCD, ACTIVE);
      }
   } else if( ringing ) {
      digitalWrite(RI, !ACTIVE);
      ringing = false;
      ringCount = 0;
   }
}

//
// setup for OTA sketch updates
//
void setupOTAupdates() {
   ArduinoOTA.setHostname(settings.mdnsName);

   ArduinoOTA.onStart([]() {
      Serial.println(F("OTA upload start"));
      digitalWrite(DSR, !ACTIVE);
   });

   ArduinoOTA.onEnd([]() {
      Serial.println(F("OTA upload end - programming"));
      Serial.flush();                  // allow serial output to finish
      digitalWrite(TXEN, HIGH);        // before disabling the TX output
   });

   ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      unsigned int pct = progress / (total / 100);
      static unsigned int lastPct = 999;
      if( pct != lastPct ) {
         lastPct = pct;
         if( settings.serialSpeed >= 4800 || pct % 10 == 0 ) {
            Serial.printf("Progress: %u%%\r", pct);
         }
      }
   });

   ArduinoOTA.onError([](ota_error_t errorno) {
      Serial.print(F("OTA Error - "));
      switch( errorno ) {
         case OTA_AUTH_ERROR:
            Serial.println(F("Auth failed"));
            break;
         case OTA_BEGIN_ERROR:
            Serial.println(F("Begin failed"));
            break;
         case OTA_CONNECT_ERROR:
            Serial.println(F("Connect failed"));
            break;
         case OTA_RECEIVE_ERROR:
            Serial.println(F("Receive failed"));
            break;
         case OTA_END_ERROR:
            Serial.println(F("End failed"));
            break;
         default:
            Serial.printf("Unknown (%u)\r\n", errorno);
            break;
      }
      sendResult(R_ERROR);
   });
   ArduinoOTA.begin();
}

//
// Return the SerialConfig value for the current data bits/parity/stop bits
// setting.
//
SerialConfig getSerialConfig(void) {
   uint8_t serialConfig = 0;
   switch( settings.dataBits ) {
      case 5:
         serialConfig = serialConfig = UART_NB_BIT_5 | (~UART_NB_BIT_MASK & serialConfig);
         break;
      case 6:
         serialConfig = serialConfig = UART_NB_BIT_6 | (~UART_NB_BIT_MASK & serialConfig);
         break;
      case 7:
         serialConfig = serialConfig = UART_NB_BIT_7 | (~UART_NB_BIT_MASK & serialConfig);
         break;
      case 8:
      default:
         serialConfig = serialConfig = UART_NB_BIT_8 | (~UART_NB_BIT_MASK & serialConfig);
         break;
   }
   switch( settings.parity ) {
      case 'E':
         serialConfig = UART_PARITY_EVEN | (~UART_PARITY_MASK & serialConfig);
         break;
      case 'O':
         serialConfig = UART_PARITY_ODD | (~UART_PARITY_MASK & serialConfig);
         break;
      case 'N':
      default:
         serialConfig = UART_PARITY_NONE | (~UART_PARITY_MASK & serialConfig);
         break;
   }
   switch( settings.stopBits ) {
      case '2':
         serialConfig = UART_NB_STOP_BIT_2 | (~UART_NB_STOP_BIT_MASK & serialConfig);
         break;
      case '1':
      default:
         serialConfig = UART_NB_STOP_BIT_1 | (~UART_NB_STOP_BIT_MASK & serialConfig);
         break;
   }
   return (SerialConfig)serialConfig;
}

// As the ESP8266 is being used as a modem (DCE) in this application,
// I've reversed the naming of RTS/CTS to match what they'd be on
// a modem. The usual naming is correct if the ESP8266 is wired up as
// a DTE, but kept confusing me here as it's wired up as a DCE.
void setHardwareFlow(void) {
   // Enable flow control of DTE -> ESP8266 data with CTS
   // CTS on the EPS8266 is pin GPIO15 which is physical pin 16
   // CTS is an output and should be connected to CTS on the RS232
   // The ESP8266 has a 128 byte receive buffer,
   // so a threshold of 64 is half full
   pinMode(CTS, FUNCTION_4); // make pin U0CTS
   SET_PERI_REG_BITS(UART_CONF1(0), UART_RX_FLOW_THRHD, 64, UART_RX_FLOW_THRHD_S);
   SET_PERI_REG_MASK(UART_CONF1(0), UART_RX_FLOW_EN);

   // Enable flow control of ESP8266 -> DTE data with RTS
   // RTS on the EPS8266 is pin GPIO13 which is physical pin 7
   // RTS is an input and should be connected to RTS on the RS232
   pinMode(RTS, FUNCTION_4); // make pin U0RTS
   SET_PERI_REG_MASK(UART_CONF0(0), UART_TX_FLOW_EN);
}

// trim leading and trailing blanks from a string
void trim(char *str) {
   char *trimmed = str;
   // find first non blank character
   while( *trimmed && isSpace(*trimmed) ) {
      ++trimmed;
   }
   if( *trimmed ) {
      // trim off any trailing blanks
      for( int i = strlen(trimmed) - 1; i >= 0; --i ) {
         if( isSpace(trimmed[i]) ) {
            trimmed[i] = NUL;
         } else {
            break;
         }
      }
   }
   // shift string only if we had leading blanks
   if( str != trimmed ) {
      int i, len = strlen(trimmed);
      for( i = 0; i < len; ++i ) {
         str[i] = trimmed[i];
      }
      str[i] = NUL;
   }
}

//
// Parse a string in the form "hostname[:port]" and return
//
// 1. A pointer to the hostname
// 2. A pointer to the optional port
// 3. The numeric value of the port (if not specified, 23)
//
void getHostAndPort(char *number, char* &host, char* &port, int &portNum) {
   char *ptr;

   port = strrchr(number, ':');
   if( !port ) {
      portNum = TELNET_PORT;
   } else {
      *port++ = NUL;
      portNum = atoi(port);
   }
   host = number;
   while( *host && isSpace(*host) ) {
      ++host;
   }
   ptr = host;
   while( *ptr && !isSpace(*ptr) ) {
      ++ptr;
   }
   *ptr = NUL;
}

//
// Display the operational settings
//
void displayCurrentSettings(void) {
   Serial.println(F("Active Profile:")); yield();
   Serial.printf("Baud.......: %lu\r\n", settings.serialSpeed); yield();
   Serial.printf("SSID.......: %s\r\n", settings.ssid); yield();
   Serial.printf("Pass.......: %s\r\n", settings.wifiPassword); yield();
   Serial.printf("mDNS name..: %s.local\r\n", settings.mdnsName); yield();
   Serial.printf("Server port: %u\r\n", settings.listenPort); yield();
   Serial.printf("Busy msg...: %s\r\n", settings.busyMsg); yield();
   Serial.printf("E%u Q%u V%u X%u &K%u NET%u S0=%u\r\n",
      settings.echo, settings.quiet, settings.verbose,
      settings.extendedCodes, settings.rtsCts, settings.telnet,
      settings.autoAnswer); yield();

   Serial.println(F("Speed dial:"));
   for( int i = 0; i < SPEED_DIAL_SLOTS; ++i ) {
      if( settings.speedDial[i][0] ) {
         Serial.printf("%u: %s,%s\r\n",
            i, settings.speedDial[i], settings.alias[i]);
         yield();
      }
   }
}

//
// Display the settings stored in flash (NVRAM).
//
void displayStoredSettings(void) {
   bool v_bool;
   uint8_t v_uint8;
   uint16_t v_uint16;
   uint32_t v_uint32;
   char v_char16[16 + 1];
   char v_char32[32 + 1];
   char v_char50[50 + 1];
   char v_char64[64 + 1];
   char v_char80[80 + 1];
   Serial.println(F("Stored Profile:")); yield();
   Serial.printf("Baud.......: %lu\r\n", EEPROM.get(offsetof(struct Settings, serialSpeed),v_uint32)); yield();
   Serial.printf("SSID.......: %s\r\n", EEPROM.get(offsetof(struct Settings, ssid), v_char32)); yield();
   Serial.printf("Pass.......: %s\r\n", EEPROM.get(offsetof(struct Settings, wifiPassword), v_char64)); yield();
   Serial.printf("mDNS name..: %s.local\r\n", EEPROM.get(offsetof(struct Settings, mdnsName), v_char80)); yield();
   Serial.printf("Server port: %u\r\n", EEPROM.get(offsetof(struct Settings, listenPort), v_uint16)); yield();
   Serial.printf("Busy Msg...: %s\r\n", EEPROM.get(offsetof(struct Settings, busyMsg),v_char80)); yield();
   Serial.printf("E%u Q%u V%u X%u &K%u NET%u S0=%u\r\n",
      EEPROM.get(offsetof(struct Settings, echo), v_bool),
      EEPROM.get(offsetof(struct Settings, quiet), v_bool),
      EEPROM.get(offsetof(struct Settings, verbose), v_bool),
      EEPROM.get(offsetof(struct Settings, extendedCodes), v_bool),
      EEPROM.get(offsetof(struct Settings, rtsCts), v_bool),
      EEPROM.get(offsetof(struct Settings, telnet), v_bool),
      EEPROM.get(offsetof(struct Settings, autoAnswer), v_uint8));
   yield();

   Serial.println(F("Speed dial:"));
   int speedDialOffset = offsetof(struct Settings, speedDial);
   int aliasOffset = offsetof(struct Settings, alias);
   for (int i = 0; i < SPEED_DIAL_SLOTS; i++) {
      EEPROM.get(
         speedDialOffset + i * (MAX_SPEED_DIAL_LEN + 1),
         v_char50
      );
      if( v_char50[0] ) {
         Serial.printf("%u: %s,%s\r\n",
            i,
            v_char50,
            EEPROM.get(aliasOffset + i * (MAX_ALIAS_LEN + 1), v_char16));
         yield();
      }
   }
}

//
// Password is set for incoming connections.
// Allow 3 tries or 60 seconds before hanging up.
//
void inPasswordMode() {
   if( tcpClient.available() ) {
      int c = receiveTcpData();
      switch( c ) {
         case -1:    // telnet control sequence: no data returned
            break;

         case LF:
         case CR:
            tcpClient.println();
            if( strcmp(settings.serverPassword, password) ) {
               ++passwordTries;
               password[0] = NUL;
               passwordLen = 0;
               tcpClient.print(F("\r\nPassword: "));
            } else {
               state = ONLINE;
               sendResult(R_CONNECT);
               tcpClient.println(F("Welcome"));
            }
            break;

         case BS:
         case DEL:
            if( passwordLen ) {
               password[--passwordLen] = NUL;
               tcpClient.print(F("\b \b"));
            }
            break;

         default:
            if( isprint((char)c) && passwordLen < MAX_PWD_LEN ) {
               tcpClient.print('*');
               password[passwordLen++] = (char)c;
               password[passwordLen] = 0;
            }
            break;
      }
   }
   if( millis() - connectTime > PASSWORD_TIME || passwordTries >= PASSWORD_TRIES ) {
      tcpClient.println(F("Good-bye"));
      endCall();
   } else if( !tcpClient.connected() ) {   // no client?
      endCall();                           // then hang up
   }
}

//
// Paged text output: using the terminal rows defined in
// settings.height, these routines pause the output when
// a screen full of text has been shown.
//
// Call with PagedOut("text", true); to initialise the
// line counter.
//
static uint8_t numLines = 0;

static bool PagedOut(const char *str, bool reset=false) {
	char c = ' ';

	if( reset ) {
		numLines = 0;
	}
	if( numLines >= settings.height-1 ) {
		Serial.print(F("[More]"));
		while( !Serial.available() );
		c = Serial.read();
		Serial.print(F("\r      \r"));
		numLines = 0;
	}
	if( c != CTLC ) {
		Serial.println(str);
		yield();
		++numLines;
	}
	return c == CTLC;
}

static bool PagedOut(const __FlashStringHelper *flashStr, bool reset=false) {
	char str[80];

	strncpy_P(str, (PGM_P)flashStr, sizeof str);
	str[(sizeof str)-1] = 0;
	return PagedOut(str, reset);
}

