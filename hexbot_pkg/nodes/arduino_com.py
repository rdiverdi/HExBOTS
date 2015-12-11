#!/usr/bin/env python

import serial
import time

data = [1, 2, 3, 4, 5, 6]

ser = serial.Serial('/dev/ttyUSB0')

for num in data:
	ser.write(str(num))
	ser.write('N')
ser.write('E')

last = False
while True:
	response = ''
	while ser.inWaiting() > 0:
		response += ser.read()
		time.sleep(.01)
		last = True
	if last:
		print response
		response = ''
	last = False
