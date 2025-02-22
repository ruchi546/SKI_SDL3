#include "Decoration.h"

Decoration::Decoration(GameManager* gameManager)
    : ScrollableObject(gameManager, 480.0f, 1280.0f) {
    randomTexture();
}