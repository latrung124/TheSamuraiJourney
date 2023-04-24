#pragma once
#include "baseState.h"
#include "samurainormalattackstate.h"
#include "samuraiidlestate.h"
#include "samuraistrongattackstate.h"
#include "samuraispecialattackstate.h"
#include "samuraidefendstate.h"
#include "samuraiwalkstate.h"
class SamuraiStateMachine {
public:
    SamuraiStateMachine();
    ~SamuraiStateMachine();
    bool SetState(BaseState* _state);
    void StateAnimationDone();
public:
    BaseState* current_state_;
    SamuraiIdleState* smr_idle_state_;
    SamuraiNormalAttackState* smr_normal_attack_state_;
    SamuraiStrongAttackState* smr_strong_attack_state_;
    SamuraiSpecialAttackState* smr_special_attack_state_;
    SamuraiDefendState* smr_defend_state_;
    SamuraiWalkState* smr_walk_state_;
};
