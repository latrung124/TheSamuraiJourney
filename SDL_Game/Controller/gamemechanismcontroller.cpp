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

bool GameMechanismController::ColisionCheck(Samurai* _samurai, std::shared_ptr<ArcherSkeleton>& _ar_sk) {
    // printf("top1: %d, bot1: %d, right1: %d, left1: %d \n", _top1, _bottom1, _right1, _left1);
    // printf("top2: %d, bot2: %d, right2: %d, left2: %d \n", _top2, _bottom2, _right2, _left2);
    if (_ar_sk->GetStateMachine()->GetCurrentState()) {
        //samurai hurt
    }

    if (_samurai->GetBottomPos() <= _ar_sk->GetTopPos()) {
        return false;
    }
    if (_samurai->GetTopPos() >= _ar_sk->GetBottomPos()) {
        return false;
    }
    if (_samurai->GetRightPos() <= _ar_sk->GetLeftPos()) {
        return false;
    }
    if (_samurai->GetLeftPos() >= _ar_sk->GetRightPos()) {
        return false;
    }
    if (dynamic_cast<SamuraiNormalAttackState*>(_samurai->GetSamuraiStateMachine()->GetCurrentState())) {
        //run skeleton hurt state
        printf("run skeleton hurt state! \n");
        _ar_sk->Hurt();
    }
    // return (_left1 < _right2 && _right1 > _left2 && _top1 < _bottom2 && _bottom1 > _top2);
    return true;
}

bool GameMechanismController::GuardCheck(int _enemy_x, int _samurai_x) {
    return (_enemy_x - GUARD_DISTANCE <= _samurai_x && _samurai_x <= _enemy_x + GUARD_DISTANCE);
}