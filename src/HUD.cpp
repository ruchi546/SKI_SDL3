#include "HUD.h"
#include <stdexcept>

HUD::HUD(SDL_Renderer* renderer, const std::string& fontPath, int fontSize) {
    scoreText = std::make_shared<TextComponent>(renderer, fontPath, fontSize);
    addComponent(scoreText);
    scoreText->setPosition(480.0f - 70.0f, 10.0f);
}

HUD::~HUD() {
}

void HUD::update(float deltaTime, int score) {
    scoreText->setText(std::to_string(score));
}

void HUD::render(SDL_Renderer* renderer) {
    Actor::render(renderer);
}
