#pragma once
#include "baseState.h"
#define AR_SK_NORMAL_ATTACK_FRAME_NUMBER 5
#define AR_SK_DIFF_NORMAL_ATTACK_SPRITES 50
class GameWorld;
class ArcherSkeletonNormalAttackState : public BaseState{
public:
    ArcherSkeletonNormalAttackState();
    virtual ~ArcherSkeletonNormalAttackState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture* ar_sk_normal_attack_sprites_;
    SDL_Rect ar_sk_sprites_rect_[AR_SK_NORMAL_ATTACK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};

