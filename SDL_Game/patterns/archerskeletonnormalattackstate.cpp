#include "archerskeletonnormalattackstate.h"
#include "GameWorld/gameworld.h"
ArcherSkeletonNormalAttackState::ArcherSkeletonNormalAttackState() {
    ar_sk_normal_attack_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init idle state failed!\n", __FUNCSIG__);
    }
}

ArcherSkeletonNormalAttackState::~ArcherSkeletonNormalAttackState() {
    SDL_DestroyTexture(ar_sk_normal_attack_sprites_);
}

bool ArcherSkeletonNormalAttackState::InitializeState() {
    //init the sprite animation texture and rect
    std::string ar_sk_normal_attack_image_path = ARCHER_SKELETON_NORMAL_ATTACK_PATH;
    ar_sk_normal_attack_sprites_ = CommonObject::Instance()->ImageTexture(ar_sk_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (ar_sk_normal_attack_sprites_ == nullptr) {
        printf("%s () Failed to load the idle texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    ar_sk_sprites_rect_[AR_SK_NORMAL_ATTACK_FRAME_NUMBER];
    for (int i = 0; i < AR_SK_NORMAL_ATTACK_FRAME_NUMBER; ++i) {
        ar_sk_sprites_rect_[i].x = i * game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].y = 0;
        ar_sk_sprites_rect_[i].w = game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;
}

void ArcherSkeletonNormalAttackState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (ar_sk_normal_attack_sprites_ == nullptr) {
        printf("%s idle sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_];
    is_facing_right = Samurai::Instance()->GetIsFacingRight();
    if (!is_facing_right) {
        int current_x_pos = 300;
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_NORMAL_ATTACK_SPRITES) ? AR_SK_DIFF_NORMAL_ATTACK_SPRITES : 0;
        destination_rect_ = { current_x_pos, 600, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_normal_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { 300, 600, game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_normal_attack_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());
}

void ArcherSkeletonNormalAttackState::Update() {
    if (ar_sk_normal_attack_sprites_ == nullptr) {
        printf("%s texture nullptr", __FUNCSIG__);
        return;
    }
    //destroy last texture
    // std::string ar_sk_normal_attack_image_path = SAMURAI_IDLE_PATH;
    // ar_sk_normal_attack_sprites_ = CommonObject::Instance()->ImageTexture(ar_sk_normal_attack_image_path, GameWorld::Instance()->GetRenderer());
    if (ar_sk_normal_attack_sprites_ == nullptr) {
        printf("%s () Failed to load the idle texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_/AR_SK_NORMAL_ATTACK_FRAME_NUMBER];
    if (!is_facing_right) {
        int current_x_pos = 300;
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_NORMAL_ATTACK_SPRITES) ? AR_SK_DIFF_NORMAL_ATTACK_SPRITES : 0;
        destination_rect_ = { current_x_pos, 600, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_normal_attack_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { 300, 600, game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_normal_attack_sprites_, &current_frame_rect, &destination_rect_);
    } 
    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/AR_SK_NORMAL_ATTACK_FRAME_NUMBER >= AR_SK_NORMAL_ATTACK_FRAME_NUMBER) {
        this->Exit();
    }
}

void ArcherSkeletonNormalAttackState::Exit() {
    is_mode_on_ = false;
    //call animation done
    // ArcherSkeleton::Instance()->sk_state_machine_->StateAnimationDone();
}