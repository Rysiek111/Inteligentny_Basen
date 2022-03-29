#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define pinLED D0
#define przekaznik1 D1
#define przekaznik2 D2
#define przekaznik3 D3
#define PINLED D6
#define przekaznik6 D7
#define NUMPIXELS      46

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINLED, NEO_GRB + NEO_KHZ800);

const char* ssid = "Basen";


const unsigned int port = 80;
ESP8266WebServer server(port);
String HTMLHeader() { //nagłówek strony
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
String HTMLFooter() {    // stopka strony www
  String f = "";
  f += "<p>Adam Chodóra, Ryszard Górczak,Szymon Kosma &copy2021</p></td></tr>";
  f += "</body>\n";
  f += "</html>\n";
  return f;
}
String HTMLPage() {
  String p = "";
  p += "<p><h3>Sterowanie basenem</h3></p>\n";
  p += ( "R: <INPUT TYPE=number ID='RED'  VALUE='0' MIN='0' MAX='255' SIZE='25' MAXLENGTH='50'></FORM>");
  p += ( "G: <INPUT TYPE=number ID='GREEN'  VALUE='0' MIN='0' MAX='255' SIZE='25' MAXLENGTH='50'></FORM>");
  p += ( "B: <INPUT TYPE=number ID='BLUE'  VALUE='0' MIN='0' MAX='255' SIZE='25' MAXLENGTH='50'></FORM>");
  p += ("<p><a href = \"/LED\"><button class=\"btn btn-danger\">Ustaw kolor</button></a></p>\n");
  p += ( (digitalRead(pinLED) == 0) ? "<p><a href = \"/przekaznik0-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik0-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik1) == 0) ? "<p><a href = \"/przekaznik1-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik1-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik2) == 0) ? "<p><a href = \"/przekaznik2-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik2-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  p += ( (digitalRead(przekaznik3) == 0) ? "<p><a href = \"/przekaznik3-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik3-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  //  p += ( (digitalRead(przekaznik4) == 0) ? "<p><a href = \"/przekaznik4-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik4-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  //  p += ( (digitalRead(przekaznik5) == 0) ? "<p><a href = \"/przekaznik5-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik5-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
  // p += ( (digitalRead(przekaznik6) == 0) ? "<p><a href = \"/przekaznik6-wylaczony\"><button class=\"btn btn-danger\">przekaźnik WŁĄCZONY</button></a></p>\n" : "<p><a href = \"/przekaznik6-wlaczony\"><button class=\"btn btn-success\">przekaźnik WYŁĄCZONY</button></a></p>\n");
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
  //adres załączajacy przekaźnik0
  server.on("/przekaznik0-wlaczony", []() {
    digitalWrite(pinLED, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik0
  server.on("/przekaznik0-wylaczony", []() {
    digitalWrite(pinLED, HIGH); //stan wysoki wyłącza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres załączajacy przekaźnik1
  server.on("/przekaznik1-wlaczony", []() {
    digitalWrite(przekaznik1, LOW); //stan niski załacza LED wewnętrzny
    server.send(200, "text/html", WebPage());
  });
  //adres wyłączajacy przekaźnik2
  server.on("/przekaznik1-wylaczony", []() {
    digitalWrite(przekaznik1, HIGH); //stan wysoki wyłącza LED wewnętrzny
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
  //  server.on("/przekaznik4-wlaczony", []() {
  //    digitalWrite(przekaznik4, LOW); //stan niski załacza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //  //adres wyłączajacy przekaźnik4
  //  server.on("/przekaznik4-wylaczony", []() {
  //    digitalWrite(przekaznik4, HIGH); //stan wysoki wyłącza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //  //adres załączajacy przekaźnik5
  //  server.on("/przekaznik5-wlaczony", []() {
  //    digitalWrite(przekaznik5, LOW); //stan niski załacza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //  //adres wyłączajacy przekaźnik1
  //  server.on("/przekaznik5-wylaczony", []() {
  //    digitalWrite(przekaznik5, HIGH); //stan wysoki wyłącza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //adres załączajacy przekaźnik6
  //  server.on("/przekaznik6-wlaczony", []() {
  //    digitalWrite(przekaznik6, LOW); //stan niski załacza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //  //adres wyłączajacy przekaźnik6
  //  server.on("/przekaznik6-wylaczony", []() {
  //    digitalWrite(przekaznik6, HIGH); //stan wysoki wyłącza LED wewnętrzny
  //    server.send(200, "text/html", WebPage());
  //  });
  //  server.on("/LED", []() {
  //    //    int redColor = RED;
  //    //    int greenColor = GREEN.value;
  //    //    int blueColor = BLUE.value;
  //    //
  //    //    pixels.begin();
  //    //
  //    //    for (int i = 0; i < NUMPIXELS; i++) {
  //    //
  //    //      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
  //    //
  //    //
  //    //      pixels.show();
  //    //
  //    //
  //    //      delay(100);
  //    //    }
  //    //
  //    server.send(200, "text/html", WebPage());
  //  });

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
  WiFi.softAP("Basen", "1234567890");
  //Sieć koniec kodu

  //Servis www
  Serial.begin(115200);
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

  //  pinMode(przekaznik4, OUTPUT);
  //  //wyłącz przekaznik
  //  digitalWrite(przekaznik4, LOW);

  //  pinMode(przekaznik5, OUTPUT);
  //  //wyłącz przekaznik
  //  digitalWrite(przekaznik5, LOW);

  //  pinMode(przekaznik6, OUTPUT);
  //  //wyłącz przekaznik
  //  digitalWrite(przekaznik6, LOW);
  setservers();

}

void loop() {
  server.handleClient();
}