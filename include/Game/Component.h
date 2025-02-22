#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL3/SDL.h>

class Component {
public:
    virtual ~Component() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif // COMPONENT_H
