#include "Game.h"
#include "Screen.h"
#include "Map.h"
#include "Spawner.h"
#include "Menu.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"

Game::Game()
    : window(nullptr), renderer(nullptr), player(nullptr), gameManager(nullptr),
    gameMap(nullptr), lift(nullptr), decoration(nullptr), hud(nullptr),
    musicActor(nullptr), dieScreen(nullptr), imGuiManager(nullptr),
    isPaused(false), lastFrameTicks(0) {

    if (!initialize()) {
        SDL_Log("Failed to initialize the game.");
        exit(1);
    }

    gameManager = new GameManager();
    gameManager->setGameSpeed(200.0f);

    player = new Player();
    player->setDead(false);
    player->loadTexture(renderer, "assets/player.png");
    player->loadTrailTexture(renderer, "assets/trail.png");

    gameMap = new Map(gameManager);
    gameMap->loadTexture(renderer, "assets/map.png");
    gameMap->loadCollisionMap("assets/map_collider.bmp");

    lift = new Lift(gameManager);
    lift->loadTextures(renderer, "assets/lift01.png", "assets/lift02.png");

    decoration = new Decoration(gameManager);
    decoration->loadTextures(renderer, "assets/decoration01.png", "assets/decoration02.png");

    hud = new HUD(renderer, "assets/mountain.otf", 24);

    musicActor = new MusicActor(renderer, "assets/background_music.wav");
    musicActor->playMusic(true);

    dieScreen = new DieScreen(renderer, "assets/mountain.otf", 24);
    imGuiManager = new ImGuiManager(gameManager, player, dieScreen);
}

Game::~Game() {
    cleanup();
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Ski_SDL3", Screen::WIDTH, Screen::HEIGHT, NULL);
    if (!window) {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("Couldn't create renderer: %s", SDL_GetError());
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) {
            SDL_Quit();
            exit(0);
        }

        player->handleEvent(event);
        imGuiManager->handleEvent(event);

        if (dieScreen->isVisible()) {
            dieScreen->handleEvent(event);
            const bool* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_RETURN]) {
                dieScreen->hide();
                isPaused = false;
                decoration->randomTexture();
                lift->randomTexture();
                spawner.restart();
                hud->update(0, 0);
                gameManager->setGameSpeed(200.0f);
                player->restart();
            }
            return;
        }
    }
}

void Game::update() {
    if (dieScreen->isVisible()) {
        return;
    }

    Uint64 ticks = SDL_GetTicks();
    float deltaTime = (ticks - lastFrameTicks) / 1000.0f;
    lastFrameTicks = ticks;

    gameManager->update(deltaTime);

    if (player && !player->isAlive()) {
        if (player->getScore() > gameManager->getHighScore()) {
            gameManager->setHighScore(player->getScore());
        }

        dieScreen->show(player->getScore(), gameManager->getHighScore());
        isPaused = true;
        return;
    }

    gameMap->update(deltaTime, gameManager);
    decoration->update(deltaTime, gameManager);
    lift->update(deltaTime, gameManager);

    if (player) {
        player->update(deltaTime, spawner.getObstacles(), *gameMap, gameManager);
    }

    spawner.update(deltaTime, renderer, gameManager);
    hud->update(deltaTime, player->getScore());
    musicActor->update(deltaTime);
}

void Game::render() {
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    imGuiManager->render();
    gameMap->render(renderer);
    decoration->render(renderer);

    if (player) {
        player->render(renderer);
    }

    hud->render(renderer);
    spawner.render(renderer);
    lift->render(renderer);

    if (dieScreen->isVisible()) {
        dieScreen->render();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    delete player;
    delete dieScreen;
    delete imGuiManager;
    delete gameManager;
    delete gameMap;
    delete lift;
    delete decoration;
    delete hud;
    delete musicActor;

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
}

void Game::run() {
    Menu menu(renderer);
    menu.loadTexture(renderer, "assets/map.png");
    if (!menu.show()) {
        return;
    }

    while (true) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}