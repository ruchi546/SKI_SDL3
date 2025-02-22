#include "DieScreen.h"
#include "Screen.h"

DieScreen::DieScreen(SDL_Renderer* renderer, const std::string& fontPath, int fontSize)
    : renderer(renderer), font(nullptr), backgroundTexture(nullptr), visible(false), runScore(0), highScore(0) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        SDL_Log("Failed to load font");
    }

    SDL_Color darkColor = { 0, 0, 0, 128 };
    backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::getWidth(), Screen::getHeight());
    SDL_SetTextureBlendMode(backgroundTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer, darkColor.r, darkColor.g, darkColor.b, darkColor.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);

    runScoreText = std::make_shared<TextComponent>(renderer, fontPath, fontSize);
    highScoreText = std::make_shared<TextComponent>(renderer, fontPath, fontSize);
	continueText = std::make_shared<TextComponent>(renderer, fontPath, fontSize);
}

DieScreen::~DieScreen() {
    if (font) {
        TTF_CloseFont(font);
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }

}

void DieScreen::show(int runScore, int highScore) {
    this->runScore = runScore;
    this->highScore = highScore;
    runScoreText->setText("Run Score: " + std::to_string(runScore));
    runScoreText->setColor({ 255, 255, 255, 255 });
    highScoreText->setText("High Score: " + std::to_string(highScore));
    highScoreText->setColor({ 255, 255, 255, 255 });
	continueText->setText("Press Enter to Restart");
	continueText->setColor({ 255, 255, 255, 255 });
    
    visible = true;
}

void DieScreen::hide() {
    visible = false;
}

bool DieScreen::isVisible() const {
    return visible;
}

void DieScreen::handleEvent(const SDL_Event& event) {
    const bool* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_RETURN]) {
        hide();
    }
}

void DieScreen::render() {
    if (!visible) return;

    SDL_RenderTexture(renderer, backgroundTexture, nullptr, nullptr);
    SDL_FRect runScoreRect = { (float)Screen::getWidth() / 2 - 100, (float)Screen::getHeight() / 2 - 50, 200, 50 };
    SDL_FRect highScoreRect = { (float)Screen::getWidth() / 2 - 100, (float)Screen::getHeight() / 2, 200, 50 };

    runScoreText->setPosition(runScoreRect.x, runScoreRect.y);
    runScoreText->render(renderer);

    highScoreText->setPosition(highScoreRect.x, highScoreRect.y);
    highScoreText->render(renderer);

	continueText->setPosition((float)Screen::getWidth() / 2 - 100, (float)Screen::getHeight() / 2 +50);
	continueText->render(renderer);
}

SDL_Texture* DieScreen::createTextTexture(const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(),text.length(), color);
    if (!surface) {
        SDL_Log("Failed to create text surface");
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}