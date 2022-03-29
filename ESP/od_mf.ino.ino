#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


/*LEDY*/
#include <Adafruit_NeoPixel.h>
#define LED_PIN     D6
#define NUM_LEDS    34
bool ledstate = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
void setColor(int led, int redValue, int greenValue, int blueValue, int delayValue)
{
  pixels.setPixelColor(led, pixels.Color(redValue, greenValue, blueValue)); 
  pixels.show();
  delay(delayValue);
}
/*koniec ledy*/
 
#define pinLED D0
#define przekaznik1 D1
#define przekaznik2 D2
#define przekaznik3 D3
#define przekaznik4 D4
#define przekaznik5 D5

const char* ssid = "Basen";


const unsigned int port = 80;
ESP8266WebServer server(port);
String HTMLHeader() { //nagłówek strony
  String h = "<!DOCTYPE html>\n";
  h += "<html>";
  h += "<head>";
  h += "<title></title>";
  h += "<meta charset=\"utf-8\">";
  h += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  h += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\" >";
  h += "</head>";
  h += "<body style=\"text-align: center;color: white; background: black;font-size: 1.5em;\">\n";

  return h;
}
String HTMLFooter() {    // stopka strony www
  String f = "";
  f += "<p>Adam Chodóra, Ryszard Górczak,Szymon Kosma 2021 &copy;</p></td></tr>";
  f += "</body>\n";
  f += "</html>\n";
  return f;
}
String HTMLPage() {
  String p = "";
  p += "<p><h3>Sterowanie basenem</h3></p>\n";
  p += ( (ledstate == 1) ? "<p><a href = \"/led-wylaczony\"><button class=\"btn btn-danger\">LED ON</button></a></p>\n":"<p><a href = \"/led-wlaczony\"><button class=\"btn btn-success\">LED OFF</button></a></p>\n");
  p += ( (digitalRead(pinLED) == 0) ? "<p><a href = \"/glowny\"><button class=\"btn btn-danger\">Do zbiornika retencyjnego</button></a></p>\n" : "<p><a href = \"/retencyjny\"><button class=\"btn btn-success\">Do zbiornika głównego</button></a></p>\n");
  p += ( (digitalRead(przekaznik2) == 0) ? "<p><a href = \"/pompka-OFF\"><button class=\"btn btn-danger\">OFF</button></a></p>\n" : "<p><a href = \"/przekaznik2-wlaczony\"><button class=\"btn btn-success\">BRAK</button></a></p>\n");
  p += ( (digitalRead(przekaznik2) == 0) ? "<p><a href = \"/przekaznik2-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik2-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik3) == 0) ? "<p><a href = \"/przekaznik3-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik3-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik4) == 0) ? "<p><a href = \"/przekaznik4-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik4-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik5) == 0) ? "<p><a href = \"/przekaznik5-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik5-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  return p;
}
String WebPage() {
  return HTMLHeader() + HTMLPage() + HTMLFooter();
}
//funkcja ustala adresy poszczególnych działań serwera www
void setservers(void) {
  //adres główny
  server.on("/", []() {
    server.send(200, "text/html", WebPage());
  });
  //adres lewo
  server.on("/glowny", []() {
    digitalWrite(pinLED, LOW); //stan niski załacza LED wewnętrzny
    digitalWrite(przekaznik1, LOW); //stan wysoki wyłącza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres prawo
  server.on("/retencyjny", []() {
    digitalWrite(pinLED, HIGH); //stan wysoki wyłącza LED wewnętrzny
    digitalWrite(przekaznik1, HIGH); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
    //adres off pompka
  server.on("/pompka-OFF", []() {
    digitalWrite(pinLED, HIGH); //stan wysoki wyłącza LED wewnętrzny
    digitalWrite(przekaznik1, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });

  //adres załączajacy przekaźnik2
  server.on("/przekaznik2-wlaczony", []() {
    digitalWrite(przekaznik2, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik2
  server.on("/przekaznik2-wylaczony", []() {
    digitalWrite(przekaznik2, HIGH); //stan wysoki wyłącza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres załączajacy przekaźnik3
  server.on("/przekaznik3-wlaczony", []() {
    digitalWrite(przekaznik3, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik3
  server.on("/przekaznik3-wylaczony", []() {
    digitalWrite(przekaznik3, HIGH); //stan wysoki wyłącza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres załączajacy przekaźnik4
  server.on("/przekaznik4-wlaczony", []() {
    digitalWrite(przekaznik4, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik4
  server.on("/przekaznik4-wylaczony", []() {
    digitalWrite(przekaznik4, HIGH); //stan wysoki wyłącza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres załączajacy przekaźnik5
  server.on("/przekaznik5-wlaczony", []() {
    digitalWrite(przekaznik5, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik1
  server.on("/przekaznik5-wylaczony", []() {
    digitalWrite(przekaznik5, HIGH); //stan wysoki wyłącza LED wewnętrzny
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

  server.begin(); // Start serwera www
}


void setup() {
  //Sieć Start
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  IPAddress localIp(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(localIp, gateway, subnet);
  WiFi.softAP("Basen");
  //Sieć koniec kodu

  //Servis www
  //Serial.begin(115200);
  //ustaw pin z LED na OUTPUT
  pinMode(pinLED, OUTPUT);
  //wyłącz LED
  digitalWrite(pinLED, LOW);
  pinMode(przekaznik1, OUTPUT);
  //wyłącz przekaznik
  digitalWrite(przekaznik1, LOW);
  pinMode(przekaznik2, OUTPUT);
  //wyłącz przekaznik
  digitalWrite(przekaznik2, LOW);
  pinMode(przekaznik3, OUTPUT);
  //wyłącz przekaznik
  digitalWrite(przekaznik3, LOW);
  pinMode(przekaznik4, OUTPUT);
  //wyłącz przekaznik
  digitalWrite(przekaznik4, LOW);
  pinMode(przekaznik5, OUTPUT);
  //wyłącz przekaznik
  digitalWrite(przekaznik5, LOW);
  
  pixels.begin(); // This initializes the NeoPixel library.
  
  for(int led=0; led <=NUM_LEDS; led++)
  { 
      setColor(led,0,0,0,10);
  }

  setservers();

  
}


void loop() {
  server.handleClient();
}
