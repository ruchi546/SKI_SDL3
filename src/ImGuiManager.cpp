#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(GameManager* gameManager, Player* player, DieScreen* dieScreen)
    : gameManager(gameManager), player(player), dieScreen(dieScreen), imGuiNewHighScoreValue(0), showImGuiWindow(false) {
}

ImGuiManager::~ImGuiManager() {
}

void ImGuiManager::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        // Verificar si se presionó Ctrl + I
        if (event.key.key == SDLK_I && (event.key.mod & SDL_KMOD_CTRL)) {
            showImGuiWindow = !showImGuiWindow; // Alternar visibilidad
        }
    }
}

void ImGuiManager::render() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (showImGuiWindow) {

        ImGui::Begin("Game", nullptr, ImGuiWindowFlags_None);
        if (ImGui::BeginTabBar("Tabs")) {
            if (ImGui::BeginTabItem("Score")) {
                ImGui::Text("Current Score: %d", player->getScore());
                ImGui::Text("High Score: %d", gameManager->getHighScore());

                ImGui::InputInt("New High Score", &imGuiNewHighScoreValue);
                if (ImGui::Button("Apply")) {
                    gameManager->setHighScore(imGuiNewHighScoreValue);
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Game Speed")) {
                ImGui::Text("Game Speed: %f", gameManager->getGameSpeed());
                if (ImGui::Button("Increase Game Speed")) {
                    gameManager->setGameSpeed(gameManager->getGameSpeed() + 10.0f);
                }
                if (ImGui::Button("Decrease Game Speed")) {
                    gameManager->setGameSpeed(gameManager->getGameSpeed() - 10.0f);
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Player Settings")) {
                static float playerSpeed = player->getSpeed();
                ImGui::SliderFloat("Player Speed", &playerSpeed, 0.0f, 1000.0f);
                if (ImGui::Button("Apply Player Speed")) {
                    player->setSpeed(playerSpeed);
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }
    ImGui::Render();
}