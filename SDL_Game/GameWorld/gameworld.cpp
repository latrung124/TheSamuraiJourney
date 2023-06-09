#include "gameworld.h"

static GameWorld* game_world_ = nullptr;
GameWorld::GameWorld() {
    sdl_window_ = nullptr;
    sdl_renderer_ = nullptr;
    background_texture_ = nullptr;
    compensation_texture_ = nullptr;

    start_of_original_background_ = 0;
    start_of_compensation_background_ = 0;
    end_of_original_background_ = WINDOW_WIDTH;
    end_of_compensation_background_ = 0;
    current_screen_ = 1;
}

GameWorld::~GameWorld() {
    if (game_world_ != nullptr) {
        delete game_world_;
        game_world_ = nullptr;
    }
}

GameWorld* GameWorld::Instance() {
    if (game_world_ == nullptr) {
        game_world_ = new GameWorld();
    }
    return game_world_;
}

SDL_Renderer* GameWorld::GetRenderer() {
    return sdl_renderer_;
}

bool GameWorld::InitializeTheWindow()
{
    bool isSuccess = false;
    
    //init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(" %s () SDL could not initialize! SDL_Error %s\n", __FUNCSIG__ , SDL_GetError());
        return isSuccess;
    }
    else {
        //create window
        sdl_window_ = SDL_CreateWindow(game_define::kGameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (sdl_window_ == nullptr) {
            printf(" %s () Can't create the window! SDL_Error: %s\n", __FUNCSIG__ , SDL_GetError());
        }
        else {
            //create renderer
            sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (sdl_renderer_ == nullptr) {
                printf(" %s () Can't create the renderer! SDL_Error: %s\n", __FUNCSIG__ , SDL_GetError());
                SDL_DestroyWindow(sdl_window_);
            }
            printf(" %s () Create render successfully!");
            isSuccess = true;
        }
    }
    return isSuccess;
}

bool GameWorld::InitializeTheImageLoader() {
    //Initialize PNG loading
    bool isSuccess = false;
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: %s\n"<< __FUNCSIG__ << IMG_GetError() << std::endl;
        return isSuccess;
    }
    isSuccess = true;
    return isSuccess;
}

bool GameWorld::InitializeTheBackground() {
    bool isSuccess = false;
    //load background image
    //std::string background_path = "D:/workspace/SDLproject/Demo_Game/SDL_Game/asset/map/Background.png";
    std::string background_path = BACKGROUND_PATH;
    if (sdl_renderer_ != nullptr) {
        background_texture_ = CommonObject::Instance()->ImageTexture( background_path, sdl_renderer_);
        if (background_texture_ != nullptr)
        isSuccess = true;
        else {
            printf(" %s () The background texture is nullptr!\n");
        }
        compensation_texture_ = background_texture_;
    }
    else {
        printf(" %s () The renderer is nullptr for somereasone\n");
    }
    return isSuccess;
}

bool GameWorld::InitializeTheGameWorld() {
    bool isSuccess = false;
    if (InitializeTheWindow()) {
        if (InitializeTheBackground()) {
            //set rectangle for the background
            original_background_rect_;
            original_background_rect_.x = 0;
            original_background_rect_.y = 0;
            original_background_rect_.w = WINDOW_WIDTH;
            original_background_rect_.h = WINDOW_HEIGHT;

            compensation_background_rect_.x = WINDOW_WIDTH;
            compensation_background_rect_.y = 0;
            compensation_background_rect_.w = WINDOW_WIDTH;
            compensation_background_rect_.h = WINDOW_HEIGHT;

            //set the background as the initial renderer background
            SDL_RenderClear(sdl_renderer_);
            SDL_RenderCopy(sdl_renderer_, background_texture_, nullptr, &original_background_rect_);
            SDL_RenderPresent(sdl_renderer_);
            isSuccess = true;
        }
        else {
            //failed to load the background image
        }
    }
    else {
        //failed to load the window
    }

    return isSuccess;
}

void GameWorld::CleanUp() {
    SDL_DestroyTexture(background_texture_);
    SDL_DestroyTexture(compensation_texture_);
    SDL_DestroyRenderer(sdl_renderer_);
    SDL_DestroyWindow(sdl_window_);
    IMG_Quit();
    SDL_Quit();
}

bool GameWorld::InitializeSamurai() {
    bool isSuccess = false;
    printf(" %s \n", __FUNCSIG__);
    //idle state is on
    Samurai::Instance()->Idle();
    isSuccess = true;
    return isSuccess;
}

bool GameWorld::InitializeTheEnemies() {
    //init archer skeleton
    printf("%s \n", __FUNCSIG__);
    for (int i = 0; i < AR_SK_NUMBER; ++i) {
        auto ar_sk = CharacterPool::Instance()->GetArcherSkeleton();
        if (ar_sk == nullptr) return false;
        ar_sk_enemies_.push_back(ar_sk);
    }

    //run all archer skeleton in the idle state
    for (int i = 0; i < ar_sk_enemies_.size();++i) {
        if (ar_sk_enemies_[i] != nullptr) {
            ar_sk_enemies_[i]->Idle();
            ar_sk_enemies_[i]->ShowHealthPoint();
        }
    }
    return true;
}

