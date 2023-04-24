#pragma once
#define BACKGROUND_PATH "..\\asset\\map\\Background.png"
#define SAMURAI_IDLE_PATH "..\\asset\\character\\samurai\\Idle.png"
#define SAMURAI_RUN_PATH "..\\asset\\character\\samurai\\Run.png"
#define SAMURAI_WALK_PATH "..\\asset\\character\\samurai\\Walk.png"
#define SAMURAI_HURT_PATH "..\\asset\\character\\samurai\\Hurt.png"
#define SAMURAI_JUMP_PATH "..\\asset\\character\\samurai\\Jump.png"
#define SAMURAI_DEFEND_PATH "..\\asset\\character\\samurai\\Protection.png"
#define SAMURAI_DEAD_PATH "..\\asset\\character\\samurai\\Dead.png"
#define SAMURAI_NORMAL_ATTACK_PATH "..\\asset\\character\\samurai\\Attack_1.png"
#define SAMURAI_STRONG_ATTACK_PATH "..\\asset\\character\\samurai\\Attack_2.png"
#define SAMURAI_SPECIAL_ATTACK_PATH "..\\asset\\character\\samurai\\Attack_3.png"
#define GAME_MOVING_OFFSET 2
#define WINDOW_WIDTH 928
#define WINDOW_HEIGHT 793
#define ANIMATION_SPEED 100 //100 milliseconds
#define FPS 60

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace game_define {
    static const std::string kGameName = "The Samurai's Journey";
    static const int kCharacterSize = 128; //pixels
    const int kXSamuraiInitPos = 50;
    const int kYSamuraiInitPos = 600;

    static uint32_t kLastUpdateTime = 0;
    static const int kSmrMaxVelocity = 10;
    static const int kSmrWalkVelocity = 1;

    enum KeyPressSurfaces{
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
}

class CommonObject {
public:
    CommonObject();
    ~CommonObject();

    static CommonObject* Instance();

    SDL_Texture* ImageTexture(std::string& _path, SDL_Renderer* _renderer);
};
