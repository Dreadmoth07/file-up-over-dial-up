#include "Reciever.h"
#include <cstdlib>
#include <unistd.h>

int main(int argc, char **argv){
    long loops;
    int rc; // read control
    int size;
    snd_pcm_t *handle; // handle for the capture
    snd_pcm_hw_params_t *params; // hardware parameters
    unsigned int val; // sample rate
    int dir;
    snd_pcm_uframes_t frames; // number of frames per period
    
    short buffer[256]; // buffer

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
    
    bool* peaked = new bool;
    *peaked = false;

    while(true){
        if ((rc = snd_pcm_readi(handle, buffer, 2)) != 2) {
            fprintf (stderr, "read from audio interface failed (%s)\n",
                    snd_strerror (rc));
            
        }
        else if(abs((float)(buffer[0]) / 32767) > 1 && !(*peaked)){
            std::cout << "peaked" << std::endl;
            *peaked = true;
            pid_t p = fork();
            if(p == 0)
                endPeak(buffer, 500000, peaked);
        }
    }
}


void endPeak(short buffer[256], int waitus, bool* b){
    std::cout << "waiting" << std::endl;
    usleep(waitus);
    *b = false;
    std::cout << "done waiting" << std::endl;
}