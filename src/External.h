#ifndef EXTERNAL_H_
#define EXTERNAL_H_
#include <raylib.h>

struct anySound{
    Sound xsound,ysound;
    Music mainMenuM,raceM,runM;
};

class MusicManager {
    public:
    Music* currentTrack = nullptr;
    float volume = 1.0f;

    MusicManager(Music* track);
    void Update();
    void Play(Music* track);
};

void loadMyAudio(anySound& s);
void unloadMyAudio(anySound& s);

#endif 