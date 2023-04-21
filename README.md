[![GitHub](https://img.shields.io/github/license/kurskov/ArduinoProject-PCBcounter)](https://github.com/kurskov/ArduinoProject-PCBcounter/blob/main/LICENSE)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/kurskov/ArduinoProject-PCBcounter)](https://github.com/kurskov/ArduinoProject-PCBcounter/releases/latest)

# PCBcounter

The PCB counter for the destaker of a SMA line.

The counter receives data from the conveyor drive and the PCB presence sensor.
The counter increases its value if, at the beginning of the conveyor movement, there is a PCB on it.
When the set value is reached, a buzzer sounds and display backlight on.

The board presence and conveyor movement sensors operate at a low signal level.

Additionally:
- you can connect the screen via I2C channel
- you can enable the status log on the serial port
- you can select piezo or buzzer from relay

## Hardware

- Arduino Nano (ATmega328P)
- LCD 1602A
- Relay module (1 chanel)
- Optocoupler (2 chanels)
- Button