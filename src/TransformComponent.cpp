#include "TransformComponent.h"

TransformComponent::TransformComponent()
    : position{ 0, 0 }, rotation(0), scale{ 1, 1 } {
}

TransformComponent::~TransformComponent() {}

void TransformComponent::update(float deltaTime) {
}

void TransformComponent::render(SDL_Renderer* renderer) {
}

void TransformComponent::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void TransformComponent::setRotation(float angle) {
    rotation = angle;
}

void TransformComponent::setScale(float scaleX, float scaleY) {
    scale.x = scaleX;
    scale.y = scaleY;
}

SDL_FPoint TransformComponent::getPosition() const {
    return position;
}

float TransformComponent::getRotation() const {
    return rotation;
}

SDL_FPoint TransformComponent::getScale() const {
    return scale;
}
