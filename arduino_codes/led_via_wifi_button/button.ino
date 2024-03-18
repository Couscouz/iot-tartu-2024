#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "iotempire-04"
#define STAPSK "iotempire"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "10.42.0.145";
const int led = LED_BUILTIN;
const int button = D3;

bool ledsOn = true;
bool OldButtonState = HIGH; 

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //works!

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(500);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String on = "/on";
  String off = "/off";

  // Lire l'état actuel du bouton
  int buttonState = digitalRead(button);

  // Vérifier s'il y a eu un changement d'état du bouton
  if (buttonState != OldButtonState) {
      if (ledsOn) {
        Serial.print("bouton on");
        client.print(String("GET ") + on + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
        ledsOn = false;
      } else {
        Serial.print("offfffffff");
        client.print(String("GET ") + off + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
        ledsOn = true;
      } 
  }

  Serial.println();
  Serial.println("closing connection");
}