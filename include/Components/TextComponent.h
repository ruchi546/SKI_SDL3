#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "Component.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextComponent : public Component {
public:
    TextComponent(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    virtual ~TextComponent();

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void setText(const std::string& text);
    void setColor(const SDL_Color& color);
    void setPosition(float x, float y);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_FRect rect;
    SDL_Color color;
    std::string text;

    void updateTexture();
};

#endif // TEXT_COMPONENT_H
