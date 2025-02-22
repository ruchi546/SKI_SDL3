#ifndef MUSIC_ACTOR_H
#define MUSIC_ACTOR_H

#include "Actor.h"
#include "AudioComponent.h"
#include <string>

class MusicActor : public Actor {
public:
    MusicActor(SDL_Renderer* renderer, const std::string& musicPath);
    virtual ~MusicActor();

    void playMusic(bool loop = true);
    void stopMusic();

private:
    std::shared_ptr<AudioComponent> audio;
};

#endif // MUSIC_ACTOR_H
