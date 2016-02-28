# Teensy-Arcade-Controller
Teensy 2.0 C script for an arcade controller

# Boutons
PORTF0-1    UP-DOWN
PORTF4-5    LEFT-RIGHT
PORTB0-1    BTN1-2
PORTB3-6    BTN3-6
PORTD0      Player one
PORTD2      NewCoin

# Install
1. Install [Teensy Loader](https://www.pjrc.com/teensy/loader_linux.html)
2. Edit the Makefile for your teensy
```
#MCU = at90usb162       # Teensy 1.0
MCU = atmega32u4        # Teensy 2.0
#MCU = at90usb646       # Teensy++ 1.0
#MCU = at90usb1286      # Teensy++ 2.0
```
see https://www.pjrc.com/teensy/gcc.html for teensy 3.0
3. Compile ```make```
4. Transfer main.elf on your Teensy
