#pragma once
#include "baseState.h"

#define DEFEND_FRAME_NUMBER 2
#define DIFF_LEFT_RIGHT_DEFEND 50 // differ between the facing left and right
class GameWorld;
class SamuraiDefendState : public BaseState
{
public:
    SamuraiDefendState();
    virtual ~SamuraiDefendState() override;
    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

    bool InitializeState();
private:
    SDL_Texture *smr_defend_sprites_;
    SDL_Rect smr_sprites_rect_[DEFEND_FRAME_NUMBER];
    SDL_Rect destination_rect_;
    unsigned int current_frame_;
    bool is_mode_on_;
};
