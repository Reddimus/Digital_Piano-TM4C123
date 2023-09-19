# Music Box for TM4C123GH6PM

This project encompasses a digital piano powered by a TM4C123 MCU, integrating a speaker, amplifier, and DAC circuit. It bifurcates into two primary functionalities: a music box module that curates three melodies, managed via dual switches, and a digital piano module utilizing a 6-bit R/2R DAC with 4 tactile push buttons serving as piano keys. The underpinning embedded system is crafted in C++ with an object-oriented paradigm, centralizing the Sound class as the foundational parent, while the Music & Piano classes delineate the device's modes.

## Files

- `MusicBox.cpp`: Main application logic.
    - `Sound.cpp` / `Sound.h`: Sound **parent** class.
        - Contains notes, DAC, toneTab, and SysTick attributes.
        - Allows option to switch modes using switch 1.
        - `Piano.cpp` / `Piano.h`: Piano **child** class.
            - Piano mode (default)
            - Allows option to play individual piano keys C, D, E, F, G, A, B in piano mode.
            - Allows option to change octave in piano mode using switch 2.
        - `Music.cpp` / `Music.h`: Music **child** class.
            - Music box mode.
            - Contains songs list, current song played in music box mode.
            - Allows option to change song in music box mode using switch 2.
    - `ButtonLED.cpp` / `ButtonLED.h`: Button & LED class.
        - Contains underlying button actions; calls Sound, Music, and Piano classes to play notes, change modes, and change songs.
        - GPIO port D & F tm4c123gh6pm.h register addresses and bit masks.
    - `startup.s` functions compiled in `C`: 
        - Assembly language startup code for TM4C123GH6PM microcontroller containing the following functions:
            - `EnableInterrupts()`
            - `DisableInterrupts()`
            - `WaitForInterrupt()`
            - `GPIO_PORTF_Handler()`
            - `GPIO_PORTD_Handler()`
    - `tm4c123gh6pm.h`: TM4C123GH6PM microcontroller pre-defined register addresses and bit masks for GPIO ports, SysTick, and NVIC registers and interrupts.
    
    
        

## Hardware and GPIO Ports

### GPIO_PORTD Table

| Pin  | Usage                     | Component          |
|:----:|:-------------------------:|:------------------:|
| PD3  | Plays Piano key F         | Breadboard Button  |
| PD2  | Plays Piano key E         | Breadboard Button  |
| PD1  | Plays Piano key D         | Breadboard Button  |
| PD0  | Plays Piano key C         | Breadboard Button  |

### GPIO_PORTF Table

| Pin  | Usage                     |
|:----:|:-------------------------:|
| PF4  | Onboard Switch 1          |
| PF3  | Onboard LED 3             |
| PF2  | Onboard LED 2             |
| PF1  | Onboard LED 1             |
| PF0  | Onboard Switch 2          |

### GPIO_PORTB Table
| Pin  | Usage                     |
|:----:|:-------------------------:|
| PB5  | 6-bit R/2R DAC output     |
| PB4  | 6-bit R/2R DAC output     |
| PB3  | 6-bit R/2R DAC output     |
| PB2  | 6-bit R/2R DAC output     |
| PB1  | 6-bit R/2R DAC output     |
| PB0  | 6-bit R/2R DAC output     |

### Miscellaneous
| Pin  | Usage                     |
|:----:|:-------------------------:|
| GND  | Ground for breadboard     |
| VBUS | Power for amplifier       |

## How to Run

1. Create DAC circuit.
    - See `Digital_Piano_Schematic.pdf` for reference.
1. Compile all `.cpp` & `.h` files.
2. Flash onto your TM4C123GH6PM microcontroller.
    - You can use the provided Keil uVision project folder.
3. Play music!
    - Switch 1: Toggle between music box and piano modes.
    - Switch 2: 
        - Toggle between songs in **music box mode**.
        - Increase octave in **piano mode**. If octave is at max, it will reset to the lowest octave.
    - Piano Keys: Play notes in **piano mode**.
