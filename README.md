# RPI-Pico-Test

This is a just me teating the RPI Pico with PlatformIO.

Usage
With a serial monitor send a 32bit binnary message formated as so.
XXXXXYYYZZZZZZZZ

X being the pin
Y being the operation
Z being the value (some operations)

current operations are 0 for digitalWrite

1 for digitalRead

2 for pin mode (value 0 for input, value 1 for output)

3 for analogRead

4 for analogWrite