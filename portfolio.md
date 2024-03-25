

# Portfolio

## Who are we ?

We're two French guys who are here to discover the principles of the IoT. We have the same name and come from the same engineering school. Our main course of study is cybersecurity, but we're keen to learn more about many aspects of the IoT. We're curious, committed and determined.

## What is IoT

IoT is a generic terms which is use to gather billion of connected devices in a wide range of fields such as :
 - Health Care
 - Military
 - Agriculture
 - Smart cities
 - Industrial automation
	
The Internet of Things covers a lot of devices, which can be :
 - Google Home, Raspberry PI, Computers, Smartphones ...
 - Smart sensors, smart watches, smart bicycles, smart houses ...

It's also present in many common protocols like :

 - MQTT (Message Queuing Telemetry Transport) : which is a standard messaging protocols for IoT, lightweight and efficient
 - Bluetooth
 - HTTP

    
The main benefits of such devices are
 - **Communication**
 - Full digitization
 - Quick access to processed data
 - Remote control
    
and challenges are most likely
 - Security
 - Compatibility 
 - Privacy
 - Power Consumption 
   
We can also note that most of people doesn't realize that we are surrounded by tons of IoT devices without realizing it, yet everyone are using them all day long.
    
We can imagine a scenario such as :

**Harvest management, animal geolocation, Breeding data processing, Integrated messaging**

*The Holy Cow*

Farmer : Mikael, Neighbor: Walt, Cow: Marguarita

Mikael is the owner of a huge farm in Cuzco in Peru. He has 999 cows which are daily running in his 99 acres.
He also has some wheat fields in order to feed his cows.
The weather is sunny like 26 and Mikael is riding his tractor in one of his giant wheat field.
He looks down at his iPad and sees the progress of his harvest in live.
An audible and visual notification interrupts him, indicating that one of his beasts is no longer within his perimeter (field).
He puch the notification that opens the application, in which all his cows are geolocated and represented by green dots, except for one by a red dot, highlighted by the application.
Mikael then clicks on the red dot and accesses a wealth of data about the cow. He can see its exact location, speed and direction, as each cow is fitted with a GPS collar.
He then decides to call Walt, his neighbor, via the app to intercept Marguarita.
Mikael transfers Marguarita's data to Walt, who can then react and retrieve the cow.
Once Marguarita has been caught, Walt informs Mikael via the app's messaging system, who then unlocks access to the fence remotely.
Walt can cross the fence with his tractor and Marguarita.
And Mikael hasn't moved from his tractor, so he can finish harvesting with peace of mind.




## Week 2

**CLOUD Schema**

We made up a diagram of the global iot architecture, it can be found under the name *iot_architecture.jpg*

**Informations about ESP ecosystem**

The ESP ecosystem, primarily centered around the ESP8266 and ESP32 microcontrollers, has gained immense popularity in the maker and DIY communities due to its affordability, versatility, and ease of use.

Arduino IDE compatible (as well as IOT Empire framework)
ESP8266 is as cheap as a good coffee (chip less than 1$)
A lot of versions (with batteries, relays ...)
ESP32 is the successor of ESP8266
Uses cases : Sensors and switches

So as a conclusion, when you see the price of such devices, the "ease" of use, we can easily say that this is democratization of hardware.

**Practical**

After finishing the *iot_kit_inventory.jpg* table, with all the details of each component, we started the real practical.

First of all, we started with a ESP8266 board and the simple blink program. It turned out to work pretty well. The installation can be found in the picture *blinking_led.jpg*

Then we added a button to change the blink speed, and we made up this :

```c++
int delayTime = 1000;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, INPUT_PULLUP); // Activer la résistance de pull-up interne
}

// the loop function runs over and over again forever
void loop() {
  int buttonState = digitalRead(D6);

  // Si le bouton est enfoncé, diminuez la vitesse de clignotement
  if (buttonState == LOW) {
    delayTime = 2000; // Changer le délai à 2 secondes
  } else {
    delayTime = 200; // Sinon, garder le délai à 1 seconde
  }
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(D4, LOW);
  // turn the LED on (HIGH is the voltage level)
  delay(delayTime);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(D4, HIGH);
  // turn the LED off by making the voltage LOW
  delay(delayTime);
}
```

The picture of the installation is *blinking_led_with_button.jpg*

Then we changed a bit the code to try to power the leds on and off at the same time, but we didnt manage to do so and the result was an alterating lighting. The code was :

