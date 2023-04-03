#define PIN_IRS 2;          // pin of IR sensor
#define PIN_CONV 4;         // pin of conveyor
#define PIN_BUZZER 7;       // pin of buzzer
#define PIN_RESET 8;        // pin of reset buzzer

#define COUNT_TARGET 10;    // target for PCB counter

void setup() {
  // starting set for trigger of PCB position
  bool ir_sensor = false;
  bool conveyor = false;
  
  // buzzer status
  bool buzzer = false;
  
  // PCB counter
  int counter = 0;

  // pin setting
  pinMode(PIN_IRS, INPUT_PULLUP);
  pinMode(PIN_CONV, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RESET, INPUT_PULLUP);
}

void loop() {
  if ( !conveyor && digitalRead(PIN_CONV) ) { // conveyor started
    if ( !ir_sensor && digitalRead(PIN_IRS) ) { // PCB on the conveyor
      counter++;  // increment of PCB counter
      ir_sensor = true; // set trigger
      if (counter >= COUNT_TARGET) {  // run buzzer
        digitalWrite(PIN_BUZZER, HIGH);
      }
    }
    conveyor = true;
  } else if ( conveyor && !digitalRead(PIN_CONV) ) {  // conveyor stoped and trigger reset
    conveyor = false;
    ir_sensor = false;
  }

  // stop buzzer
  if ( digitalRead(PIN_RESET) ) {
    digitalWrite(PIN_BUZZER, LOW);
  }
}

