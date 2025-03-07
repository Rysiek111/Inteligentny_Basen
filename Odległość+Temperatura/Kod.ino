// Dodawanie potrzebnych bibliotek
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Informowanie Arduino UNO, jaki ekran jest podpięty
LiquidCrystal_I2C lcd(0x27, 2, 16);

// Informowanie Arduino UNO, gdzie jest podpięty termometr
OneWire oneWire(7);
DallasTemperature sensorsOneWire(&oneWire);

// Polskie znaki i znak stopnia
byte char0[8] = {
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// Mierzenie odległości przez czujnik ultradźwiękowy
double ultraSonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long microseconds = pulseIn(echoPin, HIGH);
  return (double)(microseconds / 58);
}

// Mierzenie temperatury
int getDS18B20Value() {
  sensorsOneWire.requestTemperatures();
  return sensorsOneWire.getTempCByIndex(0);
}

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, char0);
  lcd.clear();
  sensorsOneWire.begin();
}

void loop() {
  int temp = getDS18B20Value();
  double distance = ultraSonicDistance(5, 4);

  // Wyświetlanie wartości na ekranie LCD
  lcd.setCursor(0, 0);
  lcd.print("Odleglosc: " + String(distance) + " cm");
  lcd.setCursor(0, 1);
  
  if (temp == -127) {
    lcd.print("Blad temp!");
  } else {
    lcd.print("Temperatura: " + String(temp) + "");
    lcd.write((byte)0);
    lcd.print("C");
  }
  
  // Sterowanie na podstawie temperatury
  if (temp >= 20) {
    digitalWrite(3, LOW);
  } else if (temp <= 10) {
    digitalWrite(3, HIGH);
  }
  
  delay(1000);
}