```c++
const int LED_PIN_INTERNAL = LED_BUILTIN; // Broche pour la LED interne
const int LED_PIN_EXTERNAL = D4;          // Broche pour la LED externe
const int BUTTON_PIN = D6;                // Broche pour le bouton

int delayTime = 1000; // Délai initial de clignotement (1 seconde)
bool ledsOn = true;   // Variable pour suivre l'état actuel des LEDs
bool OldButtonState = HIGH; 

void setup() {
  pinMode(LED_PIN_INTERNAL, OUTPUT);
  pinMode(LED_PIN_EXTERNAL, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Activer la résistance de pull-up interne

  // Initialisez les LEDs à l'état initial (allumées)
  digitalWrite(LED_PIN_INTERNAL, LOW);
  digitalWrite(LED_PIN_EXTERNAL, LOW);
}

void loop() {
  // Lire l'état actuel du bouton
  int buttonState = digitalRead(BUTTON_PIN);

  // Vérifier s'il y a eu un changement d'état du bouton
  if (buttonState != OldButtonState) {
      if (ledsOn) {
        digitalWrite(LED_PIN_INTERNAL, HIGH);
        digitalWrite(LED_PIN_EXTERNAL, HIGH);
        ledsOn = false;
      } else {
        digitalWrite(LED_PIN_INTERNAL, LOW);
        digitalWrite(LED_PIN_EXTERNAL, LOW);
        ledsOn = true;
      } 
  }
}
```

**RGB LED color mixer**

Then, we went to try the RGB mixer. It didn't work out as well as we'd hoped and we ended up trying several things (single-colored pine ...) which didn't work out.
The assembly is in picture *rbg_mixer_v1.jpg*
The last version of code that we used is : 

```c++
const int PIN_RED   = D5;
const int PIN_GREEN = D6;
const int PIN_BLUE  = D7;

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
}

void loop() {
  // color code #00C9CC (R = 0,   G = 201, B = 204)
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 201);
  analogWrite(PIN_BLUE,  0);

  delay(1000); // keep the color 1 second

  // color code #F7788A (R = 247, G = 120, B = 138)
  analogWrite(PIN_RED,   200);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  0);

  delay(1000); // keep the color 1 second

  // color code #34A853 (R = 52,  G = 168, B = 83)
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  200);

  delay(1000); // keep the color 1 second
}
```
## Week 3

**RGB LED button change color**

First we realise to build an installation to change the color of a LED. We inspired ourself with previous results and success to make it works.
The assembly is in gif ``RGB_LED_button.gif`` and the last version of code that we used is in ``rgb_led_button.ino``


**Kiosk Mode firefox**

We put firefox browser of our laptop in kiosk mode, with a default url of "localhost:5000" and a fullscreen, in order to easily display dashboards for the upcoming sessions.

**Meme Generator Flask App**

We made a simple Flask app which is displaying random memes from *meme-api.com*, the code of the falsk app can be found in the project ``TheMemes``. You can change your name with a simple form and a post request.

**Computer to microcontroller RGB LED via Web request**

We made a RGB mixer controllable with web request (/red, /green, /blue).
You can see the result in ``web_rgb_mixer.gif`` and the serial output in ``micro_web_output.jpg``
The code is in ``arduino_codes/rgb_via_web.ino``

**Button to Webhook, Webhook to curl to RGB Led**

Then, we made a controllable led via a wifi connected button on a second node.
You can see the result in ```led_button_wifi.gif`.
The 2 codes are in ``led_via_wifi_button``

**Add more hardware**

We decided to add another button in our setup.
The goal is to have one button controlling the color of the RGB led and another button only for on/off.
The code of this node can be found in ``led_via_2_wifi_buttons``
The sum up gif of this all setup is ``3_nodes_wifi.gif``

## Week 4

For this week we decided to go for the dashboard and the temperature sensor.
In fact, we ordered some in order to make passive wifi temperature in our flat.
First of all, we started by setting up Node-Red on the gateway computer, installing dashboards libraries and so.

Then we made a simple MQTT Hello world, composed of a MQTT in into a Debug block in order to print.
Secondly, a trigger into a MQTT out. Can be seen in ``nodered_1.png``

After this, we made a dashboard composed with a Gauge and a Chart (``nodered_2.png``). 
In input we have a MQTT sub, giving data to a function in order to extract temperature and send it to the Gauge and the Chart.


In the second part of our work, we went for:
Temperature sensor on a node, sending each 5 seconds via MQTT to node-red server.
Then node-red is logging, dashboarding and sending it via Discord bot (``images/dicord.png``).

The node-red flow is in (``flows/discord_dashboard.json``) or also (``images/node-red-1``).
The node code is in (``arduino-ide/temperature_mqtt.ino``).
