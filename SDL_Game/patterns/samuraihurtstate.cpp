#include "samuraihurtstate.h"
#include "GameWorld/gameworld.h"
SamuraiHurtState::SamuraiHurtState() {
    smr_hurt_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init hurt state failed!\n", __FUNCSIG__);
    }
}

SamuraiHurtState::~SamuraiHurtState() {
    SDL_DestroyTexture(smr_hurt_sprites_);
}

bool SamuraiHurtState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_hurt_image_path = SAMURAI_HURT_PATH;
    smr_hurt_sprites_ = CommonObject::Instance()->ImageTexture(smr_hurt_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_hurt_sprites_ == nullptr) {
        printf("%s () Failed to load the normal texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[HURT_FRAME_NUMBER];
    for (int i = 0; i < HURT_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiHurtState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_hurt_sprites_ == nullptr) {
        printf("%s normal sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right_ = Samurai::Instance()->GetIsFacingRight();
    //cause the samurai hurt sprites has a different about 20 px in the positive x position
    // so need to calculate the x, y pos of the samurai when he do this action
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_HURT) ? DIFF_HURT : 0;
    Samurai::Instance()->HandleXPosWhenItMovesOutTheMap(current_x_pos);
    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_hurt_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }
    destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_hurt_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());

}

void SamuraiHurtState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    if (smr_hurt_sprites_ == nullptr) {
        printf("%s () hurt sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/HURT_FRAME_NUMBER];
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_HURT) ? DIFF_HURT : 0;
    Samurai::Instance()->HandleXPosWhenItMovesOutTheMap(current_x_pos);

    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_hurt_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_hurt_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/HURT_FRAME_NUMBER >= HURT_FRAME_NUMBER) {
        this->Exit();
    }

}

void SamuraiHurtState::Exit() {
    is_mode_on_ = false;
    Samurai::Instance()->smr_state_machine_->StateAnimationDone();
}