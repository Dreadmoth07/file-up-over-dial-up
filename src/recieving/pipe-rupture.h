#include <alsa/asoundlib.h>
#include <iostream>
#include <unistd.h>
#include <thread>

void endPeak(short buffer[256], int waitus, bool* b);