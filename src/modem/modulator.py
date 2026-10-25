from time import sleep           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
 
GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering

"""
Recieve sound over the sound sensor
DATA:
- INPUT_PIN: The GPIO pin the input is coming in to

FUNCTIONALITY:
- listen: Reads GPIO_IN and returns True if pin is high
- read: Reads GPIO_IN every 0.075 seconds and returns the result as a byte string. Read until 4 null bytes.
"""
class modulator:
    def __init__(self):
        self.INPUT_PIN = 4
        GPIO.setup(INPUT_PIN, GPIO.IN)

    # Read GPIO_IN and return True if pin is high
    def listen(self):
        return True if GPIO.input(INPUT_PIN) == True else False

    # Read GPIO_IN every 0.075s. Return the results of each read as a btye string
    # Continue until 4 null bytes.
    def read(self):
        bitArray = []
        nullCounter = 0
        while nullCounter < 32:
            sample = GPIO.input(INPUT_PIN)
            if sample == True:
                bitArray.append("1")
                nullCounter = 0
            else:
                bitArray.append("0")
                nullCounter += 1
        # Convert bit array to byte string
