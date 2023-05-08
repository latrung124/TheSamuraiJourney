#include "Controller/gamemechanismcontroller.h"

static GameMechanismController* game_mechanism_controller_ = nullptr;
GameMechanismController::GameMechanismController() {
    last_x_pos_map_changed_ = 0;
    is_map_moving_ = false;
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

void GameMechanismController::UpdatePositionOfEnemies(std::vector<std::shared_ptr<ArcherSkeleton>>& _ar_sk_enemies) {
    if (!is_map_moving_) return;
    if (real_x_pos_of_map_ == 0) return;
    for (int i = 0; i < _ar_sk_enemies.size(); ++i) {
        if (_ar_sk_enemies[i] != nullptr) {
            _ar_sk_enemies[i]->ChangedPosAfterMapChanged(last_x_pos_map_changed_);
        }
    }
}

void GameMechanismController::SetIsMapMoving(bool _is_map_moving) {
    if (_is_map_moving != is_map_moving_) {
        is_map_moving_ = _is_map_moving;
    }
}

bool GameMechanismController::GetIsMapMoving() {
    return is_map_moving_;
}

void GameMechanismController::IncreaseRealXPosOfMap(int _x_pos) {
    last_x_pos_map_changed_ = (-1) * _x_pos;
    real_x_pos_of_map_ += _x_pos;
}

void GameMechanismController::DecreaseRealXPosOfMap(int _x_pos) {
    last_x_pos_map_changed_ = _x_pos;
    real_x_pos_of_map_ -= _x_pos;
}

int GameMechanismController::GetRealXPosOfMap() {
    return real_x_pos_of_map_;
}