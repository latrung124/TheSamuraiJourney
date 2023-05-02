#pragma once
#include "baseState.h"
#define AR_SK_WALK_FRAME_NUMBER 8
#define AR_SK_DIFF_WALK_SPRITES 50
class GameWorld;
class ArcherSkeletonWalkState : public BaseState{
public:
    ArcherSkeletonWalkState();
    virtual ~ArcherSkeletonWalkState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture* ar_sk_walk_sprites_;
    SDL_Rect ar_sk_sprites_rect_[AR_SK_WALK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};


