#pragma once
#include "baseState.h"

#define RUN_FRAME_NUMBER 8
#define DIFF_RUN_SPRITES 30 // differ between the walk sprites in the facing left and right
class GameWorld;
class SamuraiRunState : public BaseState
{
public:
    SamuraiRunState();
    virtual ~SamuraiRunState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_run_sprites_;
    SDL_Rect smr_sprites_rect_[RUN_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
