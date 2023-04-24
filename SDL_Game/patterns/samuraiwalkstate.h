#pragma once
#include "baseState.h"

#define WALK_FRAME_NUMBER 9
#define DIFF_WALK_SPRITES 30 // differ between the walk sprites in the facing left and right
class GameWorld;
class SamuraiWalkState : public BaseState
{
public:
    SamuraiWalkState();
    virtual ~SamuraiWalkState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_walk_sprites_;
    SDL_Rect smr_sprites_rect_[WALK_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};