import time
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
 
GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering

"""
Recieve sound over the sound sensor
DATA:
- INPUT_PIN: The GPIO pin the input is coming in to

FUNCTIONALITY:
- listen: Reads GPIO_IN and returns True if pin is high
- receive: Reads GPIO_IN every 0.075 seconds and returns the result as a byte string. Read until 4 null bytes.
"""
class modulator:
    def __init__(self):
        self.INPUT_PIN = 4
        GPIO.setup(self.INPUT_PIN, GPIO.IN)

    # Read GPIO_IN and return True if pin is high
    def listen(self):
        return True if GPIO.input(self.INPUT_PIN) == True else False

    # Read GPIO_IN every 0.075s. Return the results of each read as a btye string
    # Continue until 4 null bytes.
    def receive(self):
        byteArray = []
        nullCounter = 0
        while nullCounter < 4:
            byteValue = 0 
            nullCounter += 1
            for i in range(8):
                time.sleep(0.075)
                sample = GPIO.input(self.INPUT_PIN)
                if sample == True:
                    byteValue += 1 << i
                    nullCounter = 0
            byteArray.append(byteValue)

        return bytes(byteArray)

def __main__():
    m = modulator()
    m.read()

if __name__ == "__main__":
    __main__()
