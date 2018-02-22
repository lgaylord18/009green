#include <SPI.h>
#include <MFRC522.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playWav1;
AudioOutputAnalog        audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;

//RFID READER
#define SS_PIN_RFID 10
#define RST_PIN     8 //FLOATING
//SD CARD PINS
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define MOSI_PIN          11
// MISO DEFAULT 12
#define SCK_PIN           13

//OTHER PINS
#define BUTTON_0     1
#define BUTTON_1     2
#define BUTTON_2     3

MFRC522 mfrc522(SS_PIN_RFID, RST_PIN);      // Create MFRC522 instance

////////////////////////////////////////
/////////   GLOBAL VARIABLES   /////////
////////////////////////////////////////
int numCards = 0;                 // Set number of RFID tags you want
int numValues = 12;
int input = -1;
int lastInput = 0;
int numGames = 0;
int gameNum = 0;
boolean selecting = true;

// INPUTS
const int LONG_PRESS = 2000;
const int B0S = 0;
const int B1S = 1;
const int B2S = 2;
const int B0L = 3;
const int B1L = 4;
const int B2L = 5;

const int FlashChipSelect = 6;

// CARD CLASS
class Card {
  public:
   int valueIndex;
   uint8_t UID[4];
};

class Game {
  public:
    String values[30];    //lots of wav files
    String instructions;  //wav file
    String title;         //wav file with title of game
    void button0S();
    void button1S();
    void button2S();
    void button0L();
    void button1L();
    void button2L();
};

Card Cards[100];
Game Games[100];
Game CurrentGame;

void addGame(String v[30], String inst) {
  Game g1;
  memcpy(g1.values, v, sizeof(v)); //Copy values into the game
  g1.instructions = inst;          //Set instructions
  Games[numGames] = g1;
  numGames ++;
  Serial.println("Game Added!");
}

////////////////////////////////////////
/////////   HELPER FUNCTIONS   /////////
////////////////////////////////////////

// Gets the value from the list of UID
int findCard(int uidLength, uint8_t uidValue[]) {
    for (int i=0; i < numCards; i++) {

        if (uidMatch(uidLength, uidValue, Cards[i].UID)) {
          return i;
      }
    }
    return -1;
}

boolean uidMatch(int uidLength, uint8_t uid1[], uint8_t uid2[]) {
  for (int j=0; j < uidLength; j++) {
    if (uid1[j] != uid2[j]) {
      return false;
    }
  }
  return true;
}

void addCard(uint8_t* uidValue) {
  Card c1;
  c1.valueIndex = (int)random(numValues);
  c1.UID[0] = uidValue[0];
  c1.UID[1] = uidValue[1];
  c1.UID[2] = uidValue[2];
  c1.UID[3] = uidValue[3];
  Cards[numCards] = c1;
  numCards ++;
  Serial.println("Card Added!: ");
  Serial.print(c1.UID[0]);Serial.print(c1.UID[1]);Serial.print(c1.UID[2]);Serial.println(c1.UID[3]);
  Serial.print("Total Cards: ");Serial.println(numCards);Serial.println("");

}

void randomizeValues() {
    for (int i=0; i < numCards; i++) {
        Card card = Cards[i];
        card.valueIndex = (int)random(numValues);
        Cards[i] = card;
    }
    Serial.println("Randomized");
}

void nextGame() {
  gameNum ++;
  if (gameNum > numGames) {
    gameNum = 0;
  }
  const char *cstr = Games[gameNum].title.c_str();
  playFile(cstr);
}

void previousGame() {
  gameNum --;
  if (gameNum < 0) {
    gameNum = numGames;
  }
  const char *cstr = Games[gameNum].title.c_str();
  playFile("test1.wav");
}


void selectGame() {
  CurrentGame = Games[gameNum];
  const char *cstr = CurrentGame.instructions.c_str();
  playFile(cstr);
}

void playFile(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
//    Serial.println("playing");
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
//     sgtl5000_1.volume(vol);
  }
}

////////////////////////////////////////

// GAME 1! //
String game1Values[3] = {
  "1.wav",
  "2.wav",
  "3.wav",
};
String game1instructions = "read.wav";

