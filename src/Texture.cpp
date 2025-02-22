#include "Texture.h"

Texture::Texture() : texture(nullptr), surface(nullptr), width(0), height(0) {}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path) {
    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        SDL_Log("Failed to load image %s:", path.c_str());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        SDL_DestroySurface(loadedSurface);
        return false;
    }

    surface = loadedSurface;
    width = surface->w;
    height = surface->h;

    return true;
}

float Texture::getWidth() {
    return static_cast<float>(width);
}

float Texture::getHeight() {
    return static_cast<float>(height);
}

void Texture::render(SDL_Renderer* renderer, float x, float y, float w, float h) {
    SDL_FRect renderQuad = { x, y, w, h };
    SDL_RenderTexture(renderer, texture, nullptr, &renderQuad);
}

void Texture::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (surface) {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }
    width = height = 0;
}
