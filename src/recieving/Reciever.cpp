#include "Reciever.h"
#include <alsa/asoundlib.h>
#include <ostream>

int main(int argc, char **argv){
    long loops;
    int rc; // read control
    int size;
    snd_pcm_t *handle; // handle for the capture
    snd_pcm_hw_params_t *params; // hardware parameters
    unsigned int val; // sample rate
    int dir;
    snd_pcm_uframes_t frames; // number of frames per period
    
    void* buffer[256]; // buffer

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
    // Signed 16-bit little-endian format
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
    size = frames * 2; // 2 bytes per sample so obv gotta double size

    std::cout << "Listening??" << std::endl;

    while(true){
        rc = snd_pcm_readi(handle, buffer, size);
        if (rc == -EPIPE) {
            // End Pipe - Overrun occurred
            std::cerr << "Overrun occurred!" << std::endl;
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            std::cerr << "Error from read: " << snd_strerror(rc) << std::endl;
        } else if (rc != (int)frames) {
            // short reads are reads where there is not sufficient space in the buffer.
            std::cerr << "Short read, read " << rc << " frames" << std::endl;
        }
    }

}