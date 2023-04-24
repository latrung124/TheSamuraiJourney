#pragma once
#include "baseState.h"

#define SPECIAL_ATTACK_FRAME_NUMBER 4
#define DIFF_LEFT_RIGHT_SPECIAL_ATTACK 50 // differ between the facing left and right
class GameWorld;
class SamuraiSpecialAttackState : public BaseState
{
public:
    SamuraiSpecialAttackState();
    virtual ~SamuraiSpecialAttackState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_special_attack_sprites_;
    SDL_Rect smr_sprites_rect_[SPECIAL_ATTACK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
