/*
  Teleporter Firmware
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

 // Connection info.
const char* ssid = "pubnub-visitor";
const char* password =  "data-stream!";
const char* mqttServer = "mqtt.pndsn.com";
const int mqttPort = 1883;
const char* clientID = "pub-c-ae388464-6b8a-430e-be0a-64377c198dda/sub-c-77c1dde4-dc65-11e8-b7c4-3e16c06ff365/teleporter";
WiFiClient espClient;
PubSubClient client(espClient);

// Define pins.
Servo releaseServo;
int rled = 15; // The PWM pins the indicator LEDs are attached to.
int gled = 12;
int bled = 14;
int drled = 13; // The pins the display LEDs are attached to.
int dgled = 2;
int dbled = 0;
int buzzer = 5; // The pin the buzzer is attached to.
int servo = 4; // The pin the servo is attached to.
int relay = 10; // The pin the relay header is attached to.

// Timing.
bool tick;
unsigned long previousMillis = 0;
unsigned long interval = 0;
int state = 0;
 
void setup() {
  Serial.begin(9600);
  
  // Initialize outputs.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(drled, OUTPUT);
  pinMode(dgled, OUTPUT);
  pinMode(dbled, OUTPUT);
  pinMode(relay, OUTPUT);
  releaseServo.attach(servo);
  releaseServo.write(90);

  // Turn on power strip.
  digitalWrite(relay, HIGH);

  // Start WiFi and connect.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect(clientID)) {
      Serial.println("connected");  
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  client.subscribe("tp");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  String payload_buff;
  for (int i=0;i<length;i++) {
    payload_buff = payload_buff+String((char)payload[i]);
  }
  Serial.println(payload_buff);
  digitalWrite(rled, LOW);
  digitalWrite(drled, LOW);
  digitalWrite(gled, LOW);
  digitalWrite(dgled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(dbled, LOW);
  if (payload_buff.indexOf("open") > 0) {
    state = -1;
    releaseServo.write(150);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,440,150);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    delay(400);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,440,150);
    delay(450);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    delay(400);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,440,450);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    state = 0;
  } else if (payload_buff.indexOf("close") > 0) {
    state = -1;
    releaseServo.write(90);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,330,150);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    delay(400);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,330,150);
    delay(450);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    delay(400);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    tone(buzzer,330,450);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    state = 0;
  } else if (payload_buff.indexOf("off") > 0) {
    tone(buzzer,350,1000);
    state = 0;
  } else if (payload_buff.indexOf("l1") > 0) {
    state = -1;
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,500);
    delay(250);
    state = 1;
  } else if (payload_buff.indexOf("l2") > 0) {
    state = -1;
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,500);
    delay(250);
    state = 2;
  } else if (payload_buff.indexOf("l3") > 0) {
    state = -1;
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, LOW);
    tone(buzzer,622,250);
    delay(250);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(100);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    tone(buzzer,622,500);
    delay(250);
    state = 3;
  } else if (payload_buff.indexOf("release") > 0) {
    state = -1;
    tone(buzzer,422,1500);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(80);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(120);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, HIGH);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(50);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    delay(90);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, LOW);
    delay(60);
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
    digitalWrite(relay, HIGH);
    delay(70);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(120);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, HIGH);
    delay(50);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, LOW);
    delay(110);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
      digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(80);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(120);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, HIGH);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(50);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, HIGH);
    delay(90);
    digitalWrite(rled, LOW);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, LOW);
    delay(60);
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
    digitalWrite(relay, HIGH);
    delay(70);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    digitalWrite(relay, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(120);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, HIGH);
    delay(50);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(dgled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    delay(60);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(dbled, HIGH);
    digitalWrite(relay, LOW);
    delay(110);
    digitalWrite(rled, HIGH);
    digitalWrite(drled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    releaseServo.write(150);
    delay(320);
    digitalWrite(relay, HIGH);
    releaseServo.write(90);
    delay(2050);
    tone(buzzer,822,200);
    digitalWrite(rled, LOW);
    digitalWrite(drled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(dgled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(dbled, LOW);
    state = 0;
  }
  digitalWrite(drled, LOW);
  digitalWrite(dgled, LOW);
  digitalWrite(dbled, LOW);
}
 
void loop() {
  client.loop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (state == 0) {
      if (tick) {
        interval = 150;
        tick = false;
        digitalWrite(rled, HIGH);
        digitalWrite(drled, HIGH);
      } else {
        interval = 2000;
        tick = true;
        digitalWrite(rled, LOW);
        digitalWrite(drled, LOW);
      }
    } else if (state == 1) {
      if (tick) {
        interval = 700;
        tick = false;
        digitalWrite(drled, HIGH);
        digitalWrite(dgled, HIGH);
        digitalWrite(dbled, HIGH);
      } else {
        interval = 400;
        tick = true;
       digitalWrite(drled, LOW);
        digitalWrite(dgled, LOW);
        digitalWrite(dbled, LOW);
      }
    } else if (state == 2) {
      if (tick) {
        interval = 500;
        tick = false;
        digitalWrite(drled, HIGH);
        digitalWrite(dgled, HIGH);
        digitalWrite(dbled, HIGH);
      } else {
        interval = 300;
        tick = true;
        digitalWrite(drled, LOW);
        digitalWrite(dgled, LOW);
        digitalWrite(dbled, LOW);
      }
    } else if (state == 3) {
      if (tick) {
        interval = 300;
        tick = false;
        digitalWrite(drled, HIGH);
        digitalWrite(dgled, HIGH);
        digitalWrite(dbled, HIGH);
      } else {
        interval = 200;
        tick = true;
        digitalWrite(drled, LOW);
        digitalWrite(dgled, LOW);
        digitalWrite(dbled, LOW);
      }
    }

  }
}
