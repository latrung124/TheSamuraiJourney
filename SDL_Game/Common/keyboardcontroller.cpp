#include "Common/keyboardcontroller.h"

static KeyboardController* keyboard_controller_ = nullptr;
KeyboardController::KeyboardController() {

}

KeyboardController::~KeyboardController() {
    if (keyboard_controller_ != nullptr) {
        delete keyboard_controller_;
        keyboard_controller_ = nullptr;
    }
}

KeyboardController* KeyboardController::Instance() {
    if (keyboard_controller_ == nullptr) {
        keyboard_controller_ = new KeyboardController();
    }
    return keyboard_controller_;
}

void KeyboardController::HandleKeyDownEvent(SDL_Keycode _event_type) {
    switch (_event_type)
    {
    case SDLK_UP: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_LEFT: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->SetIsFacingRight(false);

        Samurai::Instance()->Walk();
        break;
    }
    case SDLK_RIGHT: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->SetIsFacingRight(true);

        Samurai::Instance()->Walk();
        break;
    }
    case SDLK_f: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_q: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->NormalAttack();
        break;
    }
    case SDLK_w: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->StrongAttack();
        break;
    }
    case SDLK_e: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->SpecialAttack();
        break;
    }
    case SDLK_d: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->Defend();
        break;
    }
    default:
        break;
    }
}


void KeyboardController::HandleKeyUpEvent(SDL_Keycode _event_type) {
    switch (_event_type)
    {
    case SDLK_UP: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    //jump
    case SDLK_LEFT: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->smr_state_machine_->StateAnimationDone();
        break;
    }
    case SDLK_RIGHT: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->smr_state_machine_->StateAnimationDone();
        break;
    }
    case SDLK_f: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_q: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_w: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_e: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        break;
    }
    case SDLK_d: {
        printf("%s key event:%d \n", __FUNCSIG__, (int)_event_type);
        Samurai::Instance()->smr_state_machine_->StateAnimationDone();
        break;
    }
    default:
        break;
    }

}