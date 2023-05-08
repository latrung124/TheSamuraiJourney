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