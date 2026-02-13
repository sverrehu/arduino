#!/bin/bash

PROG_BASENAME=program
DEVICE=/dev/cu.usbmodem101
MCU=atmega328p
export PATH=$HOME/tmp/avr8-gnu-toolchain-darwin_universal/bin:$PATH

avr-gcc -Os -mmcu="${MCU}" -c "${PROG_BASENAME}.c"
avr-gcc -mmcu="${MCU}" -o "${PROG_BASENAME}.elf" "${PROG_BASENAME}.o"
avr-objcopy -O ihex ${PROG_BASENAME}.elf "${PROG_BASENAME}.hex"

rm "${PROG_BASENAME}.o"
rm "${PROG_BASENAME}.elf"

avrdude -c arduino -p "${MCU}" -P "${DEVICE}" -U flash:w:"${PROG_BASENAME}.hex"

rm "${PROG_BASENAME}.hex"
