#include "samuraispecialattackstate.h"
#include "GameWorld/gameworld.h"
SamuraiSpecialAttackState::SamuraiSpecialAttackState() {
    smr_special_attack_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init special attack state failed!\n", __FUNCSIG__);
    }
}

SamuraiSpecialAttackState::~SamuraiSpecialAttackState() {
    SDL_DestroyTexture(smr_special_attack_sprites_);
}

bool SamuraiSpecialAttackState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_normal_attack_image_path = SAMURAI_SPECIAL_ATTACK_PATH;
    smr_special_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_special_attack_sprites_ == nullptr) {
        printf("%s () Failed to load the special texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[SPECIAL_ATTACK_FRAME_NUMBER];
    for (int i = 0; i < SPECIAL_ATTACK_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiSpecialAttackState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_special_attack_sprites_ == nullptr) {
        printf("%s special sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right = Samurai::Instance()->GetIsFacingRight();
    if (!is_facing_right) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_LEFT_RIGHT_SPECIAL_ATTACK) ? DIFF_LEFT_RIGHT_SPECIAL_ATTACK : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_special_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_special_attack_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());

}

void SamuraiSpecialAttackState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    // std::string smr_normal_attack_image_path = SAMURAI_SPECIAL_ATTACK_PATH;
    // smr_special_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_special_attack_sprites_ == nullptr) {
        printf("%s () special attack sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/SPECIAL_ATTACK_FRAME_NUMBER];
    if (!is_facing_right) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_LEFT_RIGHT_SPECIAL_ATTACK) ? DIFF_LEFT_RIGHT_SPECIAL_ATTACK : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_special_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_special_attack_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/SPECIAL_ATTACK_FRAME_NUMBER >= SPECIAL_ATTACK_FRAME_NUMBER) {
        this->Exit();
    }

}

void SamuraiSpecialAttackState::Exit() {
    is_mode_on_ = false;
    Samurai::Instance()->smr_state_machine_->StateAnimationDone();
}