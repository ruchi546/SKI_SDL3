#ifndef AUDIO_COMPONENT_H
#define AUDIO_COMPONENT_H

#include "Component.h"
#include <SDL3/SDL.h>
#include <string>
#include <map>

class AudioComponent : public Component {
public:
    AudioComponent();
    virtual ~AudioComponent();

    bool loadSound(const std::string& filePath, const std::string& soundId);
    void playSound(const std::string& soundId, bool loop = false);
    void stopSound(const std::string& soundId);
    bool isSoundPlaying(const std::string& soundId);
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;

private:
    SDL_AudioDeviceID audioDevice;
    std::map<std::string, SDL_AudioStream*> audioStreams;
    std::map<std::string, Uint8*> wavDataMap;
    std::map<std::string, Uint32> wavDataLenMap;
    std::map<std::string, bool> loopMap;
};

#endif // AUDIO_COMPONENT_H
