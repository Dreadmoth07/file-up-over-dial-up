import demodulator
import lineTransfer

# Create demodulator and lineTransfer
with lineTransfer.lineTransferObject("PS2", True) as l:
    demod = demodulator.demodulator()
    # Keep listening until data found
    while True:
        if l.listen() == True:
            # Output data
            data = l.receive()
            print(type(data))
            demod.demodulate(data)
