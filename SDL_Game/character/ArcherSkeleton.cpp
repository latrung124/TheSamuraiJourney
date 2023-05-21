#include "ArcherSkeleton.h"
#include "GameWorld/gameworld.h"
#include "archerskeletonstatemachine.h"
ArcherSkeleton::ArcherSkeleton() {
    x_pos_ = 300;
    y_pos_ = 600;
    width_ = 60;
    health_point_ = ARCHER_SKELETON_HP;
    ar_sk_velocity_x_ = 0;
    ar_sk_velocity_y_ = 0;
    is_facing_right_ = false;
    is_collision_ = false;
    sk_state_machine_ = new SkeletonStateMachine();
    health_border_rect_ = {x_pos_, y_pos_ + 50, WIDTH_HP_PROGRESS, HEIGHT_HP_PROGRESS};
    health_progress_rect_ = {x_pos_ + BORDER_PROGRESS_WIDTH, y_pos_ + 50 + BORDER_PROGRESS_WIDTH, WIDTH_HP_PROGRESS - BORDER_PROGRESS_WIDTH*2, HEIGHT_HP_PROGRESS - BORDER_PROGRESS_WIDTH*2};
}

ArcherSkeleton::ArcherSkeleton(int _x_pos, int _y_pos) {
    x_pos_ = _x_pos;
    y_pos_ = _y_pos;
    spawn_x_pos_ = _x_pos;
    spawn_y_pos_ = _y_pos;
    ar_sk_velocity_x_ = 0;
    ar_sk_velocity_y_ = 0;
    is_facing_right_ = false;
    is_collision_ = false;
    health_point_ = ARCHER_SKELETON_HP;
    sk_state_machine_ = new SkeletonStateMachine();
    health_border_rect_ = {x_pos_, y_pos_ + 50, WIDTH_HP_PROGRESS, HEIGHT_HP_PROGRESS};
    health_progress_rect_ = {x_pos_ + BORDER_PROGRESS_WIDTH, y_pos_ + 50 + BORDER_PROGRESS_WIDTH, WIDTH_HP_PROGRESS - BORDER_PROGRESS_WIDTH*2, HEIGHT_HP_PROGRESS - BORDER_PROGRESS_WIDTH*2};

}

ArcherSkeleton::~ArcherSkeleton() {
    if (sk_state_machine_ != nullptr) {
        delete sk_state_machine_;
        sk_state_machine_ = nullptr;
    }
}

SkeletonStateMachine* ArcherSkeleton::GetStateMachine() {
    return sk_state_machine_;
}


void ArcherSkeleton::StateAnimationUpdate() {
    if (sk_state_machine_ != nullptr) {
        sk_state_machine_->StateAnimationUpdate(this);
    }
}

int ArcherSkeleton::GetXPos() {
    return x_pos_;
}
int ArcherSkeleton::GetYPos() {
    return y_pos_;
}

int ArcherSkeleton::GetRightPos() {
    return x_pos_ + width_;
}

int ArcherSkeleton::GetLeftPos() {
    return x_pos_;
}

int ArcherSkeleton::GetTopPos() {
    return y_pos_;
}

int ArcherSkeleton::GetBottomPos() {
    return y_pos_ + game_define::kCharacterSize;
}

bool ArcherSkeleton::GetIsFacingRight() {
    return is_facing_right_;
}

void ArcherSkeleton::SetXPos(int _smr_velocity_x) {
    if (is_facing_right_) {
        if (x_pos_ <= WINDOW_WIDTH - game_define::kCharacterSize/2)
            x_pos_ += _smr_velocity_x;
    }
    else  {
        if (x_pos_ >= 0)
            x_pos_ -= _smr_velocity_x;
    }
}

void ArcherSkeleton::ChangedPosAfterMapChanged(int _x_pos) {
    x_pos_ += _x_pos;
}

void ArcherSkeleton::SetYPos(int _smr_velocity_y) {
    y_pos_ += _smr_velocity_y;
}

int ArcherSkeleton::GetVelocityX() {
    return ar_sk_velocity_x_;
}

int ArcherSkeleton::GetVelocityY() {
    return ar_sk_velocity_y_;
}

void ArcherSkeleton::SetIsFacingRight(bool _is_facing_right) {
    if (is_facing_right_ != _is_facing_right) {
        is_facing_right_ = _is_facing_right;
    }
}

void ArcherSkeleton::XPositionChanged() {
    SetXPos(ar_sk_velocity_x_);
    printf("%s x_pos: %d \n", __FUNCSIG__, x_pos_);
}

void ArcherSkeleton::SetHealthPoint(int _health_point) {
    int health_point = health_point_ - _health_point;
    health_point = health_point < 0 ? 0 : health_point;
    health_point_ = health_point;
}

int ArcherSkeleton::GetHealthPoint() {
    return health_point_;
}


