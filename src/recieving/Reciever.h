#include <alsa/asoundlib.h>
#include <iostream>
#include <unistd.h>
#include <thread>
//#include<bits/stdc++.h>


#define BUFFER_LEN 256
#define TONE_TIMER 75000

void audioAnalysis(int rc, snd_pcm_t* handle, short buffer[256]);
void micCapture(int rc, snd_pcm_t* handle, short buffer[256]);

void endPeak(short buffer[256], int waitus, bool* b);