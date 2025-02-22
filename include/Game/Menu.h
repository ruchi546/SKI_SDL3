#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "Actor.h"
#include "SpriteComponent.h"


class Menu:public Actor {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    bool loadTexture(SDL_Renderer* renderer, const std::string& path);
    bool show();

private:
    std::shared_ptr<SpriteComponent> sprite;

    SDL_Renderer* renderer;
    TTF_Font* fontButtons;
    TTF_Font* fontTitle;

    SDL_Color textColor;

    std::vector<std::string> options;
    int selectedOption;

    void render();
    void handleInput(bool& running, bool& startGame);
};

#endif // MENU_H
