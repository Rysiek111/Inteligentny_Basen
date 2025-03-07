#include <ESP8266WiFi.h>     // Biblioteka do obsługi Wi-Fi dla ESP8266
#include <ESP8266WebServer.h> // Biblioteka do obsługi serwera HTTP na ESP8266
#include <Adafruit_NeoPixel.h> // Biblioteka do obsługi diod LED NeoPixel

#define LED_PIN     D5         // Pin, do którego podłączone są diody LED
#define NUM_LEDS    34         // Liczba diod LED
const int przekazniki[] = {D0, D1, D2, D3};  // Piny, do których podłączone są przekaźniki

bool ledstate = false;  // Zmienna przechowująca stan diody LED (ON/OFF)
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  // Inicjalizacja obiektu NeoPixel

const char* ssid = "Basen";       // Nazwa sieci Wi-Fi
const char* password = "1234567890"; // Hasło do sieci Wi-Fi
ESP8266WebServer server(80);      // Tworzenie serwera na porcie 80

// Funkcja ustawia kolor dla określonego piksela (LED) w tablicy
void setColor(int led, int red, int green, int blue) {
    pixels.setPixelColor(led, pixels.Color(red, green, blue));  // Ustawia kolor piksela
    pixels.show();  // Aktualizuje wszystkie diody
}

// Funkcja generująca nagłówek strony HTML
String HTMLHeader() {
    return "<!DOCTYPE html><html><head><title>Basen</title>"
           "<meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'>"
           "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'></head>"
           "<body style='text-align: center; color: white; background: black; font-size: 1.5em;'>"; 
}

// Funkcja generująca stopkę strony HTML
String HTMLFooter() {
    return "<p>Adam Chodura, Ryszard Górczak, Szymon Kosma</p></body></html>";
}

// Funkcja generująca całą stronę HTML, w tym sterowanie dla przekaźników i LED
String HTMLPage() {
    String p = "<h3>Sterowanie basenem</h3>";
    const char* labels[] = {"Do basenu", "Do zbiornika grzewczego", "Napowietrzacz", "Elektrozawór"};
    // Pętla generująca przyciski dla każdego z czterech przekaźników
    for (int i = 0; i < 4; i++) {
        p += "<p>" + String(labels[i]) + "</p>";
        p += digitalRead(przekazniki[i]) == LOW ? "<a href='/przekaznik" + String(i) + "-wylaczony'><button class='btn btn-danger'>OFF</button></a>"
                                               : "<a href='/przekaznik" + String(i) + "-wlaczony'><button class='btn btn-success'>ON</button></a>";
    }
    // Przyciski sterujące LED
    p += "<p>LED</p>";
    p += ledstate ? "<a href='/led-wylaczony'><button class='btn btn-danger'>OFF</button></a>"
                  : "<a href='/led-wlaczony'><button class='btn btn-success'>ON</button></a>";
    return p;
}

// Funkcja generująca pełną stronę HTML
String WebPage() {
    return HTMLHeader() + HTMLPage() + HTMLFooter();
}

// Funkcja do obsługi zmiany stanu przekaźnika
void handleRelay(int relay, bool state) {
    digitalWrite(przekazniki[relay], state ? LOW : HIGH); // Włączenie/wyłączenie przekaźnika
    server.send(200, "text/html", WebPage()); // Odświeżenie strony po zmianie stanu
}

// Funkcja do ustawienia serwera HTTP i jego routingu
void setservers() {
    server.on("/", []() { server.send(200, "text/html", WebPage()); });  // Strona główna

    // Ustawienie routingu dla przekaźników (włączenie/wyłączenie)
    for (int i = 0; i < 4; i++) {
        server.on("/przekaznik" + String(i) + "-wlaczony", [i]() { handleRelay(i, true); });
        server.on("/przekaznik" + String(i) + "-wylaczony", [i]() { handleRelay(i, false); });
    }

    // Obsługa włączenia/wyłączenia LED
    server.on("/led-wlaczony", []() {
        ledstate = true; // Ustawienie stanu LED na włączony
        for (int i = 0; i < NUM_LEDS; i++) setColor(i, 200, 200, 100);  // Ustawienie koloru LED na żółty
        server.send(200, "text/html", WebPage());
    });

    server.on("/led-wylaczony", []() {
        ledstate = false; // Ustawienie stanu LED na wyłączony
        for (int i = 0; i < NUM_LEDS; i++) setColor(i, 0, 0, 0);  // Wyłączenie diod
        server.send(200, "text/html", WebPage());
    });

    server.begin(); // Uruchomienie serwera
}

void setup() {
    WiFi.mode(WIFI_AP);  // Ustawienie ESP8266 w tryb AP (Access Point)
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));  // Ustawienie konfiguracji AP
    WiFi.softAP(ssid, password);  // Uruchomienie sieci Wi-Fi z nazwą i hasłem

    Serial.begin(115200);  // Inicjalizacja komunikacji szeregowej
    for (int i = 0; i < 4; i++) {
        pinMode(przekazniki[i], OUTPUT);  // Ustawienie pinów przekaźników jako wyjścia
        digitalWrite(przekazniki[i], LOW); // Wyłączenie przekaźników
    }

    pixels.begin();  // Inicjalizacja diod NeoPixel
    for (int i = 0; i < NUM_LEDS; i++) setColor(i, 0, 0, 0);  // Wyłączenie diod NeoPixel

    setservers();  // Ustawienie serwera i jego routingu
}

void loop() {
    server.handleClient();  // Obsługuje zapytania HTTP od klientów
}
