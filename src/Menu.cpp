#include "Menu.h"
#include "Screen.h"

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), selectedOption(0) {
    sprite = std::make_shared<SpriteComponent>();
    TTF_Init();
    fontButtons = TTF_OpenFont("assets/mountain.otf", 28);
	fontTitle = TTF_OpenFont("assets/mountain.otf", 48);
    textColor = { 0, 0, 0, 255 };

    options.push_back("Play");
    options.push_back("Exit");
}

Menu::~Menu() {
	TTF_CloseFont(fontButtons);
	TTF_CloseFont(fontTitle);
    TTF_Quit();
}

bool Menu::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    return sprite->loadTexture(renderer, path);
}

bool Menu::show() {
    bool running = true;
    bool startGame = false;

    while (running) {
        handleInput(running, startGame);
        render();
        SDL_Delay(100);
    }

    return startGame;
}
void Menu::handleInput(bool& running, bool& startGame) {
    SDL_Event event;

    float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            const bool* keys = SDL_GetKeyboardState(NULL);

            if (keys[SDL_SCANCODE_UP]) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            }
            if (keys[SDL_SCANCODE_DOWN]) {
                selectedOption = (selectedOption + 1) % options.size();
            }
            if (keys[SDL_SCANCODE_RETURN]) {
                SDL_Log("Selected option: %d", selectedOption);
                if (selectedOption == 0)
                {
                    startGame = true;
                    running = false;
                }
                if (selectedOption == 1) running = false;
            }
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int yOffset = 200;
                for (size_t i = 0; i < options.size(); ++i) {
                    SDL_Surface* surface = TTF_RenderText_Solid(fontButtons, options[i].c_str(), NULL, textColor);
                    if (mouseX >= Screen::getWidth() / 2 - surface->w / 2 &&
                        mouseX <= Screen::getWidth() / 2 + surface->w / 2 &&
                        mouseY >= yOffset && mouseY <= yOffset + surface->h) {

                        selectedOption = i; 
                        if (selectedOption == 0) {
                            startGame = true;
                            running = false;
                        }
                        if (selectedOption == 1) {
                            running = false;
                        }
                    }
                    SDL_DestroySurface(surface);
                    yOffset += 50;
                }
            }
        }
    }
}


void Menu::render() {

    sprite->setRect({ 0.0f, 0.0f, (float)Screen::getWidth(), (float)Screen::getHeight() });
    sprite->render(renderer);

	SDL_Surface* surface = TTF_RenderText_Solid(fontTitle, "SKI SDL", NULL, textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FRect destRect = { Screen::getWidth() / 2 - surface->w / 2, 0, surface->w, surface->h };
	SDL_RenderTexture(renderer, texture, NULL, &destRect);

	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);

    int yOffset = 200;
    for (size_t i = 0; i < options.size(); ++i) {
        SDL_Surface* surface = TTF_RenderText_Solid(fontButtons, options[i].c_str(),NULL,
            (i == selectedOption) ? SDL_Color{ 0, 0, 255, 255 } : textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FRect destRect = { Screen::getWidth() / 2 - surface->w / 2, yOffset, surface->w, surface->h };
        SDL_RenderTexture(renderer, texture, NULL, &destRect);

        SDL_DestroyTexture(texture);
        SDL_DestroySurface(surface);

        yOffset += 50;
    }

    SDL_RenderPresent(renderer);
}
