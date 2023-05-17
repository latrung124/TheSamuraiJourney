#include "samurai.h"

static Samurai* samurai_ = nullptr;
Samurai::Samurai() {
    x_pos_ = game_define::kXSamuraiInitPos;
    y_pos_ = game_define::kYSamuraiInitPos;

    smr_velocity_x_ = game_define::kSmrWalkVelocity;
    smr_velocity_y_ = 1;
    smr_state_machine_ = new SamuraiStateMachine();
    is_facing_right_ = true;
}

Samurai::~Samurai() {
    if (smr_state_machine_ != nullptr) {
        delete smr_state_machine_;
        smr_state_machine_ = nullptr;
    }
    if (samurai_ != nullptr) {
        delete samurai_;
        samurai_ = nullptr;
    }
}

Samurai* Samurai::Instance() {
    if (samurai_ == nullptr) {
        samurai_ = new Samurai();
    }
    return samurai_;
}

int Samurai::GetXPos() {
    return x_pos_;
}
int Samurai::GetYPos() {
    return y_pos_;
}

SamuraiStateMachine* Samurai::GetSamuraiStateMachine() {
    return smr_state_machine_;
}

bool Samurai::GetIsFacingRight() {
    return is_facing_right_;
}

void Samurai::SetXPos(int _smr_velocity_x) {
    if (is_facing_right_) {
        if (x_pos_ <= WINDOW_WIDTH - game_define::kCharacterSize/2)
            x_pos_ += _smr_velocity_x;
    }
    else  {
        if (x_pos_ > 0)
            x_pos_ -= _smr_velocity_x;
    }
}
void Samurai::SetYPos(int _smr_velocity_y) {
    y_pos_ += _smr_velocity_y;
}

int Samurai::GetVelocityX() {
    return smr_velocity_x_;
}

int Samurai::GetVelocityY() {
    return smr_velocity_y_;
}

void Samurai::SetIsFacingRight(bool _is_facing_right) {
    if (is_facing_right_ != _is_facing_right) {
        is_facing_right_ = _is_facing_right;
    }
}

void Samurai::XPositionChanged() {
    SetXPos(smr_velocity_x_);
    printf("%s x_pos: %d \n", __FUNCSIG__, x_pos_);
}


void Samurai::HandleXPosWhenItMovesOutTheMap(int& _current_x_pos) {
    if (_current_x_pos > WINDOW_WIDTH - game_define::kCharacterSize) _current_x_pos = WINDOW_WIDTH - game_define::kCharacterSize - 100;
    if (_current_x_pos < 0) _current_x_pos = 0;
}

void Samurai::UpdateAnimation() {
    if (smr_state_machine_->current_state_ != nullptr)
    smr_state_machine_->current_state_->Update();
}

void Samurai::NormalAttack() {
    printf("Samurai goes to the normal attack state! \n");
    if (smr_state_machine_->SetState(smr_state_machine_->smr_normal_attack_state_)) {
        printf("Samurai changed to attack state! \n");
    }
    else {
        printf("Samurai can't change to attack state! \n");
    }
}

void Samurai::SpecialAttack() {
    printf("Samurai goes to the special attack state! \n");
    if (smr_state_machine_->SetState(smr_state_machine_->smr_special_attack_state_)) {
        printf("Samurai changed to special attack state! \n");
    }
    else {
        printf("Samurai can't change to special attack state! \n");
    }
}

void Samurai::StrongAttack() {
    printf("Samurai goes to the strong attack state! \n");
    if (smr_state_machine_->SetState(smr_state_machine_->smr_strong_attack_state_)) {
        printf("Samurai changed to strong attack state! \n");
    }
    else {
        printf("Samurai can't change to strong attack state! \n");
    }
}

void Samurai::Defend() {
    printf("Samurai goes to the defend state! \n");
    if (smr_state_machine_->SetState(smr_state_machine_->smr_defend_state_)) {
        printf("Samurai changed to defend state! \n");
    }
    else {
        printf("Samurai can't change to defend state! \n");
    }

}

void Samurai::Idle() {
    printf("Samurai goes to the idle state! \n");
    if (dynamic_cast<SamuraiIdleState*>(smr_state_machine_->current_state_)) {
        if (smr_state_machine_->SetState(smr_state_machine_->current_state_)) {
            printf("Samurai changed to idle state! \n");
        }
        else {
            printf("Samurai can't change to idle state! \n");
        }
    }
}

void Samurai::Run() {

}

void Samurai::Jump() {

}

void Samurai::Walk() {
    printf("Samurai goes to the walk state! \n");
    if (smr_state_machine_->current_state_ == smr_state_machine_->smr_walk_state_) {
        printf("Samurai still in the walk state! \n");
        return;
    }
    if (smr_state_machine_->SetState(smr_state_machine_->smr_walk_state_)) {
        printf("Samurai changed to walk state! \n");
    }
    else {
        printf("Samurai can't change to walk state! \n");
    }
}

void Samurai::Hurt() {

}

void Samurai::Die() {

}

void Samurai::AddObserver(Observer* _observer) {

}

void Samurai::RemoveObserser(Observer* _observer) {

}

void Samurai::NotifyObservers() {

}

int Samurai::GetTopPos() {
    return y_pos_;
}

int Samurai::GetBottomPos() {
    return y_pos_ + game_define::kCharacterSize;
}

int Samurai::GetLeftPos() {
    return x_pos_;
}

int Samurai::GetRightPos() {
    return x_pos_ + game_define::kCharacterSize;
}