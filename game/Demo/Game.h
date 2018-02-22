
// CARD CLASS
class Card {
  public:
   int valueIndex;
   uint8_t UID[4];
};


class Game {
  public:
    String values[10];    //lots of wav files
    String instructions;  //wav file
    String title;         //wav file with title of game
    Card Cards[100];
    int numCards;
    int numPlayers;
    int gameNum;
    void (*gameFunctions[6])();
};



