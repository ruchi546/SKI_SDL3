#include "Obstacle.h"
#include "Screen.h"
#include <cstdlib>
#include <ctime>

Obstacle::Obstacle(float x, float y, float w, float h, SDL_Renderer* renderer, GameManager* gameManager) {
    speed = gameManager->getGameSpeed();
    transform = std::make_shared<TransformComponent>();
    sprite = std::make_shared<SpriteComponent>();
    collider = std::make_shared<ColliderComponent>();
    addComponent(transform);
    addComponent(sprite);
    addComponent(collider);

    transform->setPosition(x, y);
    sprite->setRect({ x, y, w, h });
    collider->setRect({ x, y, w, h });

    texturePaths = {
        "assets/obstacle01.png",
        "assets/obstacle02.png"
    };

    randomTexture(renderer);
}

Obstacle::~Obstacle() {}

void Obstacle::randomTexture(SDL_Renderer* renderer) {
    int randomIndex = rand() % texturePaths.size();
    sprite->loadTexture(renderer, texturePaths[randomIndex]);
}

void Obstacle::update(float deltaTime, GameManager* gameManager) {
    SDL_FPoint position = transform->getPosition();
    speed = gameManager->getGameSpeed();
    position.y -= speed * deltaTime;

    if (position.y + sprite->getRect().h < 0) {
        position.y = Screen::HEIGHT;
		position.x = static_cast<float>(rand() % (480 - 2 * 96) + 96);
    }

    transform->setPosition(position.x, position.y);
    collider->setRect({ position.x, position.y, sprite->getRect().w, sprite->getRect().h });
}

void Obstacle::render(SDL_Renderer* renderer) {
    SDL_FPoint position = transform->getPosition();
    SDL_FRect rect = sprite->getRect();
    sprite->setRect({ position.x, position.y, rect.w, rect.h });
    sprite->render(renderer);
}

SDL_FRect Obstacle::getRect() const {
    return sprite->getRect();
}

SDL_Rect Obstacle::getCollisionRect() const {
    SDL_FRect rect = collider->getRect();
    return { (int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h };
}