void ArcherSkeleton::SetHealthProgressRect() {
    if (health_progress_rect_.w != GetHealthPoint()) {
        health_progress_rect_.w = GetHealthPoint();
    }
}

void ArcherSkeleton::SetIsCollision(bool _is_collision) {
    if (is_collision_ != _is_collision) {
        is_collision_ = _is_collision;
    }
}

bool ArcherSkeleton::GetIsCollision() {
    return is_collision_;
}

void ArcherSkeleton::HandleHurtEffect() {
    //handle hurt effect
}

void ArcherSkeleton::ShowHealthPoint() {
    health_border_rect_ = {x_pos_, y_pos_ + 50, WIDTH_HP_PROGRESS, HEIGHT_HP_PROGRESS};
    SDL_SetRenderDrawColor(GameWorld::Instance()->GetRenderer() , enemy_border_hp_color_.r, enemy_border_hp_color_.g, enemy_border_hp_color_.b, 0xFF);
    SDL_RenderDrawRect(GameWorld::Instance()->GetRenderer() , &health_border_rect_);
    health_progress_rect_ = {x_pos_ + BORDER_PROGRESS_WIDTH, y_pos_ + 50 + BORDER_PROGRESS_WIDTH, GetHealthPoint() == 0 ? 0 : GetHealthPoint() - BORDER_PROGRESS_WIDTH*2, HEIGHT_HP_PROGRESS - BORDER_PROGRESS_WIDTH*2};
    SDL_SetRenderDrawColor(GameWorld::Instance()->GetRenderer() , enemy_hp_color_.r, enemy_hp_color_.g, enemy_hp_color_.b, 0xFF);
    SDL_RenderFillRect(GameWorld::Instance()->GetRenderer(), &health_progress_rect_);
}

void ArcherSkeleton::NormalAttack() {
    // printf("ArcherSkeleton goes to the normal attack state! \n");
    // if (sk_state_machine_->SetState(sk_state_machine_->smr_normal_attack_state_)) {
    //     printf("ArcherSkeleton changed to attack state! \n");
    // }
    // else {
    //     printf("ArcherSkeleton can't change to attack state! \n");
    // }
}

void ArcherSkeleton::SpecialAttack() {
    // printf("ArcherSkeleton goes to the special attack state! \n");
    // if (sk_state_machine_->SetState(sk_state_machine_->smr_special_attack_state_)) {
    //     printf("ArcherSkeleton changed to special attack state! \n");
    // }
    // else {
    //     printf("ArcherSkeleton can't change to special attack state! \n");
    // }
}

void ArcherSkeleton::StrongAttack() {
    // printf("ArcherSkeleton goes to the strong attack state! \n");
    // if (sk_state_machine_->SetState(sk_state_machine_->smr_strong_attack_state_)) {
    //     printf("ArcherSkeleton changed to strong attack state! \n");
    // }
    // else {
    //     printf("ArcherSkeleton can't change to strong attack state! \n");
    // }
}

void ArcherSkeleton::Defend() {
    // printf("ArcherSkeleton goes to the defend state! \n");
    // if (sk_state_machine_->SetState(sk_state_machine_->smr_defend_state_)) {
    //     printf("ArcherSkeleton changed to defend state! \n");
    // }
    // else {
    //     printf("ArcherSkeleton can't change to defend state! \n");
    // }

}

void ArcherSkeleton::Idle() {
    printf("ArcherSkeleton goes to the idle state! \n");
    if (sk_state_machine_ != nullptr) {
        sk_state_machine_->SetState(sk_state_machine_->GetIdleState(), this);
    }
}

void ArcherSkeleton::Run() {

}

void ArcherSkeleton::Jump() {

}

void ArcherSkeleton::Walk() {
    // printf("ArcherSkeleton goes to the walk state! \n");
    // if (sk_state_machine_->current_state_ == sk_state_machine_->smr_walk_state_) {
    //     printf("ArcherSkeleton still in the walk state! \n");
    //     return;
    // }
    // if (sk_state_machine_->SetState(sk_state_machine_->smr_walk_state_)) {
    //     printf("ArcherSkeleton changed to walk state! \n");
    // }
    // else {
    //     printf("ArcherSkeleton can't change to walk state! \n");
    // }
}

void ArcherSkeleton::Hurt() {
    if (dynamic_cast<ArcherSkeletonHurtState*>(sk_state_machine_->GetCurrentState())) {
        return;
    }
    printf("ArcherSkeleton goes to the hurt state! \n");
    if (sk_state_machine_ != nullptr) {
        sk_state_machine_->SetState(sk_state_machine_->GetHurtState(), this);
    } else {
        printf("ArcherSkeleton can't go to the hurt state! \n");
    }
}

void ArcherSkeleton::Die() {

}

void ArcherSkeleton::StateAnimationDone() {
    printf("%s !", __FUNCSIG__);
    if (sk_state_machine_ != nullptr) {
        sk_state_machine_->SetState(sk_state_machine_->GetIdleState(), this);
    }
}