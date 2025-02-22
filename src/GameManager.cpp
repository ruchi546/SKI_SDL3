#include "GameManager.h"

GameManager::GameManager() : highScore(0) {
	gameSpeed = 200.0f;
	timeElapsed = 0.0f;
	timeToIncreaseSpeed = 2.0f;
	speedIncreaseRate = 20.0f;
}

GameManager::~GameManager() {
}

void GameManager::update(float deltaTime) {
    timeElapsed += deltaTime;

    if (timeElapsed >= timeToIncreaseSpeed) {
        gameSpeed += speedIncreaseRate;
        timeElapsed = 0.0f;
    }
}

void GameManager::render(SDL_Renderer* renderer) {
}

int GameManager::getHighScore() const {
	return highScore;
}

void GameManager::setHighScore(int score) {
	highScore = score;
}

float GameManager::getGameSpeed() const {
	return gameSpeed;
}

void GameManager::setGameSpeed(float speed) {
	gameSpeed = speed;
}