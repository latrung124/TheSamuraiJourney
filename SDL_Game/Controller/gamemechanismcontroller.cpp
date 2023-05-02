#include "Controller/gamemechanismcontroller.h"

static GameMechanismController* game_mechanism_controller_ = nullptr;
GameMechanismController::GameMechanismController() {
    real_x_pos_of_map_ = 0;
}

GameMechanismController::~GameMechanismController() {
    if (game_mechanism_controller_ != nullptr) {
        delete game_mechanism_controller_;
        game_mechanism_controller_ = nullptr;
    }
}

GameMechanismController* GameMechanismController::Instance() {
    if (game_mechanism_controller_ == nullptr) {
        game_mechanism_controller_ = new GameMechanismController();
    }
    return game_mechanism_controller_;
}

void GameMechanismController::IncreaseRealXPosOfMap(int _x_pos) {
    real_x_pos_of_map_ += _x_pos;
}

void GameMechanismController::DecreaseRealXPosOfMap(int _x_pos) {
    real_x_pos_of_map_ -= _x_pos;
}

int GameMechanismController::GetRealXPosOfMap() {
    return real_x_pos_of_map_;
}