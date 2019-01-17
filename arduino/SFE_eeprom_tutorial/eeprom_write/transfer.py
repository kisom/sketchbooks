#!/usr/bin/env python3

import serial

with open('ghostbusters.txt') as source:
    data = source.read()

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=19200)
ser.write(data)
