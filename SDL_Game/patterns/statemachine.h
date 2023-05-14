#pragma once
#include "baseState.h"
#include "samurainormalattackstate.h"
#include "samuraiidlestate.h"
#include "samuraistrongattackstate.h"
#include "samuraispecialattackstate.h"
#include "samuraidefendstate.h"
#include "samuraiwalkstate.h"
#include "samuraihurtstate.h"

class StateMachine {
public:
    virtual bool SetState(BaseState* _state) = 0;
    virtual void StateAnimationDone() = 0;

    BaseState* current_state_;

};

class SamuraiStateMachine : public StateMachine{
public:
    SamuraiStateMachine();
    ~SamuraiStateMachine();
    virtual bool SetState(BaseState* _state) override;
    virtual void StateAnimationDone() override;
    BaseState* GetCurrentState();
public:
    SamuraiIdleState* smr_idle_state_;
    SamuraiNormalAttackState* smr_normal_attack_state_;
    SamuraiStrongAttackState* smr_strong_attack_state_;
    SamuraiSpecialAttackState* smr_special_attack_state_;
    SamuraiDefendState* smr_defend_state_;
    SamuraiWalkState* smr_walk_state_;
    SamuraiHurtState* smr_hurt_state_;
};
