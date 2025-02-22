#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include "Texture.h"
#include "GameManager.h"

class Map {
public:
    Map(GameManager* gameManager);
    ~Map();

    bool loadTexture(SDL_Renderer* renderer, const std::string& path);
    bool loadCollisionMap(const std::string& path);
	void update(float deltaTime, GameManager* gameManager);
    void render(SDL_Renderer* renderer);

    bool isCollision(float x, float y) const;

private:
    SDL_FRect rect;
    Texture texture;
    float speed;

    SDL_Surface* collisionMap;
};

#endif // MAP_H