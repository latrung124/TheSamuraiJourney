#pragma once
#include "baseState.h"
#include "samurainormalattackstate.h"
#include "samuraiidlestate.h"
#include "samuraistrongattackstate.h"
#include "samuraispecialattackstate.h"
#include "samuraidefendstate.h"
#include "samuraiwalkstate.h"
#include "archerskeletonidlestate.h"
#include "archerskeletonnormalattackstate.h"
#include "archerskeletonspecialattackstate.h"
#include "archerskeletonstrongattackstate.h"
#include "archerskeletondiestate.h"
#include "archerskeletonhurtstate.h"
#include "archerskeletondefendstate.h"
#include "archerskeletonnormalshotstate.h"
#include "archerskeletonwalkstate.h"

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
public:
    SamuraiIdleState* smr_idle_state_;
    SamuraiNormalAttackState* smr_normal_attack_state_;
    SamuraiStrongAttackState* smr_strong_attack_state_;
    SamuraiSpecialAttackState* smr_special_attack_state_;
    SamuraiDefendState* smr_defend_state_;
    SamuraiWalkState* smr_walk_state_;
};

class ArcherSkeleton;
class SkeletonStateMachine : public StateMachine{
public:
    SkeletonStateMachine(ArcherSkeleton* _ar_sk);
    ~SkeletonStateMachine();

    virtual bool SetState(BaseState* _state) override;
    virtual void StateAnimationDone() override;
    void StateAnimationUpdate(std::shared_ptr<ArcherSkeleton>& _ar_sk);

    ArcherSkeletonIdleState* ar_sk_idle_state_;
};
