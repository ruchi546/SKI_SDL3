#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Actor.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "GameManager.h"
#include <vector>

class Obstacle : public Actor {
public:
    Obstacle(float x, float y, float w, float h, SDL_Renderer* renderer, GameManager* gameManager);
    ~Obstacle();

	void update(float deltaTime, GameManager* gameManager);
    void render(SDL_Renderer* renderer) override;

    SDL_FRect getRect() const;
    SDL_Rect getCollisionRect() const;

private:
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<SpriteComponent> sprite;
    std::shared_ptr<ColliderComponent> collider;
    float speed;

    void randomTexture(SDL_Renderer* renderer);
    std::vector<std::string> texturePaths;
};

#endif // OBSTACLE_H