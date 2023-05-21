#include "Controller/gamemechanismcontroller.h"

static GameMechanismController* game_mechanism_controller_ = nullptr;
GameMechanismController::GameMechanismController() {
    last_x_pos_map_changed_ = 0;
    is_map_moving_ = false;
    real_x_pos_of_map_ = 0;
    background_offset_ = 0;
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

void GameMechanismController::SetBackgroundOffset(int _off_set) {
    background_offset_ = _off_set;
}

int16_t GameMechanismController::GetBackgroundOffset() {
    return background_offset_;
}


void GameMechanismController::UpdatePositionForSamurai(Samurai* _samurai) {
    int x_pos = _samurai->GetXPos();
    int velocity = _samurai->GetVelocityX();
    if (_samurai->GetIsFacingRight()) {
        if (x_pos < WINDOW_WIDTH/2) {
            _samurai->SetXPos(velocity);
            SetIsMapMoving(false);
            SetBackgroundOffset(0);
        } else {
            SetIsMapMoving(true);
            SetBackgroundOffset(velocity);
        }
    } else {
        if (real_x_pos_of_map_ == 0 && x_pos > 0) {
            _samurai->SetXPos(velocity);
            SetIsMapMoving(false);
            SetBackgroundOffset(0);
        } else {
            SetIsMapMoving(true);
            SetBackgroundOffset(velocity);
        }
    }
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
    printf("%s is_map_moving: %d\n", __FUNCSIG__, _is_map_moving);
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
    bool is_collision = false;
    if (_ar_sk->GetStateMachine()->GetCurrentState()) {
        //samurai hurt
    }

    //health progress will be update if the collision is changed to false
    if (_samurai->GetBottomPos() <= _ar_sk->GetTopPos()) {
        return is_collision;
    }
    if (_samurai->GetTopPos() >= _ar_sk->GetBottomPos()) {
        return is_collision;
    }
    if (_samurai->GetRightPos() <= _ar_sk->GetLeftPos()) {
        return is_collision;
    }
    if (_samurai->GetLeftPos() >= _ar_sk->GetRightPos()) {
        return is_collision;
    }
    is_collision = true;
    //if skeleton is changed state from not collision to collision.
    // if (_ar_sk->GetIsCollision()) {
    //     //still collision -> do nothing
    //     return true;
    // } else {
    //     // from not collision change to collision
    //     _ar_sk->SetIsCollision(is_collision);
    // }
    if (dynamic_cast<SamuraiNormalAttackState*>(_samurai->GetSamuraiStateMachine()->GetCurrentState())) {
        //run skeleton hurt state
        printf("skeleton hurt by normal attack state! \n");

        _ar_sk->SetIsCollision(is_collision);
        _ar_sk->Hurt();
    } else if (dynamic_cast<SamuraiSpecialAttackState*>(_samurai->GetSamuraiStateMachine()->GetCurrentState())) {
        printf("skeleton hurt by Special attack state! \n");
        _ar_sk->SetIsCollision(is_collision);
        _ar_sk->Hurt();
        // _ar_sk->SetHealthPoint(SAMURAI_SPECIAL_DAMAGE);
    } else if (dynamic_cast<SamuraiStrongAttackState*>(_samurai->GetSamuraiStateMachine()->GetCurrentState())) {
        printf("skeleton hurt by Strong attack state! \n");
        _ar_sk->SetIsCollision(is_collision);
        _ar_sk->Hurt();
        // _ar_sk->SetHealthPoint(SAMURAI_STRONG_DAMAGE);
    }
    // return (_left1 < _right2 && _right1 > _left2 && _top1 < _bottom2 && _bottom1 > _top2);
    return is_collision;
}

bool GameMechanismController::GuardCheck(int _enemy_x, int _samurai_x) {
    return (_enemy_x - GUARD_DISTANCE <= _samurai_x && _samurai_x <= _enemy_x + GUARD_DISTANCE);
}