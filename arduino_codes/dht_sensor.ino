// Capteur de temperature et d'humidite DHT11
// https://tutoduino.fr/
// Copyleft 2020
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
// Definit la broche de l'Arduino sur laquelle la 
// broche DATA du capteur est reliee 
#define DHTPIN D2
// Definit le type de capteur utilise
#define DHTTYPE DHT11
// Declare un objet de type DHT
// Il faut passer en parametre du constructeur 
// de l'objet la broche et le type de capteur
DHT dht(DHTPIN, DHTTYPE);

float tempC;
float humidity;
// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "iotempire-04";
const char* password = "iotempire";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.12.1";

// Initializes the espClient.
WiFiClient esp_temp_portable;
PubSubClient client(esp_temp_portable);

// This connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions reconnects your ESP8266 to your MQTT broker
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("esp_temp_portable")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("temperature/value");
      client.subscribe("humidity/value");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  float tempC = -1.0;
  float humidity = -1.0;
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //Turn off wifi access point
  WiFi.mode(WIFI_STA);
 }
// ensures that you ESP is connected to wifi and mqtt broker
void loop() {
  //connect wifi if not connected
  if (WiFi.status() != WL_CONNECTED) {
    delay(1);
    setup_wifi();
    return;
}
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("esp_temp_portable");

  tempC = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.println("Temperature = " + String(dht.readTemperature())+" Â°C");
  Serial.println("Humidite = " + String(dht.readHumidity())+" %");
  Serial.print("ca marche");
  char msgt[10]; 
  char msgh[10];

  sprintf(msgh,"%f",humidity);
  sprintf(msgt,"%f",tempC);
  client.publish("temperature/value", msgt );
  client.publish("humidity/value" , msgh);
  delay(10000);
}

