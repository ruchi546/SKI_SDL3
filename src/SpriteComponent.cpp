#include "SpriteComponent.h"
#include <SDL3/SDL_log.h>

SpriteComponent::SpriteComponent() : rect{ 0, 0, 0, 0 } {}

SpriteComponent::~SpriteComponent() {}

bool SpriteComponent::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    bool success = texture.loadFromFile(renderer, path);
    if (!success) {
        SDL_Log("Failed to load texture: %s", path.c_str());
    }
    return success;
}

void SpriteComponent::render(SDL_Renderer* renderer) {
    texture.render(renderer, rect.x, rect.y, rect.w, rect.h);
}

void SpriteComponent::update(float deltaTime) {
}

void SpriteComponent::setRect(const SDL_FRect& rect) {
    this->rect = rect;
}

SDL_FRect SpriteComponent::getRect() const {
    return rect;
}
