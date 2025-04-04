//dodawanie potrzebnychbibliotek
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <DS3231.h>


LiquidCrystal_PCF8574 lcd(0x27);
DS3231 clock1;

String toStringWithLeadingZeros(byte number) {
  String result = String(number);
  if(number < 10) {
    result = "0" + result;
  }
  return result;
}
//wyświeylenie roku : miesięcy : dni
String getDateString() {
  bool century;
  String day = toStringWithLeadingZeros(clock1.getDate());
  String month = toStringWithLeadingZeros(clock1.getMonth(century));
  String year = String(clock1.getYear() + 2000);
  return day + "." + month + "." + year + "r.";
}
//Wyświetlenie godziny : minut : sekund
String getTimeString() {
  bool h12, pm;
  String hour = toStringWithLeadingZeros(clock1.getHour(h12, pm));
  String minute = toStringWithLeadingZeros(clock1.getMinute());
  String second = toStringWithLeadingZeros(clock1.getSecond());
  return hour + ":" + minute + ":" + second;
}

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(true);
  delay(100);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.print(getDateString());
  lcd.setCursor(0, 1);
  lcd.print(getTimeString());
  delay(1000);
}
