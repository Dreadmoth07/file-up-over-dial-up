import demodulator
import lineTransfer

# Create demodulator and lineTransfer
with lineTransfer.lineTransferObject("PS2", True) as l:
    demod = demodulator.demodulator()
    # Keep listening until data found
    while True:
        choice = input("Read or write?")
        if choice == "r":
            for i in range(999999):
                if l.listen() == True:
                    # Output data
                    data = l.receive()
                    print(type(data))
                    demod.demodulate(data)
        else:
            data = input("Enter data to send: ")
            l.send(data.encode("UTF-8"))
