#pragma once
#include "archerskeletonbasestate.h"
#include "character/ArcherSkeleton.h"
#include "archerskeletonidlestate.h"
#include "archerskeletonnormalattackstate.h"
#include "archerskeletonspecialattackstate.h"
#include "archerskeletonstrongattackstate.h"
#include "archerskeletondiestate.h"
#include "archerskeletonhurtstate.h"
#include "archerskeletondefendstate.h"
#include "archerskeletonnormalshotstate.h"
#include "archerskeletonwalkstate.h"

class SkeletonStateMachine{
public:
    SkeletonStateMachine();
    ~SkeletonStateMachine();

    bool SetState(ArcherSkeletonBaseState* _state, ArcherSkeleton* _ar_sk);
    void StateAnimationUpdate(ArcherSkeleton* _ar_sk);
    ArcherSkeletonBaseState* GetIdleState();
    ArcherSkeletonBaseState* GetHurtState();

private:
    ArcherSkeletonIdleState* ar_sk_idle_state_;
    ArcherSkeletonBaseState* current_state_;
    ArcherSkeletonHurtState* ar_sk_hurt_state_;
};
