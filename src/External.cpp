#include "External.h"

void loadMyAudio(anySound& s){
    s.xsound = LoadSound("assets/audio/x1n.mp3");
    s.ysound = LoadSound("assets/audio/x2n.mp3");
    s.mainMenuM = LoadMusicStream("assets/audio/mainmenum.mp3");
    s.raceM = LoadMusicStream("assets/audio/race.mp3");
    s.runM = LoadMusicStream("assets/audio/runrelaxn.mp3");
}

void unloadMyAudio(anySound& s){
    UnloadSound(s.xsound);
    UnloadSound(s.ysound);
    UnloadMusicStream(s.mainMenuM);
    UnloadMusicStream(s.raceM);
    UnloadMusicStream(s.runM);
}

MusicManager::MusicManager(Music* track){
    currentTrack = track;
    PlayMusicStream(*currentTrack); 
}

void MusicManager::Update(){
    if (currentTrack != nullptr) {
        UpdateMusicStream(*currentTrack);
    }
    SetMasterVolume(volume);
}
void MusicManager::Play(Music* track) {
    if (currentTrack != nullptr) StopMusicStream(*currentTrack);
    currentTrack = track;
    if (currentTrack != nullptr) {
        PlayMusicStream(*currentTrack);
        SetMusicVolume(*currentTrack, volume);
    }
}

