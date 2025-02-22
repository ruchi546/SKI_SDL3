#include "Spawner.h"
#include "Obstacle.h"
#include <cstdlib>
#include <ctime>

Spawner::Spawner()
    : spawnTimer(0.0f), spawnInterval(1.0f) {
    std::srand(std::time(nullptr));
}

Spawner::~Spawner() {
    for (auto* obstacle : obstacles) {
        delete obstacle;
    }
}

void Spawner::spawnObstacle(SDL_Renderer* renderer, GameManager* gameManager) {
    float x = static_cast<float>(rand() % (480 - 2 * 96) + 96);
    float y = -100.0f;
    float w = 20.0f;
    float h = 20.0f;

    Obstacle* newObstacle = new Obstacle(x, y, w, h, renderer, gameManager);
    obstacles.push_back(newObstacle);
}

void Spawner::restart() {
    spawnTimer = 0.0f;

    for (auto* obstacle : obstacles) {
        delete obstacle;
    }
    obstacles.clear();
}

void Spawner::update(float deltaTime, SDL_Renderer* renderer, GameManager* gameManager) {
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval) {
        spawnObstacle(renderer, gameManager);
        spawnTimer = 0.0f;
    }

    for (auto* obstacle : obstacles) {
		obstacle->update(deltaTime, gameManager);
    }
}

void Spawner::render(SDL_Renderer* renderer) {
    for (auto* obstacle : obstacles) {
        obstacle->render(renderer);
    }
}