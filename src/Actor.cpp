#include "Actor.h"
#include "Component.h"

Actor::Actor() {}

Actor::~Actor() {}

void Actor::update(float deltaTime) {
    for (auto& component : components) {
        component->update(deltaTime);
    }
}

void Actor::render(SDL_Renderer* renderer) {
    for (auto& component : components) {
        component->render(renderer);
    }
}

void Actor::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

template <typename T>
T* Actor::getComponent() {
    for (auto& component : components) {
        if (auto castedComponent = std::dynamic_pointer_cast<T>(component)) {
            return castedComponent.get();
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Component>>& Actor::getComponents() const {
    return components;
}