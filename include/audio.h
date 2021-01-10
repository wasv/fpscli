#ifndef __AUDIO_H_
#define __AUDIO_H_

#ifndef WITH_AUDIO
#warning Audio disabled
#else // WITH_AUDIO

#include <array>
#include <portaudio.h>

#define PI 3.14159265f

namespace BitBorn {
class Audio {
    const int SAMPLE_RATE{44100};
    float phase{0.0f};

    PaStream *stream;

  public:
    enum State { Saw, Sine, Square };
    enum Event { Collide, Fire, Die };

    bool init();
    bool start();
    bool stop();

    ~Audio();

    int callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                 PaStreamCallbackFlags statusFlags);
};
} // namespace BitBorn

#endif // WITH_AUDIO

#endif // __AUDIO_H_