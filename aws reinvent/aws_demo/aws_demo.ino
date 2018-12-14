#include <ESP8266WiFi.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
 
const static char ssid[] = "ATT-WIFI-665M";
const static char pass[] = "PubNub2018"; 

int rled = 15; // The PWM pins the indicator LEDs are attached to.
int gled = 12;
int bled = 14;
int drled = 13; // The pins the display LEDs are attached to.
int dgled = 2;
int dbled = 0;
int controlpin = 10; // The pin the relay is attached to.

int mode = 0;
bool on = false;
String last = "off"; 

void setup() {
    pinMode(controlpin, OUTPUT);
    pinMode(rled, OUTPUT);
    pinMode(gled, OUTPUT);
    pinMode(bled, OUTPUT);
    pinMode(drled, OUTPUT);
    pinMode(dgled, OUTPUT);
    pinMode(dbled, OUTPUT);

    Serial.begin(9600);
    WiFi.begin(ssid, pass);
    if(WiFi.waitForConnectResult() == WL_CONNECTED){
      PubNub.begin("pub-c-ae388464-6b8a-430e-be0a-64377c198dda", "sub-c-77c1dde4-dc65-11e8-b7c4-3e16c06ff365");
    } else {
      Serial.println("Couldn't get a wifi connection");
      while(1) delay(100);
    }
}
 
void loop() {
    PubNub_BASE_CLIENT *client;
    
    Serial.println("waiting for a message (subscribe)");
    PubSubClient *pclient = PubNub.subscribe("tp"); // Subscribe to the control channel.
    if (!pclient) {
        Serial.println("subscription error");
        delay(1000);
        return;
    }
    String message;
    while (pclient->wait_for_data()) {
        char c = pclient->read();
        //Serial.print(c);
        message = message+String(c); // Append to string.
    }
    pclient->stop();
    
    if(message.indexOf(last) == -1  ) {
      if(message.indexOf("on") > 0) {
          last = "on";
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(30);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(60);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(30);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(40);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(30);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, HIGH);
          delay(50);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, LOW);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, HIGH);
          delay(60);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(40);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          digitalWrite(controlpin, HIGH);
      } else if (message.indexOf("off") > 0) {
          last = "off";
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(40);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(30);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, HIGH);
          delay(50);
          digitalWrite(rled, LOW);
          digitalWrite(drled, HIGH);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, HIGH);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, HIGH);
          digitalWrite(drled, LOW);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, HIGH);
          delay(60);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, HIGH);
          digitalWrite(dbled, HIGH);
          delay(40);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, HIGH);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          delay(40);
          digitalWrite(rled, LOW);
          digitalWrite(drled, LOW);
          digitalWrite(gled, LOW);
          digitalWrite(dgled, LOW);
          digitalWrite(bled, LOW);
          digitalWrite(dbled, LOW);
          digitalWrite(controlpin, LOW);
      }
    }
    Serial.print(message);
    Serial.println();
    delay(5);
}

