#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     D5
#define NUM_LEDS    34
const int przekazniki[] = {D0, D1, D2, D3};

bool ledstate = false;
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Basen";
const char* password = "1234567890";
ESP8266WebServer server(80);

void setColor(int led, int red, int green, int blue) {
    pixels.setPixelColor(led, pixels.Color(red, green, blue));
    pixels.show();
}

String HTMLHeader() {
    return "<!DOCTYPE html><html><head><title>Basen</title>"
           "<meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'>"
           "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'></head>"
           "<body style='text-align: center; color: white; background: black; font-size: 1.5em;'>";
}

String HTMLFooter() {
    return "<p>Adam Chodura, Ryszard Górczak, Szymon Kosma</p></body></html>";
}

String HTMLPage() {
    String p = "<h3>Sterowanie basenem</h3>";
    const char* labels[] = {"Do basenu", "Do zbiornika grzewczego", "Napowietrzacz", "Elektrozawór"};
    for (int i = 0; i < 4; i++) {
        p += "<p>" + String(labels[i]) + "</p>";
        p += digitalRead(przekazniki[i]) == LOW ? "<a href='/przekaznik" + String(i) + "-wylaczony'><button class='btn btn-danger'>OFF</button></a>"
                                               : "<a href='/przekaznik" + String(i) + "-wlaczony'><button class='btn btn-success'>ON</button></a>";
    }
    p += "<p>LED</p>";
    p += ledstate ? "<a href='/led-wylaczony'><button class='btn btn-danger'>OFF</button></a>"
                  : "<a href='/led-wlaczony'><button class='btn btn-success'>ON</button></a>";
    return p;
}

String WebPage() {
    return HTMLHeader() + HTMLPage() + HTMLFooter();
}

void handleRelay(int relay, bool state) {
    digitalWrite(przekazniki[relay], state ? LOW : HIGH);
    server.send(200, "text/html", WebPage());
}

void setservers() {
    server.on("/", []() { server.send(200, "text/html", WebPage()); });
    
    for (int i = 0; i < 4; i++) {
        server.on("/przekaznik" + String(i) + "-wlaczony", [i]() { handleRelay(i, true); });
        server.on("/przekaznik" + String(i) + "-wylaczony", [i]() { handleRelay(i, false); });
    }
    
    server.on("/led-wlaczony", []() {
        ledstate = true;
        for (int i = 0; i < NUM_LEDS; i++) setColor(i, 200, 200, 100);
        server.send(200, "text/html", WebPage());
    });
    
    server.on("/led-wylaczony", []() {
        ledstate = false;
        for (int i = 0; i < NUM_LEDS; i++) setColor(i, 0, 0, 0);
        server.send(200, "text/html", WebPage());
    });
    
    server.begin();
}

void setup() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password);
    
    Serial.begin(115200);
    for (int i = 0; i < 4; i++) {
        pinMode(przekazniki[i], OUTPUT);
        digitalWrite(przekazniki[i], LOW);
    }
    
    pixels.begin();
    for (int i = 0; i < NUM_LEDS; i++) setColor(i, 0, 0, 0);
    
    setservers();
}

void loop() {
    server.handleClient();
}
