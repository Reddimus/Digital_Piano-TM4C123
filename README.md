# Music Box for TM4C123GH6PM

## Files

- `MusicBox.cpp`: Main application logic.
- `Music.cpp/h`: Handles music playback.
- `SysTick.cpp/h`: Manages system timing.
- `Switch.cpp`: Handles button switches (Note: `Switch.h` is missing).
- `tm4c123gh6pm.h`: Microcontroller-specific header.

## Hardware and GPIO Ports

### GPIO_PORTA Table

| Pin  | Usage                     | Component          |
|------|---------------------------|--------------------|
| PA3  | Speaker Buzzer            | RuiLing PC-BUZZER-2|

### GPIO_PORTF Table

| Pin  | Usage                     |
|------|---------------------------|
| PF4  | Onboard Switch 1          |
| PF0  | Onboard Switch 2          |


## How to Run

1. Compile all `.cpp` files.
2. Flash onto your TM4C123GH6PM microcontroller.
    - You can use the provided Keil uVision project folder.
3. Press onboard SW1 to start the music box. Press SW2 to shuffle the song.