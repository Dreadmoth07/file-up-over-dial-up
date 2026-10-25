
from time import sleep           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
 
GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering
INPUT_PIN = 4           # Sets our input pin, in this example I'm connecting our button to pin 4. Pin 0 is the SDA pin so I avoid using it for sensors/buttons
GPIO.setup(INPUT_PIN, GPIO.IN)           # Set our input pin to be an input

OUTPUT_PIN = 17
GPIO.setup(OUTPUT_PIN, GPIO.OUT) # Start a loop that never ends

def read():
    last2 = False
    last = False
    while True: 
        current = GPIO.input(INPUT_PIN)
        if ((current == True) & (last == True) & (last2 == True)): # Physically read the pin now        	       	
            print('3.3')
        else:
            print('0')
            last2 = last
            last = current
            sleep(0.05)           # Sleep for a full second before restarting our loop


def write():
    while True:
        input() # Stall until user presses enter
        GPIO.output(OUTPUT_PIN, True)
        sleep(1)
        GPIO.output(OUTPUT_PIN, False)

def main():
    choice = input()
    if choice == "r":
        read()
    if choice == "w":
        write()

main()
