#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include <SDL3/SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent();
    virtual ~TransformComponent();

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void setPosition(float x, float y);
    void setRotation(float angle);
    void setScale(float scaleX, float scaleY);

    SDL_FPoint getPosition() const;
    float getRotation() const;
    SDL_FPoint getScale() const;

private:
    SDL_FPoint position;
    float rotation;
    SDL_FPoint scale;
};

#endif // TRANSFORM_COMPONENT_H