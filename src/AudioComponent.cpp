#include "AudioComponent.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_audio.h>
#include <stdexcept>

AudioComponent::AudioComponent() : audioDevice(0) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("Failed to initialize audio: %s", SDL_GetError());
        throw std::runtime_error("Failed to initialize audio");
    }

    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audioDevice == 0) {
        SDL_Log("Failed to open audio device: %s", SDL_GetError());
        throw std::runtime_error("Failed to open audio device");
    }
}

AudioComponent::~AudioComponent() {
    for (auto& pair : wavDataMap) {
        SDL_free(pair.second);
    }
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool AudioComponent::loadSound(const std::string& filePath, const std::string& soundId) {
    SDL_AudioSpec spec;
    Uint8* wavData;
    Uint32 wavDataLen;

    if (SDL_LoadWAV(filePath.c_str(), &spec, &wavData, &wavDataLen) == 0) {
        SDL_Log("Failed to load WAV file: %s", SDL_GetError());
        return false;
    }

    SDL_AudioStream* stream = SDL_CreateAudioStream(&spec, nullptr);
    if (stream == nullptr) {
        SDL_Log("Failed to create audio stream: %s", SDL_GetError());
        SDL_free(wavData);
        return false;
    }

    if (!SDL_BindAudioStream(audioDevice, stream)) {
        SDL_Log("Failed to bind audio stream: %s", SDL_GetError());
        SDL_free(wavData);
        SDL_DestroyAudioStream(stream);
        return false;
    }

    audioStreams[soundId] = stream;
    wavDataMap[soundId] = wavData;
    wavDataLenMap[soundId] = wavDataLen;
    loopMap[soundId] = false;

    return true;
}

void AudioComponent::playSound(const std::string& soundId, bool loop) {
    if (audioStreams.find(soundId) != audioStreams.end()) {
        SDL_AudioStream* stream = audioStreams[soundId];
        Uint8* wavData = wavDataMap[soundId];
        Uint32 wavDataLen = wavDataLenMap[soundId];

        loopMap[soundId] = loop;
        SDL_PutAudioStreamData(stream, wavData, (int)wavDataLen);
    }
}

void AudioComponent::stopSound(const std::string& soundId) {
    if (audioStreams.find(soundId) != audioStreams.end()) {
        SDL_AudioStream* stream = audioStreams[soundId];
        SDL_ClearAudioStream(stream);
    }
}

bool AudioComponent::isSoundPlaying(const std::string& soundId) {
    if (audioStreams.find(soundId) != audioStreams.end()) {
        SDL_AudioStream* stream = audioStreams[soundId];
        return SDL_GetAudioStreamAvailable(stream) > 0;
    }
    return false;
}

void AudioComponent::update(float deltaTime) {
    for (auto& pair : audioStreams) {
        SDL_AudioStream* stream = pair.second;
        if (SDL_GetAudioStreamAvailable(stream) == 0) {
            if (loopMap[pair.first]) {
                Uint8* wavData = wavDataMap[pair.first];
                Uint32 wavDataLen = wavDataLenMap[pair.first];
                SDL_PutAudioStreamData(stream, wavData, (int)wavDataLen);
            }
        }
    }
}

void AudioComponent::render(SDL_Renderer* renderer) {
}
