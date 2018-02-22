////////////////////////////////////////
//////////   GAME FUNCTIONS   //////////
////////////////////////////////////////
void changeValue() {
    playFile("chng_val");  //TODO CHANGE SINGLE CARD VALUE AUDIO
    boolean waiting = true;
    while (waiting) { 
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
      }
        // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
      }

       // Card found
      byte* uidValue = mfrc522.uid.uidByte;
      int cardNum = findCard(uidValue);
      Card c1 = Cards[cardNum];
      c1.valueIndex = (int)random(Games[gameNum].numCards);
      Cards[cardNum] = c1;
      playFile("shuff1");
//      playFile() //TODO CHANGED ONE VALUE
      waiting = false;
    }        
}

void randomizeValues() {
//    playFile("error");  //TODO CHANGE SINGLE CARD VALUE AUDIO
    for (int i=0; i < numCards; i++) {
        Card card = Cards[i];
        card.valueIndex = (int)random(Games[gameNum].numCards);
        Cards[i] = card;
    }
    playFile("shuffled");
//    playFile() //TODO SHUFFLED ALL
    Serial.println("Randomized");
}

void cardMatch(){
  playFile("winmode");
  int numMatch = 3;
  int cardValue = -1;
  uint8_t scanned[numMatch][4] = {};
  int i = 0;
  boolean newCard;

  while (i < numMatch){
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
        }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
        }
      // Card found
      byte* uidValue = mfrc522.uid.uidByte;
      newCard = true;
      // check if that card has been scanned before
      for (int j = 0; j < numMatch; j++) {
        uint8_t* uidPrev = scanned[j];
        if (uidMatch(4, uidPrev, uidValue)) {
          newCard = false;
        }
      }
      if (newCard) {
        playFile("pair");
        scanned[i][0] = uidValue[0];
        scanned[i][1] = uidValue[1];
        scanned[i][2] = uidValue[2];
        scanned[i][3] = uidValue[3];
  
        Card c = Cards[findCard(uidValue)];
        //First card (look for this value)
        if (i == 0) {
          cardValue = c.valueIndex;
        }
        if ((i > 0) && (cardValue != c.valueIndex)) {
          playFile("lose");
          return;
        }
        i++;
      }
  }
  playFile("win");
}

void readCard() {
    // Look for new cards. Return if not found
    playFile("read");
    boolean reading = true;
    while (reading) {
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        input = -1;
        continue;
      }
       // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        input = -1;
        continue;
      }
    
      // Card found
      byte* uidValue = mfrc522.uid.uidByte;
      int cardNum = findCard(uidValue);
      if (cardNum != -1) {
        const String value = Games[gameNum].values[Cards[cardNum].valueIndex];
        playFile(value.c_str());
      } else {
        playFile("error");
        Serial.println("Unkown card");Serial.println("");
      }
      reading = false;
    }
}


void playSound() {
  playFile("beatmatch");
  delay(200);
  playFile("a");
  playFile("b");
  playFile("e");
  playFile("c");
  playFile("d");
}

void matchCards() {
  playFile("matchsound");
  
  int soundLength = 6;
  uint8_t scanned[6][4] = {};
  int valueIndex[soundLength] = {0, 1, 4, 2, 3 };
  int i = 0;
  boolean newCard;
  while (i < soundLength - 1){
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
        }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
        }
      // Card found
      byte* uidValue = mfrc522.uid.uidByte;
      newCard = true;
      // check if that card has been scanned before
      for (int j = 0; j < soundLength - 1; j++) {
        uint8_t* uidPrev = scanned[j];
        if (uidMatch(4, uidPrev, uidValue)) {
          newCard = false;
        }
      }
      if (newCard) {
        Card c = Cards[findCard(uidValue)];
        const String value = Games[gameNum].values[c.valueIndex];
        playFile(value.c_str());
        scanned[i][0] = uidValue[0];
        scanned[i][1] = uidValue[1];
        scanned[i][2] = uidValue[2];
        scanned[i][3] = uidValue[3];
  
        //First card (look for this value)
        if (valueIndex[i] != c.valueIndex) {
          playFile("wrong");
          return;
        }
        i++;
      }
  }
  playFile("ss_w");
}

void doNothing() {
  
}


void (*buttonFunctions [7])() = { changeValue, readCard, randomizeValues, cardMatch, doNothing, playSound, matchCards };

