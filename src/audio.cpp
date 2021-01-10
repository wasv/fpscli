#include "audio.h"
#ifdef WITH_AUDIO

#include <portaudio.h>
#include <cmath>

using namespace BitBorn;

static int audio_callback(const void *input, void *output, unsigned long frameCount,
                          const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    return ((Audio *)userData)->callback(input, output, frameCount, timeInfo, statusFlags);
}

int Audio::callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags) {
    float *out = (float *)output;
    unsigned int i;
    (void)input; /* Prevent unused variable warning. */

    for (i = 0; i < frameCount; i++) {
        phase += 1.0f/SAMPLE_RATE;
        if(phase > 1.0f)
            phase = 0.0f;
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        float left = 0.5f * cos(440.0f * phase * (2 * PI));
        float right = 0.5f * cos(480.0f * phase * (2 * PI));

        *out++ = left; /* left */
        *out++ = right; /* right */
    }
    return paContinue;
}

bool Audio::init() {
    PaError err;

    /* Initialize library before making any other calls. */
    err = Pa_Initialize();
    if (err != paNoError) {
        return false;
    }

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream(&stream, 0,       /* no input channels */
                               2,                /* stereo output */
                               paFloat32,        /* 32 bit floating point output */
                               SAMPLE_RATE, 256, /* frames per buffer */
                               &audio_callback, this);
    if (err != paNoError) {
        return false;
    }

    return true;
}

bool Audio::start() { return Pa_StartStream(stream) == paNoError; }

bool Audio::stop() { return Pa_StopStream(stream) == paNoError; }

Audio::~Audio() {
    Pa_CloseStream(stream);
    Pa_Terminate();
}
#endif // WITH_AUDIO
