//
// AT$AE? query auto execute command string
// AT$AE=auto execute command string
//
char *doAutoExecute(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.autoExecute);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.autoExecute, atCmd, MAX_AUTOEXEC_LEN);
         settings.busyMsg[MAX_AUTOEXEC_LEN] = NUL;
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
// AT$BM?  query busy message
// AT$BM=busy message set busy message
//
char *doBusyMessage(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.busyMsg);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.busyMsg, atCmd, MAX_BUSYMSG_LEN);
         settings.busyMsg[MAX_BUSYMSG_LEN] = NUL;
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
// AT$MDNS? query mDNS network name
// AT$MDNS=mdnsname set mDNS network name
//
char *doMdnsName(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.mdnsName);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;

      case '=':
         ++atCmd;
         strncpy(settings.mdnsName , atCmd, MAX_MDNSNAME_LEN);
         settings.mdnsName[MAX_MDNSNAME_LEN] = NUL;
         atCmd[0] = NUL;
         sendResult(R_OK);
         break;

      default:
         sendResult(R_ERROR);
         lastCmd[0] = NUL;
         break;
   }
   return atCmd;
}

//
// AT$PASS? query WiFi password
// AT$PASS=password set WiFi password
//
char *doWiFiPassword(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.wifiPassword);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.wifiPassword, atCmd, MAX_WIFI_PWD_LEN);
         settings.wifiPassword[MAX_WIFI_PWD_LEN] = NUL;
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
// AT$SB?  query serial speed
// AT$SB=n set serial speed
//
char *doSpeedChange(char *atCmd) {
   long newSerialSpeed;

   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.serialSpeed);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         newSerialSpeed = atol(atCmd);
         while( isdigit(*atCmd) ) {
            ++atCmd;
         }
         if( newSerialSpeed != settings.serialSpeed ) {
            switch( newSerialSpeed ) {
               case 110L:                       // 110 thru 76.8K are the
               case 300L:                       // standard 'BYE' rates, if
               case 450L:                       // you're wondering why
               case 600L:                       // unusual rates like 110, 450
               case 710L:                       // and 710 are in this list
               case 1200L:
               case 2400L:
               case 4800L:
               case 9600L:
               case 19200L:
               case 38400L:
               case 57600L:
               case 76800L:
               case 115200L:
                  sendResult(R_OK);
                  Serial.flush();               // wait for transmit to finish
                  digitalWrite(TXEN, HIGH);     // disable the TX output
                  Serial.updateBaudRate(newSerialSpeed);
                  settings.serialSpeed = newSerialSpeed;
                  digitalWrite(TXEN, LOW);  // reenable the TX output
                  break;

               default:
                  sendResult(R_ERROR);
                  break;
            }
         } else {
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
// AT$SP?  query inbound TCP port #
// AT$SP=n set inbound TCP port #
//         NOTE: n=0 will disable the inbound TCP port
//               and a RING message will never be displayed
//
char *doServerPort(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.listenPort);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         settings.listenPort = atoi(atCmd);
         while( isDigit(atCmd[0]) ) {
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
// AT$SSID? query WiFi SSID
// AT$SSID=ssid set WiFi SSID
//
char *doSSID(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.ssid);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.ssid, atCmd, MAX_SSID_LEN);
         settings.ssid[MAX_SSID_LEN] = NUL;
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
// AT$SU? query data configuration
// AT$SU=nps set data configuration
//       n=7/8   data bits
//       p=N/E/O parity
//       s=1/2   stop bits
//
char *doDataConfig(char *atCmd) {
   bool ok = true;
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.printf("%u%c%u\r\n",
            settings.dataBits,
            settings.parity,
            settings.stopBits);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         switch( atCmd[1] ) {
            case '5':
            case '6':
            case '7':
            case '8':
               break;
            default:
               ok = false;
               break;
         }
         switch( toupper(atCmd[2]) ) {
            case 'N':
            case 'O':
            case 'E':
               break;
            default:
               ok = false;
               break;
         }
         switch( atCmd[3] ) {
            case '1':
            case '2':
               break;
            default:
               ok = false;
               break;
         }
         if( ok ) {
            settings.dataBits = atCmd[1] - '0';
            settings.parity = toupper(atCmd[2]);
            settings.stopBits = atCmd[3] - '0';
            atCmd += 4;    // skip over =dps
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
// AT$TTL? query Telnet location
// AT$TTL=location set Telnet location
//
char *doLocation(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.location);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.location, atCmd, MAX_LOCATION_LEN);
         settings.location[MAX_LOCATION_LEN] = NUL;
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
// AT$TTS? query Telnet window size
// AT$TTS=WxH set Telnet window size (width x height)
//
char *doWindowSize(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.printf("%ux%u\r\n", settings.width, settings.height);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         {
            char *width = atCmd + 1;
            char *height = strpbrk(width, "xX");
            if( !width || !height ) {
               sendResult(R_ERROR);
            } else {
               ++height; // point to 1st char past X
               settings.width = atoi(width);
               settings.height = atoi(height);
               atCmd = height;
               while( isDigit(atCmd[0]) ) {
                  ++atCmd;
               }
               if( !atCmd[0] ) {
                  sendResult(R_OK);
               }
            }
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}

//
// AT$TTY? query Telnet terminal type
// AT$TTY=terminal set Telnet terminal type
//
char *doTerminalType(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.terminal);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         strncpy(settings.terminal, atCmd, MAX_TERMINAL_LEN);
         settings.location[MAX_TERMINAL_LEN] = NUL;
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
// AT$W? query startup wait status
// AT$W=0 disable startup wait
// AT$W=1 enable startup wait (wait for a CR on startup)
//
char *doStartupWait(char *atCmd) {
   switch( atCmd[0] ) {
      case '?':
         ++atCmd;
         Serial.println(settings.startupWait);
         if( !atCmd[0] ) {
            sendResult(R_OK);
         }
         break;
      case '=':
         ++atCmd;
         switch( atCmd[0] ) {
            case '0':
            case '1':
               settings.startupWait = atCmd[0] == '1';
               atCmd[0] = NUL;
               sendResult(R_OK);
               break;
            default:
               sendResult(R_ERROR);
               break;
         }
         break;
      default:
         sendResult(R_ERROR);
         break;
   }
   return atCmd;
}
