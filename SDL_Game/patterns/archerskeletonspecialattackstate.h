#pragma once
#include "baseState.h"

#define AR_SK_SPECIAL_ATTACK_FRAME_NUMBER 4
#define AR_SK_DIFF_LEFT_RIGHT_SPECIAL_ATTACK 50 // differ between the facing left and right
class GameWorld;
class ArcherSkeletonSpecialAttackState : public BaseState
{
public:
    ArcherSkeletonSpecialAttackState();
    virtual ~ArcherSkeletonSpecialAttackState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *ar_sk_special_attack_sprites_;
    SDL_Rect ar_sk_sprites_rect_[AR_SK_SPECIAL_ATTACK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
