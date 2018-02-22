void addGame(String title, int numPlayers, int numCards, int numValues, String values[30], void (*gameFunctions[6])()) {
  Serial.println("ADDING GAME");
  Game g1;
  int i;
  for (i = 0; i < numValues; ++i) {
      const String val = values[i];
      g1.values[i] = val;
  }
  g1.title = title;
  g1.numPlayers = numPlayers;
  g1.numCards = numCards;
  for (i = 0; i < 6; i++) {
    g1.gameFunctions[i] = gameFunctions[i];
  }
  Games[numGames] = g1;
  numGames ++;
  Serial.println("Game Added!"); 
}

void addGames() {
  for (int i=0; i < totalGames; i++) {
    int numParams = allGames[i][0].toInt();
    int numValues = allGames[i][1].toInt();
    int numPlayers = 2;
    int numCards = allGames[i][2].toInt();
    String title;
    void (* funcPointers [6])() = {};
    String values[numValues];
    for (int j=3; j <= numParams; j++) {
      if (j == 3) {
         title = allGames[i][j];
      }
      if (j == 4) {
         numPlayers = allGames[i][j].toInt();
      }
      if ((j > 4) && (j < 11)) {
         funcPointers[j - 5] = buttonFunctions[allGames[i][j].toInt()];
      }
      if (j >= 11) {
         values[j-11] = allGames[i][j];
      }
    }
    addGame(title, numPlayers, numCards, numValues, values, funcPointers);
  }
}

