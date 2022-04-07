//dodawanie potrzebnychbibliotek
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
//Definiowanie zmiennych
#define przekaznik0 D0
#define przekaznik1 D1
#define przekaznik2 D2
#define przekaznik3 D3
#define LED_PIN     D5
#define NUM_LEDS    34

//LEDY
bool ledstate = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
void setColor(int led, int redValue, int greenValue, int blueValue, int delayValue)
{
  pixels.setPixelColor(led, pixels.Color(redValue, greenValue, blueValue)); 
  pixels.show();
  delay(delayValue);
}
//koniec ledy

const char* ssid = "Basen";
const char* password = "1234567890";

//Tworzenie strony 
const unsigned int port = 80;
ESP8266WebServer server(port);
String HTMLHeader() { 
  String h = "<!DOCTYPE html>\n";
  h += "<html>";
  h += "<head>";
  h += "<title>Basen</title>";
  h += "<meta charset=\"utf-8\">";
  h += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  h += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\" >";
  h += "</head>";
  h += "<body style=\"text-align: center;color: white; background: black;font-size: 1.5em;\">\n";

  return h;
}

//Stopa strony
String HTMLFooter() {  
  String f = "";
  f += "<p>Adam Chodura, Ryszard Górczak,Szymon Kosma</p></td></tr>";
  f += "</body>\n";
  f += "</html>\n";
  return f;
}

//Przyciski
String HTMLPage() {
  String p = "";
  p += "<p><h3>Sterowanie basenem</h3></p>\n";
  p += "<p>Pompka:</p>\n";
  p += "<p>Do basenu</p>\n";
  p += ( (digitalRead(przekaznik0) == 0) ? "<p><a href = \"/przekaznik0-wylaczony\"><button class=\"btn btn-danger\">OFF</button></a></p>\n" : "<p><a href = \"/przekaznik0-wlaczony\"><button class=\"btn btn-success\">ON</button></a></p>\n");
  p += "<p>Do zbiornika grzewczego</p>\n";
  p += ( (digitalRead(przekaznik1) == 0) ? "<p><a href = \"/przekaznik1-wylaczony\"><button class=\"btn btn-danger\">OFF</button></a></p>\n" : "<p><a href = \"/przekaznik1-wlaczony\"><button class=\"btn btn-success\">ON</button></a></p>\n");
  p += "<p>Napowietrzacz</p>\n";
  p += ( (digitalRead(przekaznik2) == 0) ? "<p><a href = \"/przekaznik2-wylaczony\"><button class=\"btn btn-danger\">OFF</button></a></p>\n" : "<p><a href = \"/przekaznik2-wlaczony\"><button class=\"btn btn-success\">ON</button></a></p>\n");
  p += "<p>Elektrozawór</p>\n";
  p += ( (digitalRead(przekaznik3) == 0) ? "<p><a href = \"/przekaznik3-wylaczony\"><button class=\"btn btn-danger\">OFF</button></a></p>\n" : "<p><a href = \"/przekaznik3-wlaczony\"><button class=\"btn btn-success\">ON</button></a></p>\n");
  p += "<p>LED</p>\n";
  p += ( (ledstate == 1) ? "<p><a href = \"/led-wylaczony\"><button class=\"btn btn-danger\">OFF</button></a></p>\n":"<p><a href = \"/led-wlaczony\"><button class=\"btn btn-success\">ON</button></a></p>\n");
  return p;
}

String WebPage() {
  return HTMLHeader() + HTMLPage() + HTMLFooter();
}

//Koniec kodu strony

//Działanie przycisków
void setservers(void) {

  server.on("/", []() {
    server.send(200, "text/html", WebPage());
  });

  server.on("/przekaznik0-wlaczony", []() {
    digitalWrite(przekaznik0, LOW); 
    server.send(200, "text/html", WebPage());
  });
 
  server.on("/przekaznik0-wylaczony", []() {
    digitalWrite(przekaznik0, HIGH); 
    server.send(200, "text/html", WebPage());
  });
  
  server.on("/przekaznik1-wlaczony", []() {
    digitalWrite(przekaznik1, LOW); 
    server.send(200, "text/html", WebPage());
  });
  
  server.on("/przekaznik1-wylaczony", []() {
    digitalWrite(przekaznik1, HIGH); 
    server.send(200, "text/html", WebPage());
  });
  
  server.on("/przekaznik2-wlaczony", []() {
    digitalWrite(przekaznik2, LOW); 
    server.send(200, "text/html", WebPage());
  });
  
  server.on("/przekaznik2-wylaczony", []() {
    digitalWrite(przekaznik2, HIGH); 
    server.send(200, "text/html", WebPage());
  });

  server.on("/przekaznik3-wlaczony", []() {
    digitalWrite(przekaznik3, LOW); 
    server.send(200, "text/html", WebPage());
  });

  server.on("/przekaznik3-wylaczony", []() {
    digitalWrite(przekaznik3, HIGH); 
    server.send(200, "text/html", WebPage());
  });

    //adres załączajacy LED
  server.on("/led-wlaczony", []() {
    ledstate = 1;
    for(int led=0; led <=NUM_LEDS; led++)
    { 
      setColor(led,200,200,100,10);
    }
    server.send(200, "text/html", WebPage());
  });
  
  //adres wyłączajacy LED
  server.on("/led-wylaczony", []() {
    ledstate = 0;
    for(int led=0; led <=NUM_LEDS; led++)
    { 
      setColor(led,0,0,0,10);
    }
    server.send(200, "text/html", WebPage());
  });

  server.begin(); 
}
//koniec przycisków

void setup() {
  //Sieć Start
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  IPAddress localIp(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(localIp, gateway, subnet);
  WiFi.softAP("Basen", "1234567890");
  //Sieć koniec kodu

  Serial.begin(115200);
//Stan przycisków na początku
  pinMode(przekaznik0, OUTPUT);
  digitalWrite(przekaznik0, LOW);
  pinMode(przekaznik1, OUTPUT);
  digitalWrite(przekaznik1, LOW);
  pinMode(przekaznik2, OUTPUT);
  digitalWrite(przekaznik2, LOW);
  pinMode(przekaznik3, OUTPUT);
  digitalWrite(przekaznik3, LOW);
//ledy
  pixels.begin(); 
  
  for(int led=0; led <=NUM_LEDS; led++)
  { 
      setColor(led,0,0,0,10);
  }
  //koniec ledy

// Ustawia wyżej wymienione ustawienia
  setservers();
}

void loop() {
  server.handleClient();
}