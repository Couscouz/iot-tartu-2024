#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "iotempire-04"
#define STAPSK "iotempire"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "10.42.0.145";
const int led = LED_BUILTIN;
const int button = D5;

bool ledsOn = true;
int state_button = 0; 

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
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
  int buttonState = digitalRead(button);
  Serial.print(buttonState);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  if(buttonState == LOW){
    state_button += 1;
  }
  // We now create a URI for the request
  String red = "/red";
  String blue = "/blue";
  String green = "/green";
  
  // Lire l'état actuel du bouton
  

// Vérifier s'il y a eu un changement d'état du bouton
  state_button = state_button % 3;
  if(state_button == 0 && buttonState == LOW){
    Serial.print("bouton red");
        client.print(String("GET ") + red + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  }
    if(state_button == 1 && buttonState == LOW){
    Serial.print("bouton blue");
        client.print(String("GET ") + blue + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  }  
  if(state_button == 2 && buttonState == LOW){
    Serial.print("bouton green");
        client.print(String("GET ") + green + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  }
  buttonState = HIGH;
  
  Serial.println();
  Serial.println("closing connection");
}