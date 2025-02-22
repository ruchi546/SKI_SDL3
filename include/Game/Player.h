#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "AudioComponent.h"
#include <vector>
#include "Obstacle.h"
#include "Map.h"

class Player : public Actor {
public:
    Player();
    virtual ~Player();

	void handleEvent(const SDL_Event& event);
	void update(float deltaTime, std::vector<Obstacle*> obstacles, const Map& map, GameManager* gameManager);
    void render(SDL_Renderer* renderer) override;
    bool loadTexture(SDL_Renderer* renderer, const std::string& path);
    bool loadTrailTexture(SDL_Renderer* renderer, const std::string& path);

    int getScore() const;
    void increaseScore();
    bool isAlive() const;
    void restart();
    void setDead(bool dead);
    float getSpeed() const;
    void setSpeed(float speed);

private:
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<SpriteComponent> sprite;
    std::shared_ptr<ColliderComponent> collider;
    std::shared_ptr<AudioComponent> audio;

    Texture trailTexture;
    struct Trail {
        SDL_FRect rect;
        float alpha;
        float timeAlive;
    };
    std::vector<Trail> trails;
    Trail* turnTrail;

    bool lastMovingLeft;
    int score;
    float scoreTimer;
    float scoreInterval;
    bool dead;
    float speed;
	bool isMovingLeft;
	bool isMovingRight;
};

#endif // PLAYER_H
