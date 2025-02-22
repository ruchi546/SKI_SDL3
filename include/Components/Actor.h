#ifndef ACTOR_H
#define ACTOR_H

#include <SDL3/SDL.h>
#include <vector>
#include <memory>

class Component;

class Actor {
public:
    Actor();
    virtual ~Actor();

    void update(float deltaTime);
    virtual void render(SDL_Renderer* renderer);

    void addComponent(std::shared_ptr<Component> component);
    template <typename T>
    T* getComponent();

    const std::vector<std::shared_ptr<Component>>& getComponents() const;

private:
    std::vector<std::shared_ptr<Component>> components;
};

#endif // ACTOR_H
