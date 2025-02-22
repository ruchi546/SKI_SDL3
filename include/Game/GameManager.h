#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Actor.h"

class GameManager : public Actor {
public:
    GameManager();
    virtual ~GameManager();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer) override;

	int getHighScore() const;
	void setHighScore(int score);

	float getGameSpeed() const;
	void setGameSpeed(float speed);

private:
	int highScore;
	float gameSpeed;
	float timeElapsed;
	float timeToIncreaseSpeed;
	float speedIncreaseRate;
};

#endif