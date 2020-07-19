#ifndef _GLOBALS_H
   #define _GLOBALS_H

   // globals
   const char okStr[] PROGMEM = {"OK"};
   const char connectStr[] PROGMEM = {"CONNECT"};
   const char ringStr[] PROGMEM = {"RING"};
   const char noCarrierStr[] PROGMEM = {"NO CARRIER"};
   const char errorStr[] PROGMEM = {"ERROR"};
   const char noAnswerStr[] PROGMEM = {"NO ANSWER"};
   enum ResultCodes { R_OK, R_CONNECT, R_RING, R_NO_CARRIER, R_ERROR, R_NO_ANSWER, R_RING_IP };
   const char * const resultCodes[] PROGMEM = { okStr, connectStr, ringStr, noCarrierStr, errorStr, noAnswerStr, ringStr};

   WiFiClient tcpClient;
   uint32_t bytesIn = 0, bytesOut = 0;
   unsigned long connectTime = 0;

   WiFiServer tcpServer(0);

   struct Settings {
      uint16_t  magicNumber;
      char      ssid[MAX_SSID_LEN + 1];
      char      wifiPassword[MAX_WIFI_PWD_LEN + 1];
      uint32_t  serialSpeed;
      uint8_t   dataBits;
      char      parity;
      uint8_t   stopBits;
      bool      rtsCts;
      uint8_t   width, height;
      char      escChar;
      char      alias[SPEED_DIAL_SLOTS][MAX_ALIAS_LEN + 1];
      char      speedDial[SPEED_DIAL_SLOTS][MAX_SPEED_DIAL_LEN + 1];
      char      mdnsName[MAX_MDNSNAME_LEN + 1];
      uint8_t   autoAnswer;
      uint16_t  listenPort;
      char      busyMsg[MAX_BUSYMSG_LEN + 1];
      char      serverPassword[MAX_PWD_LEN + 1];
      bool      echo;
      uint8_t   telnet;
      char      autoExecute[MAX_AUTOEXEC_LEN + 1];
      char      terminal[MAX_TERMINAL_LEN + 1];
      char      location[MAX_LOCATION_LEN + 1];
      bool      startupWait;
      bool      extendedCodes;
      bool      verbose;
      bool      quiet;
   } settings;

   char atCmd[MAX_CMD_LEN + 1], lastCmd[MAX_CMD_LEN + 1];
   unsigned atCmdLen = 0;

   enum {CMD_NOT_IN_CALL, CMD_IN_CALL, ONLINE, PASSWORD} state = CMD_NOT_IN_CALL;

   bool     ringing = false;     // no incoming call
   uint8_t  ringCount = 0;       // current incoming call ring count
   uint32_t nextRingMs = 0;      // time of mext RING result
   uint8_t  escCount = 0;        // Go to AT mode at "+++" sequence, that has to be counted
   uint32_t guardTime = 0;       // When did we last receive a "+++" sequence
   char     password[MAX_PWD_LEN + 1];
   uint8_t  passwordTries = 0;   // # of unsuccessful tries at incoming password
   uint8_t  passwordLen = 0;
   uint8_t  txBuf[TX_BUF_SIZE];  // Transmit Buffer
   uint8_t  sessionTelnetType;
#endif
