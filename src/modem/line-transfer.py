import socket
"""
Transfer data over ethernet cables

Object lineTransferObject 
FUNCTIONALITY:
- Send data
- Recieve data
- Listen for data
"""

class lineTransferObject():
    # INPUTS: str ip address the device (XBOX or PS2)
    def __init__(self, addr):
        HOST = addr 
        PORT = 50007              # Arbitrary non-privileged port
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Created socket")
        s.bind((HOST, PORT))
        print("Bound socket")
        s.close()
        print("Socket closed")
        print("Bye!")

    # Send data across ethernet cable
    # INPUTS: int[] packet of bits to send
    # OUTPUT: bits places on ethernet cable over time
    def send(packet):
         
        pass

    # Recieve and return data sent across ethernet cable
    # INPUTS: bit stream from ethernet cable
    # RETURNS: int[] bits recieved
    def recieve():
        pass

    # Listen to ethernet cable for a short while, to see if data will be sent 
    # INPUTS: bit stream from ethernet cable
    # Returns: True if ethernet cable is sending data, False if not 
    def listen():
        pass

l = lineTransferObject("localhost")
