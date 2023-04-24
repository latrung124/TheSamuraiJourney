#include "samuraidefendstate.h"
#include "GameWorld/gameworld.h"
SamuraiDefendState::SamuraiDefendState() {
    smr_defend_sprites_ = nullptr;
    is_mode_on_ = false;
    if (!InitializeState()) {
        printf("%s init defend state failed!\n", __FUNCSIG__);
    }
}

SamuraiDefendState::~SamuraiDefendState() {
    SDL_DestroyTexture(smr_defend_sprites_);
}

bool SamuraiDefendState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_defend_image_path = SAMURAI_DEFEND_PATH;
    smr_defend_sprites_ = CommonObject::Instance()->ImageTexture(smr_defend_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_defend_sprites_ == nullptr) {
        printf("%s () Failed to load the normal texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[DEFEND_FRAME_NUMBER];
    for (int i = 0; i < DEFEND_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiDefendState::Enter() {
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_defend_sprites_ == nullptr) {
        printf("%s defend sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right = Samurai::Instance()->GetIsFacingRight();
    if (!is_facing_right) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_LEFT_RIGHT_DEFEND) ? DIFF_LEFT_RIGHT_DEFEND : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_defend_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }

    destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_defend_sprites_, &current_frame_rect, &destination_rect_);

}

void SamuraiDefendState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    if (smr_defend_sprites_ == nullptr) {
        printf("%s () defend sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/(DEFEND_FRAME_NUMBER*2)];
    if (!is_facing_right) {
        int current_x_pos = Samurai::Instance()->GetXPos();
        current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_LEFT_RIGHT_DEFEND) ? DIFF_LEFT_RIGHT_DEFEND : 0;
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_defend_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_defend_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/(DEFEND_FRAME_NUMBER*2) >= DEFEND_FRAME_NUMBER) {
        --current_frame_;
    }

}

void SamuraiDefendState::Exit() {
    is_mode_on_ = false;
}