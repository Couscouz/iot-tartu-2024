

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


**Informations about ESP ecosystem**

The ESP ecosystem, primarily centered around the ESP8266 and ESP32 microcontrollers, has gained immense popularity in the maker and DIY communities due to its affordability, versatility, and ease of use.

[videos stuff recap]

**Practical**

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
const int LED_PIN_EXTEWe improved our installation a bitRNAL = D4;          // Broche pour la LED externe
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

....