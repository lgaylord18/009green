
////////////////////////////////////////
////////   LISTENER FUNCTIONS   ////////


void B0Listener() {
  if (!digitalRead(BUTTON_0)) {
    int B0Down = millis();
    input = B0L;
    while ((millis()-B0Down) <= LONG_PRESS) {
      if(digitalRead(BUTTON_0)) {
        input = B0S;
        break;
      }
    }
  }
}

void B1Listener() {
  if (!digitalRead(BUTTON_1)) {
    int B1Down = millis();
    input = B1L;
    while ((millis() - B1Down) <= LONG_PRESS) {
      if(digitalRead(BUTTON_1)) {
        input = B1S;
        break;
      }
    }
  }
}

void B2Listener() {
  if(!digitalRead(BUTTON_2)){
    int B2Down = millis();
    input = B2L;
    delay(200);
    while ((millis()-B2Down) <= LONG_PRESS) {
      if (digitalRead(BUTTON_2)) {
        input = B2S;
        break;
      }
    }
  }
}

void listenAllButtons() {
    B0Listener();
    B1Listener();
    B2Listener();
}
