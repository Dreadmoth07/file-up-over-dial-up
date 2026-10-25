#include "Reciever.h"

int reciever(){
    long loops;
    int rc; // read control
    int size;
    snd_pcm_t *handle; // handle for the capture
    snd_pcm_hw_params_t *params; // hardware parameters
    unsigned int val; // sample rate
    int dir;
    snd_pcm_uframes_t frames; // number of frames per period
    
    short buffer[BUFFER_LEN]; // buffer

    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);

    if(rc<0){
        std::cerr << "Microphone not opened" << snd_strerror(rc);
        return -1;
    }

    // Allocate a hardware parameters object
    snd_pcm_hw_params_alloca(&params);
    // Fill it with default values
    snd_pcm_hw_params_any(handle, params);
    // Interleaved mode - makes it so that audio channels are provided in a single sequence as opposed to seperately
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    // Signed 16-bit (2-byte) little-endian format
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    // Mono channel (1 channel)
    snd_pcm_hw_params_set_channels(handle, params, 1);
    // Sampling rate: 44100 bits/second
    val = 44100;
    snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
    // Set a single "period"'s size to 32 frames
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

    // Write the parameters to the driver
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        std::cerr << "Unable to set hw parameters: " << snd_strerror(rc) << std::endl;
        return 1;
    }

    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    size = frames * 2; // 2 bytes per sample so gotta double size

    std::cout << "Listening??" << std::endl;


    std::thread w(micCapture, rc, handle, buffer);
    std::thread r(audioAnalysis, rc, handle, buffer);
    r.join();
    w.join();

}

void audioAnalysis(int rc, snd_pcm_t* handle, short buffer[BUFFER_LEN]){
    FILE *fptr;
    char fileName[] = "binary";
    fptr = fopen(fileName, "w");
    if (fptr == NULL)  printf("Failed to create file\n");

    bool peaked = false;
    int i = 0;
    while(true){
        if(abs((float)(buffer[0]) / 32767) > 0.95 || abs((float)(buffer[BUFFER_LEN / 2]) / 32767) > 0.95){
            usleep(TONE_TIMER);
            peaked = true;
        }

        if(peaked){
            std::cout << "1";
            fputc('1', fptr);
            peaked = false;
        }
        else{
            std::cout << "0";
            fputc('0', fptr);
            usleep(TONE_TIMER);
        }

        i++;
        if(i>=8){ // flush buffer every byte
            std::cout << std::endl;
            i=0;
            fflush(fptr);
        }
    }

}

void micCapture(int rc, snd_pcm_t* handle, short buffer[BUFFER_LEN]){
    while(true){
            if ((rc = snd_pcm_readi(handle, buffer, 2)) != 2) {
                fprintf (stderr, "read from audio interface failed (%s)\n",
                        snd_strerror (rc));
            }
        }
}


void endPeak(short buffer[BUFFER_LEN], int waitus, bool* b){
    std::cout << "waiting" << std::endl;
    usleep(waitus);
    *b = false;
    std::cout << "done waiting" << std::endl;
}