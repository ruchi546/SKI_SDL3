#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "GameManager.h"
#include "Player.h"
#include "DieScreen.h"
#include "imgui.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"

class ImGuiManager {
public:
    ImGuiManager(GameManager* gameManager, Player* player, DieScreen* dieScreen);
    ~ImGuiManager();

    void render();
	void handleEvent(const SDL_Event& event);

private:
    GameManager* gameManager;
    Player* player;
    DieScreen* dieScreen;
    int imGuiNewHighScoreValue;
	bool showImGuiWindow = true;
};

#endif // IMGUIMANAGER_H