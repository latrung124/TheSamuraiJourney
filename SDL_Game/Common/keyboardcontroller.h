#pragma once

#include <SDL.h>
#include "character/samurai.h"
#include <iostream>

class KeyboardController {
    public:
    KeyboardController();
    ~KeyboardController();
    static KeyboardController* Instance();
    void HandleKeyDownEvent(SDL_Keycode _event_type);
    void HandleKeyUpEvent(SDL_Keycode _event_type);
    private:
    bool is_f_pressed_;
};