void setup() {
  addGame(game1Values, game1instructions);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  SPI.setMOSI(MOSI_PIN);
  SPI.setSCK(SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  randomSeed(analogRead(0));      // Randomize seed
  SPI.begin();                    // Init SPI bus
  mfrc522.PCD_Init();             // Init MFRC522
       
  
  // BUTTONS
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  Serial.println("Connected");

  // AUDIO AMP SETUP
//  pinMode(5, OUTPUT);
//  digitalWrite(5, HIGH); // turn on the amplifier
//  delay(10);             // allow time to wake up
  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors

  playFile("welcome.wav");     //Welcome to _____
}

void loop() {
//  Serial.println("waiting for a card"); 
//    // Look for new cards. Return if not found
//    if ( ! mfrc522.PICC_IsNewCardPresent()) {
//      return;
//    }
//    // Select one of the cards
//    if ( ! mfrc522.PICC_ReadCardSerial()) {
//      return;
//    }
//  
//    // Card found
//    byte* uidValue = mfrc522.uid.uidByte;
//    uint8_t uidLength = 4;
//    Serial.println(uidValue[0]);
    
  if(!digitalRead(BUTTON_0)){
    int B0Down = millis();
    input = B0L;
    while ((millis()-B0Down) <= LONG_PRESS) {
      if(digitalRead(BUTTON_0)) {
        input = B0S;
        break;
      }
    }
  }
  if(!digitalRead(BUTTON_1)){
    int B1Down = millis();
    input = B1L;
    while ((millis()-B1Down) <= LONG_PRESS) {
      if (digitalRead(BUTTON_1)) {
        input = B1S;
        break;
      }
    }
  }
  if(!digitalRead(BUTTON_2)){
    int B2Down = millis();
    input = B2L;
    while ((millis()-B2Down) <= LONG_PRESS) {
      if (digitalRead(BUTTON_2)) {
        input = B2S;
        break;
      }
    }
  }
  if (input == -1) {
    return;
  }
  Serial.println(input);
  
  // Selecting a game
  if (selecting) {
      switch(input) {
         case B0S:    // Left Arrow
            previousGame();
            break;
         case B1S:    // Center Button
            selectGame();
            break;
         case B2S:    // Right Arrow
            nextGame();
            break;
         default:
            break;
      }

  // In a game
  } else {
    //Check if game mode has changed
    if (input != lastInput) {
        switch(input) {
           case B0S:
//              playFile(CurrentGame.b0audio);
              break;
           case B1S:
              break;
           case B2S:
              break;
           default:
              break;
        } 
    } else {
        switch(input) {
           case B0S:
//              CurrentGame.button0s();
              break;
           case B1S:
//              CurrentGame.button1s();
              break;
           case B2S:
//              CurrentGame.button2s();
              break;
           default:
              break;
        }
    }
    
    
//    if (gameMode == 2) {
//      randomizeValues();
//      if (gameMode == 2) {  // Only changed if interrupt during randomize
//          gameMode = 1;     // Go back to read mode after a shuffle
//      }
//      return;
//    }
//    

//  
//    if (gameMode == 0) {
//      if (cardNum == -1) {
//        addCard(uidValue);
//      }
//      else {
//        Serial.println("Card already exists");Serial.println("");
//        playFile(words[0]);
//      }
//    }
//  
//    if (gameMode == 1) {
//      if (cardNum != -1) {
//        Serial.println("Found card: "); Serial.print(uidValue[0]);Serial.print(uidValue[1]);Serial.print(uidValue[2]);Serial.println(uidValue[3]);Serial.println("");
//        playFile(values[Cards[cardNum].valueIndex]);
//      } else {
//        Serial.println("Unkown card");Serial.println("");
//        playFile(words[0]);
//      }
//    }
//  
//    Serial.println("Card Scanned: "); Serial.print(uidValue[0]);Serial.print(uidValue[1]);Serial.print(uidValue[2]);Serial.println(uidValue[3]);Serial.println("");
//  
//  
//    
//    ledOff();    // SHOW GOT A CARD
//    delay(300);  // SHOW GOT A CARD
//    ledOn();     // SHOW GOT A CARD
  }
  input = -1;
}


