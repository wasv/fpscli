#pragma once

#ifndef WITH_AUDIO
#warning Audio disabled
#else // WITH_AUDIO

#include <array>
#include <portaudio.h>
#include <sndfile.h>

#define PI 3.14159265f

namespace BitBorn {
class Audio {
    const int SAMPLE_RATE{44100};

    bool avail = false;
    PaStream *stream;
    SNDFILE *audio;
    SF_INFO info;

  public:
    enum State { Saw, Sine, Square };
    enum Event { Collide, Fire, Die };

    Audio();
    bool start();
    bool stop();
    bool available();

    ~Audio();

    int callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                 PaStreamCallbackFlags statusFlags);
};
} // namespace BitBorn

#endif // WITH_AUDIO
