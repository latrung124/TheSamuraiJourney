#include "statemachine.h"
#include "character/ArcherSkeleton.h"
SamuraiStateMachine::SamuraiStateMachine() {
    current_state_ = nullptr;
    smr_idle_state_ = new SamuraiIdleState();
    current_state_ = smr_idle_state_;
    smr_normal_attack_state_ = new SamuraiNormalAttackState();
    smr_strong_attack_state_ = new SamuraiStrongAttackState();
    smr_special_attack_state_ = new SamuraiSpecialAttackState();
    smr_defend_state_ = new SamuraiDefendState();
    smr_walk_state_ = new SamuraiWalkState();
}

SamuraiStateMachine::~SamuraiStateMachine() {
    if (smr_idle_state_ != nullptr) {
        delete smr_idle_state_;
        smr_idle_state_ = nullptr;
    }
    if (smr_normal_attack_state_ != nullptr) {
        delete smr_normal_attack_state_;
        smr_normal_attack_state_ = nullptr;
    }
    if (smr_strong_attack_state_ != nullptr) {
        delete smr_strong_attack_state_;
        smr_strong_attack_state_ = nullptr;
    }
    if (smr_special_attack_state_ != nullptr) {
        delete smr_special_attack_state_;
        smr_special_attack_state_ = nullptr;
    }
    if (smr_defend_state_ != nullptr) {
        delete smr_defend_state_;
        smr_defend_state_ = nullptr;
    }

}

bool SamuraiStateMachine::SetState(BaseState* _state) {
    if (_state == nullptr) return false;

    _state->Exit();
    current_state_ = _state;
    _state->Enter();
    return true;
}

void SamuraiStateMachine::StateAnimationDone() {
    SetState(smr_idle_state_);
}

/*****************Skeleton State Machine******************/

SkeletonStateMachine::SkeletonStateMachine(ArcherSkeleton* _ar_sk) {
    current_state_ = nullptr;
    ar_sk_idle_state_ = new ArcherSkeletonIdleState();
    current_state_ = ar_sk_idle_state_;
    current_state_->x_pos_ = _ar_sk->GetXPos();
    current_state_->y_pos_ = _ar_sk->GetYPos();
    current_state_->is_facing_right_ = _ar_sk->GetIsFacingRight();
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
}

bool SkeletonStateMachine::SetState(BaseState* _state) {
    if (_state == nullptr) return false;

    _state->Exit();
    current_state_ = _state;
    _state->Enter();
    return true;
}

void SkeletonStateMachine::StateAnimationUpdate(std::shared_ptr<ArcherSkeleton>& _ar_sk) {
    if (current_state_ != nullptr) {
        current_state_->x_pos_ = _ar_sk->GetXPos();
        current_state_->y_pos_ = _ar_sk->GetYPos();
        current_state_->is_facing_right_ = _ar_sk->GetIsFacingRight();
        current_state_->Update();
    }
}

void SkeletonStateMachine::StateAnimationDone() {
    SetState(ar_sk_idle_state_);
}


/*****************Skeleton State Machine******************/