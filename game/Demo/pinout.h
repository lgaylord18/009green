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
#define SDCARD_MOSI_PIN          11
// MISO DEFAULT 12
#define SDCARD_SCK_PIN           13

//OTHER PINS
#define BUTTON_0     1
#define BUTTON_1     2
#define BUTTON_2     3

MFRC522 mfrc522(SS_PIN_RFID, RST_PIN);      // Create MFRC522 instance

