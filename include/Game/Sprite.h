#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <string>

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filePath);
    ~Sprite();

    void render(float x, float y, float width, float height);

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    bool loadFromFile(const std::string& filePath);
};

#endif // SPRITE_H