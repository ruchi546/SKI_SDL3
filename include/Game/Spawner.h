#ifndef SPAWNER_H
#define SPAWNER_H

#include <vector>
#include "Obstacle.h"

class Spawner {
public:
    Spawner();
    ~Spawner();

    void spawnObstacle(SDL_Renderer* renderer, GameManager* gameManager);
    void restart();
	std::vector<Obstacle*> getObstacles() { return obstacles; }
	void update(float deltaTime, SDL_Renderer* renderer, GameManager* gameManager);
    void render(SDL_Renderer* renderer);

private:
    std::vector<Obstacle*> obstacles;
    float spawnTimer;
    float spawnInterval;
};

#endif // SPAWNER_H