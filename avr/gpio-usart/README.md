# Programming Arduino's AVR Microcontroller in C

A friend got this school assignment, and since I was out of hobby
projects I thought it would be fun to give it a go:

> _Write A C program for an AVR microcontroller that uses UART (Universal
> Asynchronous Receiver-Transmitter) to: (i) sen a message "Button
> Pressed!" when a button connected to a digital pin is pressed and (ii)
> receive a command ("ON" or "OFF") from the serial terminal to turn a
> LED on or off._

My Arduino Uno Rev 3 happens to have both an AVR and UART, and writing
such a program using the friendly Arduino C libraries would be quite
easy. The task, however, is to use generic AVR libraries which are
much more low-level. Great fun!

## Setup

Download and install:

* [GCC Compilers for
  AVR](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)
  for compiling the program
* [AVRDUDE](https://github.com/avrdudes/avrdude) for transfering the
  program to the AVR microcontroller

## Relevant Documentation

* [AVR Atmega328P UART](http://www.rjhcoding.com/avrc-uart.php)
* [A000066-full-pinout.pdf](https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf)
* [AVR 8-Bit Microcontroller](https://ww1.microchip.com/downloads/en/DeviceDoc/en590320.pdf)

## Arduino Setup

The Arduino is set up as outlined in the [Arduino – Turn LED ON and
OFF With
Button](https://roboticsbackend.com/arduino-turn-led-on-and-off-with-button/)
exercise. I tested the wiring using [a simple
program](test-arduino-wiring.c) written in the higher-level C of
[Arduino IDE](https://www.arduino.cc/en/software/), and I'm glad I
did, because my initial wiring was wrong.

## Implementation Notes

This implementation uses a naive approach with an active waiting loop,
continously polling for data from the USART and the button. This is
not energy efficient. A real-life implementation would register
interrupt handlers for the two input sources, and spend most of the
time sleeping.
