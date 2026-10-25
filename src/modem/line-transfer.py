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
    # INPUTS: bool is device establishing the connection? If so, has to listen and accept the other one 
    def __init__(self, establisher):
        HOST = "0.0.0.0" # Binds to all IPv4 interfaces the pi's connected to - so the ethernet
        PORT = 50007              # Arbitrary non-privileged port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Created socket on {HOST}")
        self.s.bind((HOST, PORT))
        print("Bound socket")
        if establisher:
            print("Attempting to accept other device")
            self.s.listen(1)
            conn, addr = self.s.accept()
            print('Connected by', addr)
        else:
            print("Attempting to connect to other device (establisher)")
            self.s.connect((HOST, PORT))

    # Send data across ethernet cable
    # INPUTS: int[] packet of bits to send
    # OUTPUT: bits places on ethernet cable over time
    def send():
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

    def close(self):
        if self.s is not None:
            self.s.close()
            self.s = None

    # Enter and Exit allow a "with" statement to be used - allowing the socket to be closed in an exception
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.close()
        print("Socket closed!")
        return False

# The first device to be executed is the establisher.
# It establishes the connection, and accepts the other device's connect() request
if input() != "":
    with lineTransferObject(True) as l:
        pass
else:
    with lineTransferObject(False) as l:
        pass
