#include "MusicActor.h"

MusicActor::MusicActor(SDL_Renderer* renderer, const std::string& musicPath) {
    audio = std::make_shared<AudioComponent>();
    addComponent(audio);
    audio->loadSound(musicPath, "background");
}

MusicActor::~MusicActor() {
}

void MusicActor::playMusic(bool loop) {
    audio->playSound("background", loop);
}

void MusicActor::stopMusic() {
    audio->stopSound("background");
}