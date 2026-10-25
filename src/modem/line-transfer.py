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
    # INPUTS: name of device (XBOX or PS2), bool is device establishing the connection? If so, has to listen and accept the other one
    def __init__(self, device, establisher):
        HOST = "192.168.137.74" if device == "XBOX" else "192.168.137.1"
        OTHER_HOST = "192.168.137.1" if device == "XBOX" else "192.168.137.74"
        PORT = 50007              # Arbitrary non-privileged port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Created socket on {HOST}")
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.s.bind((HOST, PORT))
        print("Bound socket")
        if establisher:
            print("Attempting to accept other device")
            self.s.listen(1)
            self.conn, addr = self.s.accept()
            print('Connected by', addr)
        else:
            print("Attempting to connect to other device (establisher)")
            self.s.connect((OTHER_HOST, PORT))
            print("Connected!")
            self.conn = None

    # Send data across ethernet cable
    # INPUTS: int[] packet of bits to send
    # OUTPUT: bits places on ethernet cable over time
    def send(self, bytes):
        self.conn.sendall(bytes) if self.conn != None else self.s.sendall(bytes)
        pass

    # Recieve and return data sent across ethernet cable
    # INPUTS: bit stream from ethernet cable
    # RETURNS: int[] bits received
    def receive(self):
        while True:
            data = self.conn.recv(1024) if self.conn != None else self.s.recv(1024)
            if not data: continue
            print(data)
            return

    # Listen to ethernet cable for a short while, to see if data will be sent 
    # INPUTS: bit stream from ethernet cable
    # Returns: True if ethernet cable is sending data, False if not 
    def listen(self):
        try:
            data = self.conn.recv(1024, socket.MSG_PEEK | socket.MSG_DONTWAIT) if self.conn != None else self.s.recv(1024, socket.MSG_PEEK | socket.MSG_DONTWAIT)
            return True if data else False
        except BlockingIOError: # No data to read, so return false
            return False

    def main(self):
        while True:
            mode = input("Read or write?")
            if mode == "r":
                print("Reading!")
                for i in range(999999):
                    listenedData = self.listen()
                    if listenedData == True:
                        data = self.receive()
                        if data != None: print(data)
                print("Done reading!")
            else:
                print("Writing!")
                self.send(input("Enter message: ").encode())
                print("Done writing!")


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
def __main__():
    device = input("Is this XBOX or PS2?")
    if input("Press enter for receiver") != "":
        with lineTransferObject(device, True) as l:
            l.main()
    else:
        with lineTransferObject(device, False) as l:
            l.main()

if __name__ == "__main__":
    __main__()
