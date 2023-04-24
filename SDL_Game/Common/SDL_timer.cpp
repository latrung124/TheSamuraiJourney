#include "SDL_timer.h"

SDL_Timer::SDL_Timer() {
    start_ticks_ = 0;
    pause_ticks_ = 0;

    is_started_ = false;
    is_paused_ = false;
}

void SDL_Timer::Start() {
    //start timer
    is_started_ = true;
    is_paused_ = false;

    start_ticks_ = SDL_GetTicks();
    pause_ticks_ = 0;
}

void SDL_Timer::Stop() {
    is_started_ = false;
    is_paused_ = false;

    start_ticks_ = 0;
    pause_ticks_ = 0;
}


void SDL_Timer::Pause() {
    //if timer is running and isn't already paused
    if (!is_paused_ && is_started_) {
        is_paused_ = true;
        pause_ticks_ = SDL_GetTicks() - start_ticks_;
        start_ticks_ = 0;
    }
}

void SDL_Timer::Unpause() {
    if (is_started_ && is_paused_) {
        is_paused_ = false;
        start_ticks_ = SDL_GetTicks() - pause_ticks_;
        pause_ticks_ = 0;
    }
}

Uint32 SDL_Timer::GetTicks() {
    Uint32 time = 0;
    if (is_started_) {
        if (is_paused_) {
            time = pause_ticks_;
        }
        else {
            time = SDL_GetTicks() - start_ticks_;
        }
    }
    return time;
}

bool SDL_Timer::IsStarted() {
    return is_started_;
}

bool SDL_Timer::IsPaused() {
    return is_paused_;
}