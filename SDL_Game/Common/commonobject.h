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

//skeleton sprites path
#define ARCHER_SKELETON_IDLE_PATH "..\\asset\\character\\archer_skeleton\\Idle.png"
#define ARCHER_SKELETON_NORMAL_ATTACK_PATH "..\\asset\\character\\archer_skeleton\\Attack_1.png"
#define ARCHER_SKELETON_SPECIAL_ATTACK_PATH "..\\asset\\character\\archer_skeleton\\Attack_2.png"
#define ARCHER_SKELETON_STRONG_PATH "..\\asset\\character\\archer_skeleton\\Attack_3.png"
#define ARCHER_SKELETON_DEAD_PATH "..\\asset\\character\\archer_skeleton\\Dead.png"
#define ARCHER_SKELETON_WALK_PATH "..\\asset\\character\\archer_skeleton\\Walk.png"
#define ARCHER_SKELETON_NORMAL_SHOT_PATH "..\\asset\\character\\archer_skeleton\\Shot_1.png"
#define ARCHER_SKELETON_SPECIAL_SHOT_PATH "..\\asset\\character\\archer_skeleton\\Shot_2.png"
#define ARCHER_SKELETON_HURT_PATH "..\\asset\\character\\archer_skeleton\\Hurt.png"

//enemies statistics
#define AR_SK_NUMBER 3
#define LAND_Y 600
#define SPAWN_DOWN_OFFSET 1
#define GUARD_DISTANCE 50

//game visualization
#define MAX_SCREEN_OF_FIRST_SCENE 5
#define GAME_MOVING_OFFSET 1
#define WINDOW_WIDTH 928
#define MAP_WIDTH WINDOW_WIDTH*5
#define WINDOW_HEIGHT 793
#define ANIMATION_SPEED 100 //100 milliseconds
#define FPS 60

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace game_define {
    static const std::string kGameName = "The Samurai's Journey";
    static const int kCharacterSize = 128; //pixels
    const int kXSamuraiInitPos = 0;
    const int kYSamuraiInitPos = 600;

    static uint32_t kLastUpdateTime = 0;
    static const int kSmrMaxVelocity = 10;
    static const int kSmrWalkVelocity = 1;
    static const int kSmrRunVelocity = 2;
    static const int kSpawnArcherSkeletonXPos[AR_SK_NUMBER] = {300, 600, 900};

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
