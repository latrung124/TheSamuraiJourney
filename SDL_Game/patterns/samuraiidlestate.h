#pragma once

#include "baseState.h"
#define IDLE_FRAME_NUMBER 6
#define DIFF_IDLE_SPRITES 55
class GameWorld;
class SamuraiIdleState : public BaseState{
public:
    SamuraiIdleState();
    virtual ~SamuraiIdleState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture* smr_idle_sprites_;
    SDL_Rect smr_sprites_rect_[IDLE_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
