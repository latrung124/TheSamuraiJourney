#include "archerskeletonidlestate.h"
#include "GameWorld/gameworld.h"
ArcherSkeletonIdleState::ArcherSkeletonIdleState() {
    ar_sk_idle_sprites_ = nullptr;
    is_mode_on_ = false;
    spawn_y_ = 0;
    acceleration_spawnn_down_ = SPAWN_DOWN_OFFSET;
    if (!InitializeState()) {
        printf("%s init idle state failed!\n", __FUNCSIG__);
    }
}

ArcherSkeletonIdleState::~ArcherSkeletonIdleState() {
    SDL_DestroyTexture(ar_sk_idle_sprites_);
}

bool ArcherSkeletonIdleState::InitializeState() {
    //init the sprite animation texture and rect
    std::string ar_sk_idle_image_path = ARCHER_SKELETON_IDLE_PATH;
    ar_sk_idle_sprites_ = CommonObject::Instance()->ImageTexture(ar_sk_idle_image_path, GameWorld::Instance()->GetRenderer());
    if (ar_sk_idle_sprites_ == nullptr) {
        printf("%s () Failed to load the idle texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    ar_sk_sprites_rect_[AR_SK_IDLE_FRAME_NUMBER];
    for (int i = 0; i < AR_SK_IDLE_FRAME_NUMBER; ++i) {
        ar_sk_sprites_rect_[i].x = i * game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].y = 0;
        ar_sk_sprites_rect_[i].w = game_define::kCharacterSize;
        ar_sk_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;
}

void ArcherSkeletonIdleState::Enter(ArcherSkeleton* _ar_sk) {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (ar_sk_idle_sprites_ == nullptr) {
        printf("%s idle sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_];
    if (!_ar_sk->GetIsFacingRight()) {
        int current_x_pos = _ar_sk->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_IDLE_SPRITES) ? AR_SK_DIFF_IDLE_SPRITES : 0;
        destination_rect_ = { current_x_pos, _ar_sk->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_idle_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { _ar_sk->GetXPos(), _ar_sk->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_idle_sprites_, &current_frame_rect, &destination_rect_);
    // SDL_RenderPresent(GameWorld::Instance()->GetRenderer());
}

void ArcherSkeletonIdleState::Update(ArcherSkeleton* _ar_sk) {
    if (ar_sk_idle_sprites_ == nullptr) {
        printf("%s texture nullptr", __FUNCSIG__);
        return;
    }
    if (ar_sk_idle_sprites_ == nullptr) {
        printf("%s () Failed to load the idle texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = ar_sk_sprites_rect_[current_frame_/AR_SK_IDLE_FRAME_NUMBER];
    if (!_ar_sk->GetIsFacingRight()) {
        int current_x_pos = _ar_sk->GetXPos();
        if (_ar_sk->GetYPos() < LAND_Y) {
            acceleration_spawnn_down_ += SPAWN_DOWN_OFFSET;
            _ar_sk->SetYPos(acceleration_spawnn_down_);
        } else {
            acceleration_spawnn_down_ = 0;
            _ar_sk->y_pos_ = LAND_Y;
        }
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= AR_SK_DIFF_IDLE_SPRITES) ? AR_SK_DIFF_IDLE_SPRITES : 0;
        destination_rect_ = { current_x_pos, _ar_sk->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), ar_sk_idle_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = {_ar_sk->GetXPos(), _ar_sk->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), ar_sk_idle_sprites_, &current_frame_rect, &destination_rect_);
    } 
    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/AR_SK_IDLE_FRAME_NUMBER >= AR_SK_IDLE_FRAME_NUMBER) current_frame_ = 0;
}

void ArcherSkeletonIdleState::Exit(ArcherSkeleton* _ar_sk) {
    is_mode_on_ = false;
    current_frame_ = 0;
}