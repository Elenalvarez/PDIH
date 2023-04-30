const int BUTTON_PIN = 7;      
int lastState = LOW;  
int currentState; 

void setup() {
  
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == HIGH && currentState == LOW){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(1000);
  }
  else if(lastState == LOW && currentState == HIGH){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    delay(1000);
  }
  
  lastState = currentState;
}
