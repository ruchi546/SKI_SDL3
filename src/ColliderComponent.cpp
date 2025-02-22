#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() : rect{ 0, 0, 0, 0 } {}

ColliderComponent::~ColliderComponent() {}

void ColliderComponent::update(float deltaTime) {
}

void ColliderComponent::render(SDL_Renderer* renderer) {
}

void ColliderComponent::setRect(const SDL_FRect& rect) {
    this->rect = rect;
}

SDL_FRect ColliderComponent::getRect() const {
    return rect;
}

bool ColliderComponent::checkCollision(const SDL_Rect& otherRect) const {
    SDL_Rect colliderRect = { (int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h };
    return SDL_HasRectIntersection(&colliderRect, &otherRect);
}
