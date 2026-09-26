/*
D3 -> SWEEP -> D4
D7  -> ALT -> D8
D11 -> SERVOSIGNAL

A4 -> SDA
A5 -> SCL
B10K -> A0
*/

#include <Arduino.h>

enum servomode
{
  calibration,
  sweep,
  manual,
  centre
};

float position = 0.0f;
bool mode_pressed = false;
bool old_mode = false;
bool reset_pressed = false;
servomode mode = manual;

float pot = 0.0f;
float range = 0.0f;
float min = 0;
float max = 1023;

size_t msdelay = 30;
float i = 5.55f;
float at = 0.0f;

void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(3, HIGH);

  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(7, HIGH);

  pot = analogRead(0);
  range = max - min;
}

void flipswitch(bool b, uint8_t pin)
{
  if (digitalRead(pin) == HIGH)
  {
    if (!b)
    {
      b = !b;
    }
    else
    {
      b = true;
    }
  }
  else
  {
    b = false;
  }
  delay(msdelay);
}

void loop()
{
  flipswitch(mode_pressed, 4);
  flipswitch(reset_pressed, 8);
  pot = (analogRead(0) - min) / range;

  if(!mode_pressed){
    old_mode = false;
  }

  // Manages input
  if (mode_pressed && reset_pressed)
  {
    mode = calibration;
  }
  else if (mode_pressed && !old_mode)
  {
    if (mode == sweep)
    {
      mode = manual;
    }
    else if (mode == manual)
    {
      mode = sweep;
    }
  }
  else if (reset_pressed)
  {
    mode = centre;
  }

  // Manages Controlling of servos
  if (mode == calibration)
  {
    Serial.print("Calibrating mode \n");
    Serial.print("Move and keep at hightest position for 3 seconds \n");
    delay(3000);
    max = analogRead(0);
    Serial.print("Move and keep at lowest position for 3 seconds \n");
    delay(3000);
    min = analogRead(0);
    range = max - min;
    Serial.print("Calibrated \n");
    mode = manual;
  }
  else if (mode == centre)
  {
    digitalWrite(11, LOW);
    digitalWrite(11, HIGH);
    delayMicroseconds(1500);
    digitalWrite(11, LOW);
  }
  else if (mode == manual)
  {
    digitalWrite(11, LOW);
    digitalWrite(11, HIGH);
    delayMicroseconds(1000 + (1000 * pot));
    digitalWrite(11, LOW);
  }
  else if (mode == sweep)
  {
    at += i;
    if(at >= 1000){
      at = 1000;
      i *= -1;
    } else if(at <= 0){
      at = 0;
      i *= -1;
    }

    digitalWrite(11, LOW);
    digitalWrite(11, HIGH);
    delayMicroseconds(1000 + at);
    digitalWrite(11, LOW);
    delay(50 * (1 - pot));
  }
}