#ifndef HUD_H
#define HUD_H

#include "Actor.h"
#include "TextComponent.h"
#include <SDL3/SDL.h>
#include <string>

class HUD : public Actor {
public:
    HUD(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    virtual ~HUD();

    void update(float deltaTime, int score);
    void render(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<TextComponent> scoreText;
};

#endif // HUD_H