#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "Component.h"
#include <SDL3/SDL.h>

class ColliderComponent : public Component {
public:
    ColliderComponent();
    virtual ~ColliderComponent();

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void setRect(const SDL_FRect& rect);
    SDL_FRect getRect() const;

    bool checkCollision(const SDL_Rect& otherRect) const;

private:
    SDL_FRect rect;
};

#endif // COLLIDER_COMPONENT_H