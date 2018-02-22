#include <SPI.h>
#include <MFRC522.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include "pinout.h"
// INPUTS
int input = -1;
const int LONG_PRESS = 1400;
const int B0S = 0;
const int B1S = 1;
const int B2S = 2;
const int B0L = 3;
const int B1L = 4;
const int B2L = 5;
#include "buttonListeners.h"

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

  while (playWav1.isPlaying()) {
  }
}


////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  delay(10);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(10);
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
       
  
  // BUTTON SETUP
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  
  Serial.println("Connected");
  playFile("rise");
}

/////////////////////////////////////////////

void loop() {
    while (true) {
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
      }
      break;
    }
    uint8_t uidValue1[4] = {
      mfrc522.uid.uidByte[0],
      mfrc522.uid.uidByte[1],
      mfrc522.uid.uidByte[2],
      mfrc522.uid.uidByte[3],
    };
    playFile("piano");
    
    while (true) {
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
      }
      byte* uidValue2 = mfrc522.uid.uidByte;
      if ((uidValue1[0] == uidValue2[0]) && (uidValue1[1] == uidValue2[1]) && (uidValue1[2] == uidValue2[2]) && (uidValue1[3] == uidValue2[3])) {
        continue;
      }
      break;
    }
    playFile("reverse");
    
    while (!digitalRead(BUTTON_0) || !digitalRead(BUTTON_1) || !digitalRead(BUTTON_2)) {
    }

    input = -1;
    while (input == -1) {
      listenAllButtons();
    }
    playFile("chng_val");
 
    while (true) {
      // Look for new cards. Return if not found
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        continue;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        continue;
      }
      break;
    }
    playFile("demowin");

        
    while (!digitalRead(BUTTON_0) || !digitalRead(BUTTON_1) || !digitalRead(BUTTON_2)) {
    }

    input = -1;
    while (input == -1) {
      listenAllButtons();
    }
    playFile("shuffled");
}

