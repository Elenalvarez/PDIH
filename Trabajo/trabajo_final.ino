#include <LiquidCrystal.h> //librería para la pantalla LCD
#include "DHT.h" //librería para el sensor de temperatura

//inicialización de la pantalla LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//inicializació del sensor de temperatura
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int humTierra = analogRead(A0);
  int luz = analogRead(A1);
  lcd.clear();
  int humAire = dht.readHumidity();
  int tempC = dht.readTemperature();

  //Humedad de la tierra
  lcd.setCursor(0,0);
  if (humTierra < 300)
    lcd.print("Tie:Seca ");
  else
    lcd.print("Tie:Hum ");
  Serial.print("Humedad tierra:");
  Serial.print(humTierra);

  //Humedad del ambiente
  lcd.print("Hum: ");
  lcd.print(humAire);
  lcd.print("%");
  Serial.print("|| Humedad aire:");
  Serial.print(humAire);
  Serial.print("%");

  //Iluminación
  lcd.setCursor(0,1);
  if(luz<300)
    lcd.print("Oscuro");
  else
    lcd.print("Luminoso");
  Serial.print("|| Iluminacion:");
  Serial.print(luz);

  //Temperatura
  lcd.print(" Temp:");
  lcd.print(tempC);
  Serial.print("|| Temperatura:");
  Serial.print(tempC);
  Serial.println("ºC");

  delay(5000);
}
