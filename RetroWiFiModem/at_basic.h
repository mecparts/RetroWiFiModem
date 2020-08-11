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
            if( settings.extendedCodes ) {
               Serial.print(F("CONNECTING TO SSID "));
               Serial.print(settings.ssid);
            }
            WiFi.begin(settings.ssid, settings.wifiPassword);
            for( int i = 0; i < 50; ++i ) {
               delay(500);
               if( settings.extendedCodes ) {
                  Serial.print('.');
               }
               if( WiFi.status() == WL_CONNECTED ) {
                  break;
               }
            }
            if( settings.extendedCodes ) {
               Serial.println();
            }
            if( WiFi.status() != WL_CONNECTED ) {
               sendResult(R_ERROR);
            } else {
               digitalWrite(DSR, ACTIVE);  // modem is ready
               yield();
               if( settings.extendedCodes ) {
                  Serial.printf("CONNECTED TO %s IP ADDRESS: %s\r\n",
                     settings.ssid, WiFi.localIP().toString().c_str());
               }
               if( !atCmd[0] ) {
                  sendResult(R_OK);
               }
            }
         } else {
            if( settings.extendedCodes ) {
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
   if( settings.extendedCodes ) {
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
// AT? help
//
char *showHelp(char *atCmd) {
   Serial.println(F("AT Command Summary:"));  yield();
   Serial.println(F("Help..........: AT?                     Server passwd.: AT&R=server password")); yield();
   Serial.println(F("Repeat command: A/                      Show settings.: AT&Vn")); yield();
   Serial.println(F("Answer call...: ATA                     Update NVRAM..: AT&W")); yield();
   Serial.println(F("WiFi connect..: ATCn                    Set speed dial: AT&Zn=host[:port],alias")); yield();
   Serial.println(F("Speed dial....: ATDSn                   Auto execute..: AT$AE=AT command")); yield();
   Serial.println(F("Dial host.....: ATDThost[:port]         Busy message..: AT$BM=busy message")); yield();
   Serial.println(F("Command echo..: ATEn                    mDNS name.....: AT$MDNS=mDNS name")); yield();
   Serial.println(F("HTTP get......: ATGEThttp://host[/page] WiFi password.: AT$PASS=WiFi password")); yield();
   Serial.println(F("Hang up.......: ATH                     Serial speed..: AT$SB=n")); yield();
   Serial.println(F("Network info..: ATI                     Server port...: AT$SP=n")); yield();
   Serial.println(F("Handle Telnet.: ATNETn                  WiFi SSID.....: AT$SSID=ssid")); yield();
   Serial.println(F("Leave cmd mode: ATO                     Data config...: AT$SU=dps")); yield();
   Serial.println(F("Quiet mode....: ATQn                    Location......: AT$TTL=telnet location")); yield();
   Serial.println(F("NIST date.time: ATRD/ATRT               Terminal size.: AT$TTS=WxH")); yield();
   Serial.println(F("Auto answer...: ATS0=n                  Terminal type.: AT$TTY=terminal type")); yield();
   Serial.println(F("Verbose mode..: ATVn                    Startup wait..: AT$W=n")); yield();
   Serial.println(F("Extended codes: ATXn")); yield();
   Serial.println(F("Modem reset...: ATZ")); yield();
   Serial.println(F("Fact. defaults: AT&F                    Query most commands followed by '?'")); yield();
   Serial.println(F("Flow control..: AT&Kn                   e.g. ATQ?, AT&K?, AT$SSID?")); yield();
   if( !atCmd[0] ) {
      sendResult(R_OK);
   }
   return atCmd;
}

//
// ATI: show network info
//
char *showNetworkInfo(char *atCmd) {
   Serial.println(F("Retro WiFi modem")); yield();
   Serial.println("Build......: " __DATE__ " " __TIME__); yield();
   Serial.printf("Baud.......: %lu\r\n", settings.serialSpeed); yield();
   Serial.print(F("WiFi status: "));
   switch( WiFi.status() ) {
      case WL_CONNECTED:
         Serial.println(F("CONNECTED"));
         break;
      case WL_IDLE_STATUS:
         Serial.println(F("OFFLINE"));
         break;
      case WL_CONNECT_FAILED:
         Serial.println(F("CONNECT FAILED"));
         break;
      case WL_NO_SSID_AVAIL:
         Serial.println(F("SSID UNAVAILABLE"));
         break;
      case WL_CONNECTION_LOST:
         Serial.println(F("CONNECTION LOST"));
         break;
      case WL_DISCONNECTED:
         Serial.println(F("DISCONNECTED"));
         break;
      case WL_SCAN_COMPLETED:
         Serial.println(F("SCAN COMPLETED"));
         break;
      default:
         Serial.printf("UNKNOWN (%u)\r\n", WiFi.status());
         break;
   }
   yield();
   Serial.printf("SSID.......: %s\r\n", WiFi.SSID().c_str()); yield();
   Serial.printf("MAC address: %s\r\n", WiFi.macAddress().c_str()); yield();
   Serial.printf("IP address.: %s\r\n", WiFi.localIP().toString().c_str()); yield();
   Serial.printf("Gateway....: %s\r\n", WiFi.gatewayIP().toString().c_str()); yield();
   Serial.printf("Subnet mask: %s\r\n", WiFi.subnetMask().toString().c_str()); yield();
   Serial.printf("mDNS name..: %s.local\r\n", settings.mdnsName); yield();
   Serial.printf("Server port: %u\r\n", settings.listenPort); yield();
   Serial.printf("Bytes in...: %lu\r\n", bytesIn); yield();
   Serial.printf("Bytes out..: %lu\r\n", bytesOut); yield();
   Serial.printf("Heap free..: %lu\r\n", ESP.getFreeHeap()); yield();
   Serial.printf("Sketch size: %lu\r\n", ESP.getSketchSize()); yield();
   Serial.printf("Sketch free: %lu\r\n", ESP.getFreeSketchSpace() % (1024L * 1024L)); yield();
   Serial.print(F("Call status: "));
   if( tcpClient.connected() ) {
      Serial.printf("CONNECTED TO %s\r\n", tcpClient.remoteIP().toString().c_str());
      Serial.printf("Call length: %s\r\n", connectTimeString());
   } else {
      Serial.println(F("NOT CONNECTED"));
   }
   yield();
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

