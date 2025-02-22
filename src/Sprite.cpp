#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath)
    : renderer(renderer), texture(nullptr) {
    loadFromFile(filePath);
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

bool Sprite::loadFromFile(const std::string& filePath) {
    texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        return false;
    }
    return true;
}

void Sprite::render(float x, float y, float width, float height) {

	const SDL_FRect destRect = { x, y, width, height };
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);
}