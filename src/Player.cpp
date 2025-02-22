#include "Player.h"
#include "Screen.h"
#include "Map.h"
#include <vector>
#include "Obstacle.h"

Player::Player() {
    transform = std::make_shared<TransformComponent>();
    sprite = std::make_shared<SpriteComponent>();
    collider = std::make_shared<ColliderComponent>();
    audio = std::make_shared<AudioComponent>();
    addComponent(transform);
    addComponent(sprite);
    addComponent(collider);
    addComponent(audio);
    score = 0;
    scoreTimer = 0.0f;
    scoreInterval = 1.0f;
    dead = false;
    lastMovingLeft = false;
    turnTrail = nullptr;
    speed = 500.0f;

    transform->setPosition(Screen::WIDTH / 2, 100.0f);
    sprite->setRect({ 0, 0, 25.0f, 25.0f });
    collider->setRect({ 0, 0, 25.0f, 25.0f });

    audio->loadSound("assets/death_sound.wav", "death");
}

Player::~Player() {
    if (turnTrail) {
        delete turnTrail;
    }
}

bool Player::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    return sprite->loadTexture(renderer, path);
}

bool Player::loadTrailTexture(SDL_Renderer* renderer, const std::string& path) {
    return trailTexture.loadFromFile(renderer, path);
}

void Player::increaseScore() {
    score++;
}

int Player::getScore() const {
    return score;
}

bool Player::isAlive() const {
    return !dead;
}

void Player::setDead(bool dead) {
    this->dead = dead;
    if (dead) {
        audio->playSound("death");
    }
}

float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    this->speed = speed;
}

void Player::restart() {
    transform->setPosition(Screen::WIDTH / 2, 100.0f);
    score = 0;
    scoreTimer = 0.0f;
    dead = false;
    trails.clear();
}

void Player::handleEvent(const SDL_Event& event) {
    const bool* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        isMovingLeft = true;
        isMovingRight = false;
    }
    else {
        isMovingLeft = false;
    }

    if (keys[SDL_SCANCODE_RIGHT]) {

        isMovingRight = true;
        isMovingLeft = false;
    }
    else {
        isMovingRight = false;
    }
}

void Player::update(float deltaTime, std::vector<Obstacle*> obstacles, const Map& map, GameManager* gameManager) {

    SDL_FPoint position = transform->getPosition();
    SDL_FRect rect = sprite->getRect();
    collider->setRect({ position.x, position.y, rect.w, rect.h });

    for (auto* obstacle : obstacles) {
        if (collider->checkCollision(obstacle->getCollisionRect())) {
            setDead(true);
        }
    }

    bool isMoving = false;
    bool isTurning = false;
    float newX = position.x;


    if (isMovingLeft) {
        newX -= speed * deltaTime;
        isMoving = true;
        if (!lastMovingLeft) {
            isTurning = true;
            lastMovingLeft = true;
        }
    }

    if (isMovingRight) {
        newX += speed * deltaTime;
        isMoving = true;
        if (lastMovingLeft) {
            isTurning = true;
            lastMovingLeft = false;
        }
    }

    if (!map.isCollision(newX, position.y) && !map.isCollision(newX + rect.w, position.y)) {
        position.x = newX;
    }
    
    transform->setPosition(position.x, position.y);

    scoreTimer += deltaTime;
    if (scoreTimer >= 0.2f) {
        score += static_cast<int>(gameManager->getGameSpeed() / 100.0f) - 1;
        scoreTimer = 0.0f;
    }

    if (!isMoving) {
        Trail newTrail = {
            { position.x - 2, position.y - 30, rect.w * 1.2f, rect.h * 1.2f },
            0.5f,
            0.0f
        };
        trails.push_back(newTrail);
    }

    if (isTurning) {
        if (turnTrail == nullptr) {
            turnTrail = new Trail{
                { position.x - 2, position.y - 30, rect.w * 1.2f, rect.h * 1.2f },
                1.0f,
                0.0f
            };
        }
    }

    if (turnTrail) {
        turnTrail->rect.x = position.x - 2;
        turnTrail->rect.y = position.y - 30;
        turnTrail->timeAlive += deltaTime;
        turnTrail->alpha -= deltaTime * 0.5f;

        if (turnTrail->alpha < 0.0f) {
            turnTrail->alpha = 0.0f;
        }
    }

    for (auto& trail : trails) {
        trail.timeAlive += deltaTime;
        trail.alpha -= deltaTime * 0.5f;
		trail.rect.y -= gameManager->getGameSpeed() * deltaTime;
        if (trail.alpha < 0.0f) {
            trail.alpha = 0.0f;
        }
    }

    trails.erase(std::remove_if(trails.begin(), trails.end(), [](const Trail& trail) {
        return trail.alpha <= 0.0f;
        }), trails.end());
}

void Player::render(SDL_Renderer* renderer) {
    SDL_FPoint position = transform->getPosition();
    SDL_FRect rect = sprite->getRect();

    sprite->setRect({ position.x, position.y, rect.w, rect.h });
    sprite->render(renderer);

    if (&trailTexture) {
        for (const auto& trail : trails) {
            SDL_SetRenderDrawColor(renderer, 1.0f, 1.0f, 1.0f, trail.alpha);
            trailTexture.render(renderer, trail.rect.x, trail.rect.y, trail.rect.w, trail.rect.h);
        }
    }

    if (turnTrail && &trailTexture) {
        SDL_SetRenderDrawColor(renderer, 1.0f, 0.0f, 0.0f, turnTrail->alpha);
        trailTexture.render(renderer, turnTrail->rect.x, turnTrail->rect.y, turnTrail->rect.w, turnTrail->rect.h);
    }
}
