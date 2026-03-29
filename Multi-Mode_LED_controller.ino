const int buttonPin = 2;
const int ledPin = 13;
const int ledPin2 = 12;
unsigned long lastTime = 0;
bool ledState1 = false;
bool ledState2 = false;
int lastButtonState = HIGH;
int realButtonState = HIGH;
int systemMode = 0;
int prevMode = -1;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void resetLED(){
  ledState1 = false;
  ledState2 = false;
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  int currentbuttonStatus = digitalRead(buttonPin);

  if (currentbuttonStatus != lastButtonState){
    lastDebounceTime = currentTime;
    lastButtonState = currentbuttonStatus;
  }

  if (currentTime - lastDebounceTime > debounceDelay){
    if (currentbuttonStatus != realButtonState){
      realButtonState = currentbuttonStatus;
      
      if (realButtonState == LOW){
          systemMode = (systemMode + 1) % 4;
    }
  }
  }
  if (systemMode != prevMode){
    prevMode = systemMode;
    resetLED();
  }
  if (systemMode == 0){
  }
  else if (systemMode == 1){
    if (currentTime - lastTime >= 1000){
      lastTime = currentTime;
      ledState1 = !ledState1;
      digitalWrite(ledPin, ledState1);

    }
  }
  else if (systemMode == 2){
    if (currentTime - lastTime >= 300){
      lastTime = currentTime;
      ledState2 = !ledState2;
      digitalWrite(ledPin2, ledState2);
    }
  }
  else if (systemMode == 3){
    if (currentTime - lastTime >= 500){
      lastTime = currentTime;
      ledState1 = !ledState1;
      digitalWrite(ledPin, ledState1);
      digitalWrite(ledPin2, !ledState1);
    }
  }
}
