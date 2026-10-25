from time import sleep           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO

"""
Send data over buzzer
DATA:
- OUTPUT_PIN: The GPIO Pin the output is coming out of

FUNCTIONALITY:
- demodulate(byte[] byte): Plays a stream of bytes through the buzzer, with each bit lasting 0.15s
"""
class demodulator:
    def __init__(self):
        GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering

        self.OUTPUT_PIN = 17
        GPIO.setup(self.OUTPUT_PIN, GPIO.OUT) # Start a loop that never ends

    # Plays the input array of bytes over the buzzer. Each bit lasts 0.15s
    def demodulate(self, byteArray):
        for byte in byteArray:
            byteAsInt = int.from_bytes(byte, byteorder="big")
            byte = bin(byteAsInt)[2:]
            byte = "0"*(8-len(byte)) + byte # Add leading zeros
            print(byte)
            for bit in byte:
                print(bit)
                if bit == "1":
                    self._write_high()
                elif bit == "0":
                    self._write_low()
        return

    def _write_high(self):
        GPIO.output(self.OUTPUT_PIN, True)
        sleep(0.15)
        GPIO.output(self.OUTPUT_PIN, False)

    def _write_low(self):
        GPIO.output(self.OUTPUT_PIN, False)
        sleep(0.15)

d = demodulator()
#d._write_low()
#while True:
#    d._write_high()
d.demodulate([int.to_bytes(45)])
