#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "HUD.h"
#include "MusicActor.h"
#include "Map.h"
#include "Lift.h"
#include "Decoration.h"
#include "DieScreen.h"
#include "ImGuiManager.h"
#include "Spawner.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
	float lastFrameTicks;

	GameManager* gameManager;
    Player* player;
    Spawner spawner;
    Obstacle* obstacle;
	HUD* hud;
	MusicActor* musicActor;
	Map* gameMap;
	Lift* lift;
	Decoration* decoration;
    DieScreen* dieScreen;
	ImGuiManager* imGuiManager;

    bool initialize();
    void handleEvents();
    void update();
    void render();
    void cleanup();

    bool isPaused;
	int imGuiNewHighScoreValue = 0;
};

#endif // GAME_H