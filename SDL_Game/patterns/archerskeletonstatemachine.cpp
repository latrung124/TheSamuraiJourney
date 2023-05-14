#include "archerskeletonstatemachine.h"
/*****************Skeleton State Machine******************/

SkeletonStateMachine::SkeletonStateMachine() {
    current_state_ = nullptr;
    ar_sk_idle_state_ = new ArcherSkeletonIdleState();
    ar_sk_hurt_state_ = new ArcherSkeletonHurtState();
}

SkeletonStateMachine::~SkeletonStateMachine() {
    if (current_state_ != nullptr) {
        delete current_state_;
        current_state_ = nullptr;
    }
    if (ar_sk_idle_state_ != nullptr) {
        delete ar_sk_idle_state_;
        ar_sk_idle_state_ = nullptr;
    }
    if (ar_sk_hurt_state_ != nullptr) {
        delete ar_sk_hurt_state_;
        ar_sk_hurt_state_ = nullptr;
    }
}

ArcherSkeletonBaseState* SkeletonStateMachine::GetCurrentState() {
    return current_state_;
}

ArcherSkeletonBaseState* SkeletonStateMachine::GetIdleState() {
    return ar_sk_idle_state_;
}

ArcherSkeletonBaseState* SkeletonStateMachine::GetHurtState() {
    return ar_sk_hurt_state_;
}

bool SkeletonStateMachine::SetState(ArcherSkeletonBaseState* _state, ArcherSkeleton* _ar_sk) {
    if (_state == nullptr) return false;

    _state->Exit(_ar_sk);
    current_state_ = _state;
    _state->Enter(_ar_sk);
    return true;
}

void SkeletonStateMachine::StateAnimationUpdate(ArcherSkeleton* _ar_sk) {
    if (current_state_ != nullptr) {
        current_state_->Update(_ar_sk);
    }
}

void SkeletonStateMachine::StateAnimationDone() {
    printf("%s \n", __FUNCSIG__);
}


/*****************Skeleton State Machine******************/