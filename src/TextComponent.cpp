#include "TextComponent.h"
#include <stdexcept>

TextComponent::TextComponent(SDL_Renderer* renderer, const std::string& fontPath, int fontSize)
    : renderer(renderer), texture(nullptr), color({ 0, 0, 0, 255 }) {
    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize TTF: %s", SDL_GetError());
        throw std::runtime_error("Failed to initialize TTF");
    }
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        throw std::runtime_error("Failed to load font");
    }
}

TextComponent::~TextComponent() {
    if (texture) SDL_DestroyTexture(texture);
    if (font) TTF_CloseFont(font);
}

void TextComponent::update(float deltaTime) {
    // Update logic for text component if needed
}

void TextComponent::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
}

void TextComponent::setText(const std::string& text) {
    this->text = text;
    updateTexture();
}

void TextComponent::setColor(const SDL_Color& color) {
    this->color = color;
    updateTexture();
}

void TextComponent::setPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
}

void TextComponent::updateTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.w = surface->w;
    rect.h = surface->h;

    SDL_DestroySurface(surface);
}