void GameWorld::EnemiesAnimationUpdate() {
    for (int i = 0; i < ar_sk_enemies_.size(); ++i) {
        if (ar_sk_enemies_[i] != nullptr) {
            //check collision
            printf("samurai x: %d, y: %d \n", Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos());
            printf("skeleton x: %d, y: %d \n", ar_sk_enemies_[i]->GetXPos(), ar_sk_enemies_[i]->GetYPos());
            if (GameMechanismController::Instance()->ColisionCheck(Samurai::Instance(), ar_sk_enemies_[i])) {
                printf("collision !!!\n");
            } else {
                printf("no collision !!!\n");
            }
            ar_sk_enemies_[i]->ShowHealthPoint();
            ar_sk_enemies_[i]->StateAnimationUpdate();
        }
    }
}


void GameWorld::SamuraiAnimationUpdate() {
    Samurai::Instance()->UpdateAnimation();
}

void GameWorld::RenderTheBackground() {
    //get the offset
    if (dynamic_cast<SamuraiWalkState*>(Samurai::Instance()->smr_state_machine_->current_state_)
    || dynamic_cast<SamuraiRunState*>(Samurai::Instance()->smr_state_machine_->current_state_)) {
        GameMechanismController::Instance()->UpdatePositionForSamurai(Samurai::Instance());
        int16_t background_offset = GameMechanismController::Instance()->GetBackgroundOffset();
        if (Samurai::Instance()->GetIsFacingRight()) {
            if (GameMechanismController::Instance()->GetRealXPosOfMap() < MAP_WIDTH) {
                //the map moves to left
                GameMechanismController::Instance()->IncreaseRealXPosOfMap(background_offset);
                original_background_rect_.x = original_background_rect_.x - background_offset;
                compensation_background_rect_.x -= background_offset;
                if (original_background_rect_.x == (-1) * WINDOW_WIDTH) {
                    // reset the position of the background after it met the end
                    original_background_rect_.x = 0;
                    compensation_background_rect_.x = WINDOW_WIDTH;
                }
            }
        } else {
            if (GameMechanismController::Instance()->GetRealXPosOfMap() > 0) {
                //the map moves to right
                GameMechanismController::Instance()->DecreaseRealXPosOfMap(background_offset);
                if (original_background_rect_.x == 0) {
                    original_background_rect_.x -= WINDOW_WIDTH;
                    compensation_background_rect_.x = 0;
                }
                original_background_rect_.x += background_offset;
                compensation_background_rect_.x += background_offset;
            }
        }

    } else {
        GameMechanismController::Instance()->SetIsMapMoving(false);
        GameMechanismController::Instance()->SetBackgroundOffset(0);
    }

    printf("original background x: %d, compensation background x: %d \n", original_background_rect_.x, compensation_background_rect_.x);
    //render the origin background and the compennsation background
    SDL_RenderCopy(sdl_renderer_, background_texture_, nullptr, &original_background_rect_);
    SDL_RenderCopy(sdl_renderer_, background_texture_, nullptr, &compensation_background_rect_);
}

void GameWorld::EventLoop() {
    //Init the game loop event
    SDL_Event game_event;
    bool isQuit = false;
    SDL_Timer fps_timer;
    int counted_frames = 0;
    Uint32 time_per_frame = 1000 / FPS;
    while (!isQuit) {
        fps_timer.Start();
        while (SDL_PollEvent(&game_event) != 0) {
            if (game_event.type == SDL_QUIT) {
                isQuit = true;
            } else if (game_event.type == SDL_KEYDOWN){
                KeyboardController::Instance()->HandleKeyDownEvent(game_event.key.keysym.sym);
            } else if (game_event.type == SDL_KEYUP) {
                KeyboardController::Instance()->HandleKeyUpEvent(game_event.key.keysym.sym);
            }
        }
        SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 255);
        SDL_RenderClear(sdl_renderer_);

        RenderTheBackground();
        SamuraiAnimationUpdate();
        GameMechanismController::Instance()->UpdatePositionOfEnemies(ar_sk_enemies_);
        EnemiesAnimationUpdate();
        SDL_RenderPresent(sdl_renderer_);

        //FPS calculator & capping the frame rate
        Uint32 real_time_frame = fps_timer.GetTicks();
        printf("real time: %lu \n", (unsigned long)real_time_frame);
        if (real_time_frame < time_per_frame) {
            Uint32 delay_time = time_per_frame - real_time_frame;
            printf("delay time: %lu \n", (unsigned long)delay_time);
            if (delay_time >= 0) {
                SDL_Delay(delay_time);
            }
        } else {
            Uint32 delay_time = real_time_frame - time_per_frame;
            printf("delay time: %lu \n", (unsigned long)delay_time);
            if (delay_time >= 0) {
                SDL_Delay(delay_time);
            }
        }
    }
}

void GameWorld::RunningTheGame() {
    if (InitializeTheGameWorld()) {
        printf(" %s () game world is initialized successfully\n", __FUNCSIG__);
        if (InitializeSamurai()) {
            printf(" %s () main character samurai is initialized successfully!\n", __FUNCSIG__);
            if (InitializeTheEnemies()) {
                printf(" %s () enemies initialized successfully!\n", __FUNCSIG__);
            } else {
                printf(" %s () enemies initialized failed!\n", __FUNCSIG__);
            }
        }
        else {
            printf(" %s () main character samurai can't be initialized!\n", __FUNCSIG__);
        }

        EventLoop();
    }
}