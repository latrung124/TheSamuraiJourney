#include "samuraistrongattackstate.h"
#include "GameWorld/gameworld.h"
SamuraiStrongAttackState::SamuraiStrongAttackState() {
    smr_strong_attack_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init strong attack state failed!\n", __FUNCSIG__);
    }
}

SamuraiStrongAttackState::~SamuraiStrongAttackState() {
    SDL_DestroyTexture(smr_strong_attack_sprites_);
}

bool SamuraiStrongAttackState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_strong_attack_image_path = SAMURAI_STRONG_ATTACK_PATH;
    smr_strong_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_strong_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_strong_attack_sprites_ == nullptr) {
        printf("%s () Failed to load the idle texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[STRONG_ATTACK_FRAME_NUMBER];
    for (int i = 0; i < STRONG_ATTACK_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiStrongAttackState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_strong_attack_sprites_ == nullptr) {
        printf("%s idle sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right_ = Samurai::Instance()->GetIsFacingRight();
    if (!is_facing_right_) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_STRONG_ATTACK_SPRITES) ? DIFF_STRONG_ATTACK_SPRITES : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_strong_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_strong_attack_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());

}

void SamuraiStrongAttackState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    if (smr_strong_attack_sprites_ == nullptr) {
        printf("%s texture nullptr", __FUNCSIG__);
        return;
    }
    // std::string smr_strong_attack_image_path = SAMURAI_STRONG_ATTACK_PATH;
    // smr_strong_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_strong_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_strong_attack_sprites_ == nullptr) {
        printf("%s () strong attack sprite null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/STRONG_ATTACK_FRAME_NUMBER];
    if (!is_facing_right_) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_STRONG_ATTACK_SPRITES) ? DIFF_STRONG_ATTACK_SPRITES : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_strong_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_strong_attack_sprites_, &current_frame_rect, &destination_rect_);
    }
    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/STRONG_ATTACK_FRAME_NUMBER >= STRONG_ATTACK_FRAME_NUMBER) {
        this->Exit();
    }

}

void SamuraiStrongAttackState::Exit() {
    is_mode_on_ = false;
    Samurai::Instance()->smr_state_machine_->StateAnimationDone();
}