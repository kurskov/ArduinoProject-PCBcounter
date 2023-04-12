/*
  PCB Counter

  Version: 1.0.0
  
  Author: Dmitrii Kurskov <dmitrii@kurskov.ru>
  GitHub: https://github.com/kurskov/ArduinoProject-PCBcounter
  License: MIT License
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/* DEBUG MODE */

#define DEBUG_ON           // comment this string for debug mode turn off

#ifdef DEBUG_ON
    #define DEBUG(x) Serial.println(x)
#else
    #define DEBUG(x)
#endif


/* ARDUINO PINS */

#define PIN_IRS 2          // pin of IR sensor
#define PIN_CONV 4         // pin of conveyor
#define PIN_BUZZER 7       // pin of buzzer
#define PIN_RESET 8        // pin of reset buzzer
#define PIN_LED 13         // pin of LED on board (PCB indication)


/* SETTINGS */

#define COUNT_TARGET 5    // target for PCB counter


// starting set for trigger of PCB position
bool conveyor = false;

// PCB counter
int counter = 0;

// LCD 16x2, I2C adress: 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  
  #ifdef DEBUG_ON
     Serial.begin(9600);
  #endif
  
  // pin setting
  pinMode(PIN_IRS, INPUT);
  pinMode(PIN_CONV, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RESET, INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED, LOW);

  // run display
  lcd.init();
  lcd.backlight();
  displayReset();
  
  DEBUG("Initialization complete");

}

void loop() {
  
  if ( !conveyor && digitalRead(PIN_CONV) ) { // conveyor started
    DEBUG("Conveyor started");
    if ( digitalRead(PIN_IRS) ) { // PCB on the conveyor
      DEBUG("PCB on the conveyor");
      counter++;  // increment of PCB counter
      digitalWrite(PIN_LED, HIGH);
      if (counter >= COUNT_TARGET) {  // run buzzer
        DEBUG("Buzzer on");
        tone(PIN_BUZZER, 523);
       }
    }
    conveyor = true;
  } else if ( conveyor && !digitalRead(PIN_CONV) ) {  // conveyor stoped and trigger reset
    DEBUG("Conveyor stoped");
    conveyor = false;
    digitalWrite(PIN_LED, LOW);
  }

  // stop buzzer
  if ( digitalRead(PIN_RESET) && counter ) {
    DEBUG("Buzzer off, counter reset.");
    noTone(PIN_BUZZER);
    counter = 0;
    displayReset();
  }
  
  // print result
  lcd.setCursor(9, 1);
  lcd.print(counter);
  
}

void displayReset() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Limit:   ");
  lcd.print(COUNT_TARGET);
  lcd.setCursor(0, 1);
  lcd.print("Counter: ");
  lcd.print(counter);
  
}
