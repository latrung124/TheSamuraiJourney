#include "archerskeletonspecialattackstate.h"
#include "GameWorld/gameworld.h"
ArcherSkeletonSpecialAttackState::ArcherSkeletonSpecialAttackState() {
    ar_sk_special_attack_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init special attack state failed!\n", __FUNCSIG__);
    }
}

ArcherSkeletonSpecialAttackState::~ArcherSkeletonSpecialAttackState() {
    SDL_DestroyTexture(ar_sk_special_attack_sprites_);
}

bool ArcherSkeletonSpecialAttackState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_normal_attack_image_path = SAMURAI_SPECIAL_ATTACK_PATH;
    ar_sk_special_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (ar_sk_special_attack_sprites_ == nullptr) {
        printf("%s () Failed to load the special texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    ar_sk_sprites_rect_[AR_SK_SPECIAL_ATTACK_FRAME_NUMBER];
    for (int i = 0; i < AR_SK_SPECIAL_ATTACK_FRAME_NUMBER; ++i) {
        ar_sk_sprites_rect_[i].x = i * game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].y = 0;
        ar_sk_sprites_rect_[i].w = game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void ArcherSkeletonSpecialAttackState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (ar_sk_special_attack_sprites_ == nullptr) {
        printf("%s special sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_];
    if (!is_facing_right_) {
        int current_x_pos = x_pos_;
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_LEFT_RIGHT_SPECIAL_ATTACK) ? AR_SK_DIFF_LEFT_RIGHT_SPECIAL_ATTACK : 0;
        destination_rect_ = { current_x_pos, y_pos_, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_special_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { x_pos_, y_pos_, game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_special_attack_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());

}

void ArcherSkeletonSpecialAttackState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    // std::string smr_normal_attack_image_path = SAMURAI_SPECIAL_ATTACK_PATH;
    // ar_sk_special_attack_sprites_ = CommonObject::Instance()->ImageTexture(smr_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (ar_sk_special_attack_sprites_ == nullptr) {
        printf("%s () special attack sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_/AR_SK_SPECIAL_ATTACK_FRAME_NUMBER];
    if (!is_facing_right_) {
        int current_x_pos = x_pos_;
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_LEFT_RIGHT_SPECIAL_ATTACK) ? AR_SK_DIFF_LEFT_RIGHT_SPECIAL_ATTACK : 0;
        destination_rect_ = { current_x_pos, y_pos_, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_special_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { x_pos_, y_pos_, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_special_attack_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/AR_SK_SPECIAL_ATTACK_FRAME_NUMBER >= AR_SK_SPECIAL_ATTACK_FRAME_NUMBER) {
        this->Exit();
    }

}

void ArcherSkeletonSpecialAttackState::Exit() {
    is_mode_on_ = false;
    // Samurai::Instance()->smr_state_machine_->StateAnimationDone();
}