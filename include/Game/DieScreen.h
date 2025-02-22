#ifndef DIE_SCREEN_H
#define DIE_SCREEN_H

#include <SDL3/SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Actor.h"
#include "TextComponent.h"

class DieScreen:public Actor {
public:
    DieScreen(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    ~DieScreen();

    void show(int runScore, int highScore);
    void hide();
    bool isVisible() const;

    void handleEvent(const SDL_Event& event);
    void render();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* backgroundTexture;
    std::shared_ptr<TextComponent> runScoreText;
    std::shared_ptr<TextComponent> highScoreText;
	std::shared_ptr<TextComponent> continueText;
    bool visible;
    int runScore;
    int highScore;

    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);
};
#endif // DIE_SCREEN_H