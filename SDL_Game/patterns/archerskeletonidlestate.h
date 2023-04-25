#pragma once
#include "baseState.h"
#define AR_SK_IDLE_FRAME_NUMBER 7
#define AR_SK_DIFF_IDLE_SPRITES 55
class GameWorld;
class ArcherSkeletonIdleState : public BaseState{
public:
    ArcherSkeletonIdleState();
    virtual ~ArcherSkeletonIdleState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture* ar_sk_idle_sprites_;
    SDL_Rect ar_sk_sprites_rect_[AR_SK_IDLE_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
