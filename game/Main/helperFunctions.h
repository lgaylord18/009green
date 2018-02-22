////////////////////////////////////////
/////////   HELPER FUNCTIONS   /////////
////////////////////////////////////////

void playFile(const char *filename, const char *suffix= '\0') {
  Serial.print("Playing file: ");
  Serial.println(filename);
  char fileToPlay[80];
  strcpy (fileToPlay, filename);
  strcat(fileToPlay, suffix);
  strcat(fileToPlay, ".wav");
  Serial.println(fileToPlay);
  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(fileToPlay);
  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (!digitalRead(BUTTON_0) || !digitalRead(BUTTON_1) || !digitalRead(BUTTON_2)) {
    
  }
  while (playWav1.isPlaying()) {
    input = -1;
    listenAllButtons();
    switch(input) {
      case B0S:    // Left Arrow
        input = -1;
        playWav1.stop();
        playFile(filename, suffix);
        break;
      case B1S:    // Center Button
        input = -1;
        playWav1.stop();
        break;
      case B2S:    // Right Arrow
        playWav1.stop();
        break;
      default:
        break;
    }
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    //sgtl5000_1.volume(vol);
  }
}

boolean uidMatch(int uidLength, uint8_t uid1[], uint8_t uid2[]) {
  for (int j=0; j < uidLength; j++) {
    if (uid1[j] != uid2[j]) {
      return false;
    }
  }
  return true;
}

// Gets the value from the list of UID
int findCard(uint8_t uidValue[]) {
    for (int i=0; i < numCards; i++) {
        if (uidMatch(uidLength, uidValue, Cards[i].UID)) {
          return i;
      }
    }
    return -1;
}

void addCard(uint8_t* uidValue) {
  Card c1;
  c1.valueIndex = (int)random(Games[gameNum].numCards);
  c1.UID[0] = uidValue[0];
  c1.UID[1] = uidValue[1];
  c1.UID[2] = uidValue[2];
  c1.UID[3] = uidValue[3];
  Cards[numCards] = c1;
  numCards ++;
  Serial.println("Card Added!: ");
  Serial.print(c1.UID[0]);Serial.print(c1.UID[1]);Serial.print(c1.UID[2]);Serial.println(c1.UID[3]);
  Serial.print("Total Cards: ");Serial.println(numCards);Serial.println("");
  playFile("pair");
}


void addCardWithValue(uint8_t* uidValue, int valueIndex) {
  Card c1;
  c1.valueIndex = valueIndex;
  c1.UID[0] = uidValue[0];
  c1.UID[1] = uidValue[1];
  c1.UID[2] = uidValue[2];
  c1.UID[3] = uidValue[3];
  Cards[numCards] = c1;
  numCards ++;
  Serial.println("Card Added!: ");
  Serial.print(c1.UID[0]);Serial.print(c1.UID[1]);Serial.print(c1.UID[2]);Serial.println(c1.UID[3]);
  Serial.print("Total Cards: ");Serial.println(numCards);Serial.println("");
  const String value = Games[gameNum].values[valueIndex];
  playFile(value.c_str());
}

void addCards(int totalCards) {
    playFile("error");
    //  playFile("deal");
    Serial.println("pairing Cards");
    while (numCards < Games[gameNum].numCards ){
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
      int cardNum = findCard(uidValue);
      if (cardNum == -1) {
          addCard(uidValue);
      } else {
          Serial.println("Card already exists");Serial.println("");
      }
    }
    playFile(Games[gameNum].title.c_str(), "_e");
}

void addCardsinOrder(int totalCards) {
    playFile("error");
    //  playFile("deal");
    Serial.println("pairing Cards");
    while (numCards < Games[gameNum].numCards ){
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
      int cardNum = findCard(uidValue);
      if (cardNum == -1) {
        Serial.println(numCards);
          addCardWithValue(uidValue, numCards);
      } else {
          Serial.println("Card already exists");Serial.println("");
      }
    }
    playFile(Games[gameNum].title.c_str(), "_e");
}


void nextGame() {
  gameNum ++;
  if (gameNum > numGames - 1) {
    gameNum = 0;
  }
  playFile("next");
  playFile(Games[gameNum].title.c_str());  
}

void previousGame() {
  gameNum --;
  if (gameNum < 0) {
    gameNum = numGames - 1;
  }
//  const char *cstr = Games[gameNum].title.c_str();
  playFile("previous");
  playFile(Games[gameNum].title.c_str());
}


void selectGame() {
  Serial.println(Games[gameNum].values[0]);
  Serial.println("SELECTED");
  Serial.println(Games[gameNum].title);
  playFile("select");
  playFile(Games[gameNum].title.c_str(), "_s"); 
  delay(200);
  selecting = false;
  entering = true;
}

void addPlayers() {
  playFile("players");

  Serial.println("Add players");
  boolean adding = true;
  char num[10];
  input = -1;
  while (adding) {
    B0Listener();
    B1Listener();
    B2Listener();
    if (input == -1) {
      continue;
    }
    switch (input) {
     case B0S:    // Left Arrow
        numPlayers--;
        if (numPlayers < 1) { numPlayers = 1; }
        playFile("sub");
        itoa(numPlayers, num, 10);
        playFile(num);
        break;
     case B1S:    // Center Button
        adding = false;
        break;
     case B2S:    // Right Arrow
        numPlayers++;
        playFile("add");
        itoa(numPlayers, num, 10);
        playFile(num);
        break;
    }
    input = -1;
  }
}

void demoMode() {
    while (numCards < 3 ){
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
      int cardNum = findCard(uidValue);
      if (cardNum == -1) {
          Serial.println(numCards);
          addCardWithValue(uidValue, numCards);
      } else {
          Serial.println("Card already exists");Serial.println("");
      }
    }
    input = -1;
    boolean demoing = true;
    boolean cardFound = false;
    while (demoing) {
      cardFound = true;
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        cardFound = false;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        cardFound = false;
      }
      if (cardFound) {
        byte* uidValue = mfrc522.uid.uidByte;
        int cardNum = findCard(uidValue);
        if (cardNum != -1) {
          const String value = Games[gameNum].values[Cards[cardNum].valueIndex];
          playFile(value.c_str());
        } else {
          playFile("error");
          Serial.println("Unkown card");Serial.println("");
        }
      }
      
      B0Listener();
      B1Listener();
      B2Listener();
      if (input != -1) {
        switch (input) {
         case B0S:    // Left Arrow
            break;
         case B1S:    // Center Button
            for (int i=0; i < numCards; i++) {
                Card card = Cards[i];
                card.valueIndex = (int)random(Games[gameNum].numCards);
                Cards[i] = card;
            }
            playFile("shuffled");
            Serial.println("Randomized");
            break;
         case B2S:    // Right Arrow
            break;
        }
        input = -1;
      }
    }
    
}

