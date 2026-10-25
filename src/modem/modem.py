import demodulator
import modulator
import lineTransfer

# Create demodulator and lineTransfer
with lineTransfer.lineTransferObject("PS2", True) as l:
    demod = demodulator.demodulator()
    mod = modulator.modulator()

    while True:
        # Check socket stream
        if l.listen() == True:
            # If data, read it and demodulate it
            print("Reading socket!")
            data = l.receive()
            demod.demodulate(data)
        # Check modulator stream
        if mod.listen() == True:
            # If high, modulate signal and send it over socket
            print("Reading modulator!")
            data = mod.receive()
            l.send(data)
   # # Keep listening until data found
   # while True:
   #     choice = input("Read or write?")
   #     if choice == "r":
   #         for i in range(999999):
   #             if l.listen() == True:
   #                 # Output data
   #                 data = l.receive()
   #                 print(type(data))
   #                 demod.demodulate(data)
   #     else:
   #         data = input("Enter data to send: ")
   #         l.send(data.encode("UTF-8"))
