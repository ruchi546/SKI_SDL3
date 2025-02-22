#include "Map.h"

Map::Map(GameManager* gameManager)
    : rect{ 0.0f, 0.0f, 480.0f, 1280.0f }, speed(gameManager->getGameSpeed()), collisionMap(nullptr) {
}

Map::~Map() {
    if (collisionMap) {
        SDL_DestroySurface(collisionMap);
    }
}

bool Map::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    return texture.loadFromFile(renderer, path);
}

bool Map::loadCollisionMap(const std::string& path) {
    collisionMap = SDL_LoadBMP(path.c_str());
    if (!collisionMap) {
        SDL_Log("Error al cargar el mapa de colisión: %s", SDL_GetError());
        return false;
    }
    return true;
}

bool Map::isCollision(float x, float y) const {
    if (!collisionMap) return false;

    int mapX = static_cast<int>(x);
    int mapY = static_cast<int>(y);

    if (mapX < 0 || mapX >= collisionMap->w || mapY < 0 || mapY >= collisionMap->h)
        return true;

    const SDL_PixelFormatDetails* formatDetails = SDL_GetPixelFormatDetails(collisionMap->format);
    if (!formatDetails) return true;

    Uint32 pixel = ((Uint32*)collisionMap->pixels)[mapY * collisionMap->w + mapX];
    Uint8 r, g, b;

    SDL_GetRGB(pixel, formatDetails, nullptr, &r, &g, &b);

    return !(r == 255 && g == 255 && b == 255);
}

void Map::update(float deltaTime, GameManager* gameManager) {
    speed = gameManager->getGameSpeed();
    rect.y -= speed * deltaTime;
    if (rect.y + rect.h < 0) {
        rect.y = 0;
    }
}

void Map::render(SDL_Renderer* renderer) {
    texture.render(renderer, rect.x, rect.y, rect.w, rect.h);
    texture.render(renderer, rect.x, rect.y + rect.h, rect.w, rect.h);
}