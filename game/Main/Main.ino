#include <SPI.h>
#include <MFRC522.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include "pinout.h"
#include "Game.h"
#include "global.h"
#include "allGames.h"
#include "buttonListeners.h"
#include "helperFunctions.h"
#include "gameFunctions.h"
#include "addGame.h"




////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  delay(10);
  AudioMemory(8);
  addGames();
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
  playFile("welcome");
  playFile("scroll");
}

/////////////////////////////////////////////

void loop() {
  input = -1;
  while (!digitalRead(BUTTON_0) || !digitalRead(BUTTON_1) || !digitalRead(BUTTON_2)) {
  
  }
  while (input == -1) {
    listenAllButtons();
  }
  
  Serial.print("RECEIVED INPUT: ");
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
         case B2L:    // Right Arrow
            gameNum = 1;
            playFile("add");
            demoMode();
            break;
         default:
            break;
      }
  }
  else if (entering) {
    Serial.println("ENTERING");
    addPlayers();
    if (gameNum == 2) {
      addCardsinOrder(Games[gameNum].numCards);
    } else {
      addCards(Games[gameNum].numCards);
    }
    entering = false;
    return;
  }
  else if (!entering and !selecting) {    //IN GAME
      switch(input) {
         case B0S:    // Left Arrow
            Games[gameNum].gameFunctions[B0S]();
            break;
         case B0L:   
            Games[gameNum].gameFunctions[B1L]();
            break;
         case B1S:    // Center Button
            Games[gameNum].gameFunctions[B1S]();
            break;
         case B1L:    
            Games[gameNum].gameFunctions[B1L]();
            break;
         case B2S:    // Right Arrow
            Games[gameNum].gameFunctions[B2S]();
            break;
         case B2L:
            Games[gameNum].gameFunctions[B2L]();
            break;
         default:
            break;
      }
  } 
  delay(500);
}

