#ifndef SCROLLABLE_OBJECT_H
#define SCROLLABLE_OBJECT_H

#include <SDL3/SDL.h>
#include "Texture.h"
#include "GameManager.h"

class ScrollableObject {
public:
    ScrollableObject(GameManager* gameManager, float width, float height);
    virtual ~ScrollableObject() = default;

    virtual bool loadTextures(SDL_Renderer* renderer, const std::string& path1, const std::string& path2 = "");
    void randomTexture();
	virtual void update(float deltaTime, GameManager* gameManager);
    virtual void render(SDL_Renderer* renderer);

protected:
    SDL_FRect rect;
    Texture texture01;
    Texture texture02;
    int currentTexture;
    float speed;
};

#endif // SCROLLABLE_OBJECT_H