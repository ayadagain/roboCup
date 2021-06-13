// Libs
#include "functions.h"
#include <Arduino.h>
#include <HCSR04.h>
#include <Wire.h>
// Variables Init
const int s1TrigPin = 9;
const int s1EchoPin = 10;
const int ledPin = 2;
// motor pins
const int m1p1 = 2;
const int m1p2 = 3;
const int m2p1 = 4;
const int m2p2 = 5;
String x;
int *lineSensorReadings;
// Initializers
HCSR04 uSensor1 = ultrasonicInit(s1TrigPin, s1EchoPin);
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Ready!");
  delayMicroseconds(1000);
  pinMode(ledPin, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  uSensor1.begin();
}

void loop()
{
  lineSensorReadings = lineFollowingModule();

  for (int i = 0; i < 5; i++)
  {
    Serial.print(lineSensorReadings[i]);
    Serial.print(' ');
  }

  Serial.println(' ');
}