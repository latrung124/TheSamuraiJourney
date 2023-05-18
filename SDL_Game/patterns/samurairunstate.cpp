#include "samurairunstate.h"
#include "GameWorld/gameworld.h"
SamuraiRunState::SamuraiRunState() {
    smr_run_sprites_ = nullptr;
    is_mode_on_ = false;
    is_facing_right_ = true;
    if (!InitializeState()) {
        printf("%s init run state failed!\n", __FUNCSIG__);
    }
}

SamuraiRunState::~SamuraiRunState() {
    SDL_DestroyTexture(smr_run_sprites_);
}

bool SamuraiRunState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_run_image_path = SAMURAI_RUN_PATH;
    smr_run_sprites_ = CommonObject::Instance()->ImageTexture(smr_run_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_run_sprites_ == nullptr) {
        printf("%s () Failed to load the normal texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[RUN_FRAME_NUMBER];
    for (int i = 0; i < RUN_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiRunState::Enter() {
    if (is_mode_on_) {
        printf("%s skip cause the user keep press the button!", __FUNCSIG__);
        return;
    }
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_run_sprites_ == nullptr) {
        printf("%s run sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right_ = Samurai::Instance()->GetIsFacingRight();
    Samurai::Instance()->SetVelocityX(game_define::kSmrRunVelocity);

    //cause the samurai run sprites has a different about 20 px in the positive x position
    // so need to calculate the x, y pos of the samurai when he walks
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_RUN_SPRITES) ? DIFF_RUN_SPRITES : 0;
    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_run_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }
    destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_run_sprites_, &current_frame_rect, &destination_rect_);

}

void SamuraiRunState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    if (smr_run_sprites_ == nullptr) {
        printf("%s () walk attack sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/RUN_FRAME_NUMBER];
    printf("%s samurai x_pos : %d, y_pos: %d", __FUNCSIG__, Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos());
    //cause the samurai walk sprites has a different about 20 px in the positive x position
    //so need to calculate the x, y pos of the samurai when he walks
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_RUN_SPRITES) ? DIFF_RUN_SPRITES : 0;
    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_run_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_run_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/RUN_FRAME_NUMBER >= RUN_FRAME_NUMBER) {
        current_frame_ = 0;
    }
}

void SamuraiRunState::Exit() {
    is_mode_on_ = false;
}