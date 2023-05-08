#pragma once
#include "archerskeletonbasestate.h"
#define AR_SK_HURT_FRAME_NUMBER 2
#define AR_SK_DIFF_HURT_SPRITES 55
class GameWorld;
class ArcherSkeletonHurtState : public ArcherSkeletonBaseState {
public:
    ArcherSkeletonHurtState();
    virtual ~ArcherSkeletonHurtState() override;
    virtual void Enter(ArcherSkeleton* _ar_sk) override;
    virtual void Update(ArcherSkeleton* _ar_sk) override;
    virtual void Exit(ArcherSkeleton* _ar_sk) override;

    bool InitializeState();
private:
    SDL_Texture* ar_sk_hurt_sprites_;
    SDL_Rect ar_sk_sprites_rect_[AR_SK_HURT_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};

