#pragma once
#include "baseState.h"

#define STRONG_ATTACK_FRAME_NUMBER 5
#define DIFF_STRONG_ATTACK_SPRITES 50 // differ between the facing left and right
class GameWorld;
class SamuraiStrongAttackState : public BaseState
{
public:
    SamuraiStrongAttackState();
    virtual ~SamuraiStrongAttackState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_strong_attack_sprites_;
    SDL_Rect smr_sprites_rect_[STRONG_ATTACK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};