int analogValue;

void setup() {
  pinMode(3, OUTPUT); 
}

void loop() {
  analogValue = analogRead(A0); 

  if(analogValue < 500)
    digitalWrite(3, HIGH); 
  else
    digitalWrite(3, LOW);  
}
