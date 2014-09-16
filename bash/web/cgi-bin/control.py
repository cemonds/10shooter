#!/usr/bin/python -u

from time import sleep
import serial
import os

print("Content-Type: text/html")
print("")
print("<html>")
print("<body>")
print("Hallo Cocktail")
command = os.environ['QUERY_STRING'].replace('command=','')
serial_port = serial.Serial('/dev/ttyS0', 115200, timeout=1)
serial_port.write(command)
finished = False
counter = 0
while not finished:
	line = serial_port.readline()
	sleep(.1)
	if line == "Mixing complete":
		finished = True
	elif counter == 1000:
		print("Mixing cancelled")
		finished = True
	elif line != '':
		print("<p>%s</p>" % line)
	counter += 1
       
serial_port.close()

print("</body>")
print("</html>")
