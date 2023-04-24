#pragma once
#include "baseState.h"

#define NORMAL_ATTACK_FRAME_NUMBER 4
#define DIFF_LEFT_RIGHT_NORMAL_ATTACK 30
class GameWorld;
class SamuraiNormalAttackState : public BaseState
{
public:
    SamuraiNormalAttackState();
    virtual ~SamuraiNormalAttackState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_normal_attack_sprites_;
    SDL_Rect smr_sprites_rect_[NORMAL_ATTACK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};