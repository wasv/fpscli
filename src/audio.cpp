#include "audio.h"
#include <sndfile.h>
#ifdef WITH_AUDIO

#include <cmath>

using namespace BitBorn;

static int audio_callback(const void *input, void *output, unsigned long frameCount,
                          const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    return ((Audio *)userData)->callback(input, output, frameCount, timeInfo, statusFlags);
}

int Audio::callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags) {
    float *out = (float *)output;
    unsigned int num_read;
    (void)input; /* Prevent unused variable warning. */

    num_read = sf_read_float(audio, out, frameCount);

    if(num_read < frameCount ) {
        sf_seek(audio, 0, SF_SEEK_SET);
        sf_read_float(audio, out+num_read, frameCount - num_read);
    }

    return paContinue;
}

Audio::Audio() {
    PaError err;

    audio = sf_open("sound/bg.wav", SFM_READ, &info);
    if (audio == NULL) {
        return;
    }
    /* Initialize library before making any other calls. */
    err = Pa_Initialize();
    if (err != paNoError) {
        return;
    }

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream(&stream, 0,       /* no input channels */
                               1,                /* mono output */
                               paFloat32,        /* 32 bit floating point output */
                               SAMPLE_RATE, 256, /* frames per buffer */
                               &audio_callback, this);
    if (err != paNoError) {
        return;
    }

    avail = true;
}

bool Audio::available() { return avail; }

bool Audio::start() { return Pa_StartStream(stream) == paNoError; }

bool Audio::stop() { return Pa_StopStream(stream) == paNoError; }

Audio::~Audio() {
    Pa_CloseStream(stream);
    Pa_Terminate();
}
#endif // WITH_AUDIO
