#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"
#include "Texture.h"
#include <string>

class SpriteComponent : public Component {
public:
    SpriteComponent();
    virtual ~SpriteComponent();

    bool loadTexture(SDL_Renderer* renderer, const std::string& path);
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;

    void setRect(const SDL_FRect& rect);
    SDL_FRect getRect() const;

private:
    Texture texture;
    SDL_FRect rect;
};

#endif // SPRITE_COMPONENT_H
