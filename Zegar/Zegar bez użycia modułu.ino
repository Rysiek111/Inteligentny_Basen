#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);

// Definicje polskich znaków
byte pla[8] = {0b00000, 0b00000, 0b01110, 0b00001, 0b01111, 0b10001, 0b01111, 0b00100};
byte plc[8] = {0b00010, 0b00100, 0b01110, 0b10000, 0b10000, 0b10001, 0b01110, 0b00000};
byte ple[8] = {0b00000, 0b00000, 0b01110, 0b10001, 0b11111, 0b10000, 0b01110, 0b00100};
byte pll[8] = {0b01100, 0b00100, 0b00110, 0b00100, 0b01100, 0b00100, 0b01110, 0b00000};
byte pln[8] = {0b00010, 0b00100, 0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b00000};
byte plo[8] = {0b00010, 0b00100, 0b01110, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000};
byte pls[8] = {0b00010, 0b00100, 0b01110, 0b10000, 0b01110, 0b00001, 0b11110, 0b00000};
byte plz[8] = {0b00100, 0b00000, 0b11111, 0b00010, 0b00100, 0b01000, 0b11111, 0b00000};

int lata = 2022;
int miesiace = 4;
int dni = 2;
int godziny = 19;
int minuty = 50;
int sekundy = 0;

const int dni_w_miesiacu[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, pla);
    lcd.createChar(1, plc);
    lcd.createChar(2, ple);
    lcd.createChar(3, pll);
    lcd.createChar(4, pln);
    lcd.createChar(5, plo);
    lcd.createChar(6, pls);
    lcd.createChar(7, plz);
    lcd.clear();
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print(dni);
    lcd.setCursor(2, 0);
    lcd.print("-");
    lcd.setCursor(3, 0);
    lcd.print(miesiace);
    lcd.setCursor(5, 0);
    lcd.print("-");
    lcd.setCursor(6, 0);
    lcd.print(lata);
    
    lcd.setCursor(0, 1);
    lcd.print(godziny);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(minuty);
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(sekundy);
    
    delay(1000);
    sekundy++;
    
    if (sekundy == 60) {
        sekundy = 0;
        minuty++;
    }
    if (minuty == 60) {
        minuty = 0;
        godziny++;
    }
    if (godziny == 24) {
        godziny = 0;
        dni++;
    }
    
    int max_dni = dni_w_miesiacu[miesiace - 1];
    if (miesiace == 2 && ((lata % 400 == 0) || ((lata % 4 == 0) && (lata % 100 != 0)))) {
        max_dni = 29;
    }
    
    if (dni > max_dni) {
        dni = 1;
        miesiace++;
    }
    
    if (miesiace > 12) {
        miesiace = 1;
        lata++;
    }
}
