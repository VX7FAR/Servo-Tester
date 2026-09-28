/*
1 -> 21
2 -> 10
3 -> 7
4 -> 5
5 -> 4
6 -> 3
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "animation.h"
#include <string.h>

String mode = "manual";

size_t SCREEN_WIDTH = 128;
size_t SCREEN_LENGTH = 32;
uint8_t ADDRESS = 0x3C;         //Set to whatever your address is, normally it is 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_LENGTH, &Wire, -1);

float pulse = 0.0f;
size_t max = 1023;
size_t min = 0;
float range = max - min;
size_t servopin = 11;

float increment = 5.55f;

bool sweep = false;         //This refers to the mode button  
uint8_t sweep_pin = 3;
bool reset = false; 
uint8_t reset_pin = 7;

const uint8_t *start_animation[] = {frame0, frame1, frame2, frame3, frame4, frame5, frame6, frame7, frame8, frame9, frame10, frame11} ;

void setup(){
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, ADDRESS)){
    while (true){ Serial.println("Display not found"); }
  }

  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  pinMode(3, OUTPUT);
  pinMode(sweep_pin, INPUT);
  pinMode(7, OUTPUT);
  pinMode(reset_pin, INPUT);
  pinMode(servopin, OUTPUT);

  //Remove the code below till the end of setup() if you dont want animation
  for(int i=0; i<12; i++){
    display.clearDisplay();
    display.setCursor(0,0);
    display.drawBitmap(0,0,start_animation[i], 128, 32, SSD1306_WHITE);
    display.display();
    delay(125);
  }
  display.clearDisplay();
}

void loop(){
  sweep = digitalRead(sweep_pin);
  reset = digitalRead(reset_pin);
  pulse = range/ float(analogRead(0));
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("MODE: " + mode);

  if(sweep && reset){
    mode == "calibration";
  }
  else if(reset){
    mode == "reset";
  }
  else if(sweep){
    if(mode == "manual"){
      mode = "sweep";
    }
    else if(mode == "sweep"){
      mode = "manual";
    }
    else{
      mode = "manual";
    }
  }


  if(mode == "calibration"){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("MODE: CALIBRATION");
    display.setTextWrap(true);
    display.println("Move to maximum position for 3 seconds");
    display.display();
    delay(3000);
    max = analogRead(0);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("MODE: CALIBRATION");
    display.println("Move to minimum position for 3 seconds");
    display.display();
    delay(3000);
    min = analogRead(0);
  
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("MODE: CALIBRATION");
    display.setTextSize(3);
    display.println("DONE");
    display.display();
    display.setTextWrap(false);
    delay(1500);
    range = max - min;
  }
  else if(mode == "manual"){
    digitalWrite(servopin, LOW);
    digitalWrite(servopin, HIGH);
    delayMicroseconds(1000 + (pulse * 1000));
    digitalWrite(servopin, LOW);
    display.println("PULSE: " + String(1+pulse));
    display.println("ANGLE: " + String(pulse * 180.0));
    display.println("POT: " + String(pulse));
  }
  else if(mode == "sweep"){
    display.println("SPEED: " + String(pulse * 50));
    display.setTextWrap(true);
    display.println("Use the potentiometer for changing speed");

    float i = i + increment;
    if(i>1000){
      i = 1000.0;
      increment *= -1;
    }
    else if(i < 0){
      i = 0.0;
      increment *= -1;
    }
    digitalWrite(servopin, LOW);
    digitalWrite(servopin, HIGH);
    delayMicroseconds(1000 + i);
    digitalWrite(servopin, LOW);
    delay((1.0-pulse) * 50);
  }
  else if(mode == "reset"){
    display.setTextSize(3);
    display.println("RESET!");
    display.display();
    digitalWrite(servopin, LOW);
    digitalWrite(servopin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(servopin, LOW);
  }

  display.display();
}