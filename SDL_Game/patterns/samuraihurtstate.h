#pragma once
#include "baseState.h"

#define HURT_FRAME_NUMBER 3
#define DIFF_HURT 30
class GameWorld;
class SamuraiHurtState : public BaseState
{
public:
    SamuraiHurtState();
    virtual ~SamuraiHurtState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_hurt_sprites_;
    SDL_Rect smr_sprites_rect_[HURT_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
