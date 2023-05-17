#pragma once
#include "Common/commonobject.h"
#include <thread>
#include "Common/SDL_timer.h"
#include "character/samurai.h"
#include "Common/keyboardcontroller.h"
#include "gameobjectpool.h"
#include "Controller/gamemechanismcontroller.h"
class GameWorld {

public:
    GameWorld();
    ~GameWorld();

    static GameWorld* Instance();
    bool InitializeTheWindow();
    bool InitializeTheImageLoader();
    bool InitializeTheBackground();
    bool InitializeTheGameWorld();
    void CleanUp();

    bool InitializeSamurai();
    bool InitializeTheEnemies();
    void EventLoop();
    void RenderTheBackground();
    void EnemiesAnimationUpdate();
    void SamuraiAnimationUpdate();

    void RunningTheGame();
    SDL_Renderer* GetRenderer();

    SDL_Renderer* sdl_renderer_;

    std::vector<std::shared_ptr<ArcherSkeleton>> ar_sk_enemies_;
private:
    SDL_Window* sdl_window_;
    SDL_Texture* background_texture_;
    SDL_Texture* compensation_texture_;
    SDL_Rect  original_background_rect_;
    SDL_Rect compensation_background_rect_;
    int16_t start_of_original_background_;
    int16_t end_of_original_background_;
    int16_t start_of_compensation_background_;
    int16_t end_of_compensation_background_;
    int16_t current_screen_;
};
