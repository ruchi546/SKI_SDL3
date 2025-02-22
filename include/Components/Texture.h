#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    void render(SDL_Renderer* renderer, float x, float y, float w, float h);
    float getWidth();
    float getHeight();
    void free();

private:
    SDL_Texture* texture;
    SDL_Surface* surface;
    int width, height;
};

#endif // TEXTURE_H