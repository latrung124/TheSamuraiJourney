#include "samuraiwalkstate.h"
#include "GameWorld/gameworld.h"
SamuraiWalkState::SamuraiWalkState() {
    smr_walk_sprites_ = nullptr;
    is_mode_on_ = false;
    is_facing_right_ = true;
    if (!InitializeState()) {
        printf("%s init walk state failed!\n", __FUNCSIG__);
    }
}

SamuraiWalkState::~SamuraiWalkState() {
    SDL_DestroyTexture(smr_walk_sprites_);
}

bool SamuraiWalkState::InitializeState() {
    //init the sprite animation texture and rect
    std::string smr_walk_image_path = SAMURAI_WALK_PATH;
    smr_walk_sprites_ = CommonObject::Instance()->ImageTexture(smr_walk_image_path, GameWorld::Instance()->GetRenderer());
    if (smr_walk_sprites_ == nullptr) {
        printf("%s () Failed to load the normal texture, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return false;
    }
    //define the area of each frame in the sprite sheet
    smr_sprites_rect_[WALK_FRAME_NUMBER];
    for (int i = 0; i < WALK_FRAME_NUMBER; ++i) {
        smr_sprites_rect_[i].x = i * game_define::kCharacterSize;
        smr_sprites_rect_[i].y = 0;
        smr_sprites_rect_[i].w = game_define::kCharacterSize;
        smr_sprites_rect_[i].h = game_define::kCharacterSize;
    }
    destination_rect_ = {game_define::kXSamuraiInitPos, game_define::kYSamuraiInitPos, game_define::kCharacterSize, game_define::kCharacterSize};
    return true;

}

void SamuraiWalkState::Enter() {
    if (is_mode_on_) {
        printf("%s skip cause the user keep press the button!", __FUNCSIG__);
        return;
    }
    is_mode_on_ = true;
    //use the texture and frames to render the character animation
    current_frame_ = 0;
    if (smr_walk_sprites_ == nullptr) {
        printf("%s walk sprite texture is nullptr!\n", __FUNCSIG__);
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_];
    is_facing_right_ = Samurai::Instance()->GetIsFacingRight();

    //cause the samurai walk sprites has a different about 20 px in the positive x position
    // so need to calculate the x, y pos of the samurai when he walks
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_WALK_SPRITES) ? DIFF_WALK_SPRITES : 0;
    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_walk_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
        return;
    }
    destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
    SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_walk_sprites_, &current_frame_rect, &destination_rect_);

}

void SamuraiWalkState::Update() {
    if (!is_mode_on_) {
        printf("%s mode is off \n", __FUNCSIG__);
        return;
    }
    if (smr_walk_sprites_ == nullptr) {
        printf("%s () walk attack sprites is null, SDL_Error(): %s", __FUNCSIG__, SDL_GetError());
        return;
    }
    SDL_Rect current_frame_rect = smr_sprites_rect_[current_frame_/WALK_FRAME_NUMBER];
    printf("%s samurai x_pos : %d, y_pos: %d", __FUNCSIG__, Samurai::Instance()->GetXPos(), Samurai::Instance()->GetYPos());
    //cause the samurai walk sprites has a different about 20 px in the positive x position
    //so need to calculate the x, y pos of the samurai when he walks
    int current_x_pos = Samurai::Instance()->GetXPos();
    current_x_pos -= (current_x_pos + game_define::kCharacterSize >= DIFF_WALK_SPRITES) ? DIFF_WALK_SPRITES : 0;
    if (!is_facing_right_) {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopyEx(GameWorld::Instance()->GetRenderer(), smr_walk_sprites_, &current_frame_rect, &destination_rect_, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        destination_rect_ = { current_x_pos, Samurai::Instance()->GetYPos(), game_define::kCharacterSize, game_define::kCharacterSize };
        SDL_RenderCopy(GameWorld::Instance()->GetRenderer(), smr_walk_sprites_, &current_frame_rect, &destination_rect_);
    }

    printf("%s frame %d was loaded!\n", __FUNCSIG__, current_frame_);
    ++current_frame_;
    if (current_frame_/WALK_FRAME_NUMBER >= WALK_FRAME_NUMBER) {
        current_frame_ = 0;
        Samurai::Instance()->XPositionChanged();
    }
}

void SamuraiWalkState::Exit() {
    is_mode_on_ = false;
}