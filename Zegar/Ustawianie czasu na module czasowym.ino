/*

Po wgraniu tego kodu należy ustawić czas.
W tym celu należy wysłać ciąg znaków w formie: YYMMDDwHHMMSSx, czyli
YY - dwie cyfry roku,
MM - dwie cyfry miesięcy,
DD - dwie cyfry dni,
w - jedna cyfra dnia tygodnia,
HH - dwie cyfry godziny,
MM - dwie cyfry minut,
SS - dwie cyfry sekund
x - jako zakończenie ciągu znaków,
należy wysłać to przez monitor portu szeregowego.

*/
//dodawanie potrzebnychbibliotek
#include <DS3231.h>
#include <Wire.h>

DS3231 clock1;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second) {

    boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    char inString[20];
    
    byte j=0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.println(inString);

    temp1 = (byte)inString[0] -48;
    temp2 = (byte)inString[1] -48;
    year = temp1*10 + temp2;

    temp1 = (byte)inString[2] -48;
    temp2 = (byte)inString[3] -48;
    month = temp1*10 + temp2;

    temp1 = (byte)inString[4] -48;
    temp2 = (byte)inString[5] -48;
    date = temp1*10 + temp2;

    dOW = (byte)inString[6] - 48;

    temp1 = (byte)inString[7] -48;
    temp2 = (byte)inString[8] -48;
    hour = temp1*10 + temp2;

    temp1 = (byte)inString[9] -48;
    temp2 = (byte)inString[10] -48;
    minute = temp1*10 + temp2;

    temp1 = (byte)inString[11] -48;
    temp2 = (byte)inString[12] -48;
    second = temp1*10 + temp2;
}

void setup() {

    Serial.begin(57600);
    

    Wire.begin();
}

void loop() {
    

    if (Serial.available()) {
        getDateStuff(year, month, date, dOW, hour, minute, second);
        
        clock1.setClockMode(false);
        
        clock1.setYear(year);
        clock1.setMonth(month);
        clock1.setDate(date);
        clock1.setDoW(dOW);
        clock1.setHour(hour);
        clock1.setMinute(minute);
        clock1.setSecond(second);
        

        clock1.setA1Time(dOW, hour, minute+1, second, 0x0, true,
                        false, false);

        clock1.setA2Time(date, hour, minute+2, 0x0, false, false,
                        false);

        clock1.turnOnAlarm(1);
        clock1.turnOnAlarm(2);
        
    }
    delay(1000);
}
