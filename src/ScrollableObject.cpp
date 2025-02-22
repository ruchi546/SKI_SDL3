#include "ScrollableObject.h"

ScrollableObject::ScrollableObject(GameManager* gameManager, float width, float height)
    : rect{ 0.0f, 0.0f, width, height }, speed(gameManager->getGameSpeed()), currentTexture(0) {
}

bool ScrollableObject::loadTextures(SDL_Renderer* renderer, const std::string& path1, const std::string& path2) {
    if (!texture01.loadFromFile(renderer, path1)) {
        return false;
    }
    if (!path2.empty() && !texture02.loadFromFile(renderer, path2)) {
        return false;
    }
    return true;
}

void ScrollableObject::randomTexture() {
    currentTexture = rand() % 2;
}

void ScrollableObject::update(float deltaTime, GameManager* gameManager) {
    speed = gameManager->getGameSpeed();
    rect.y -= speed * deltaTime;
    if (rect.y + rect.h < 0) {
        rect.y = 0;
    }
}

void ScrollableObject::render(SDL_Renderer* renderer) {
    if (currentTexture == 0) {
        texture01.render(renderer, rect.x, rect.y, rect.w, rect.h);
        texture01.render(renderer, rect.x, rect.y + rect.h, rect.w, rect.h);
    }
    else {
        texture02.render(renderer, rect.x, rect.y, rect.w, rect.h);
        texture02.render(renderer, rect.x, rect.y + rect.h, rect.w, rect.h);
    }
}