# File-Up Over Dial-Up
File transfer over a reverse-engineered form of dial-up.
Made during HackNotts26, a 25hr hackathon hosted at The University Of Nottingham.

Device A wants to get a file from Device B.

Device A generates a `get` query and converts it into binary, after which it outputs this as a set of beeps and silences. These are picked up by a GPIO audio sensor on a Raspberry Pi (acting as a modem), which then converts the voltage to another digital form for transfer over an ethernet cable to another Pi.

Once it is recieved by the second Pi, it is re-output in auditory form by a buzzer connected via GPIO. Device B then listens to this audio via its own microphone, converts it back into Ascii, then processes the request. The file is sent back over the same way the request is.