#pragma once
#include "commonobject.h"

class SDL_Timer {
public:
    SDL_Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();

    Uint32 GetTicks();
    bool IsStarted();
    bool IsPaused();

private:
    Uint32 start_ticks_;
    Uint32 pause_ticks_;
    bool is_paused_;
    bool is_started_;
};
