#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire to pin D4 on the ESP8266 - GPIO 2
#define ONE_WIRE_BUS D2

// Setup oneWire
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found
float tempC;

DeviceAddress tempDeviceAddress;

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
  sensors.begin();
  numberOfDevices = sensors.getDeviceCount();

  float tempC = -1.0;
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  for(int i=0;i<numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
		} else {
		  Serial.print("Found ghost device at ");
		  Serial.print(i, DEC);
		  Serial.print(" but could not detect address. Check power and cabling");
		}
  }
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

  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
		
		// Output the device ID
		Serial.print("Temperature for device: ");
		Serial.println(i,DEC);

    // Print the data
    tempC = sensors.getTempC(tempDeviceAddress);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
    } 	
  }
  Serial.print("ca marche");
  char msg[10]; 

  sprintf(msg,"%f",tempC);
  client.publish("temperature/value", msg );
  delay(10000);
  }

 void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}