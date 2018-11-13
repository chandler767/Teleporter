/*
  Teleporter Firmware

*/
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);

  pinMode(15, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);

  pinMode(10, OUTPUT);


  myservo.attach(4);  // attaches the servo on GIO2 to the servo object
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)

  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(14, LOW);   // turn the LED on (HIGH is the voltage level)


  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)

  //tone(5, 392, 100);

  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)

  digitalWrite(15, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(14, LOW);   // turn the LED on (HIGH is the voltage level)
 
    digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(1000);                       // wait for a second
}
