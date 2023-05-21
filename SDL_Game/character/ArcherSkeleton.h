#pragma once
#include "character.h"
#define ARCHER_SKELETON_HP 50
#include "Common/commonobject.h"
class SkeletonStateMachine;
class GameWorld;
class ArcherSkeleton : public Character {
public:
    ArcherSkeleton();
    ArcherSkeleton(int _x_pos, int _y_pos);
    ~ArcherSkeleton();

    virtual void NormalAttack() override;
    virtual void SpecialAttack() override;
    virtual void StrongAttack() override;
    virtual void Walk() override;
    virtual void Defend() override;
    virtual void Hurt() override;
    virtual void Idle() override;
    virtual void Die() override;
    virtual void Run() override;
    virtual void Jump() override;
    virtual int GetTopPos() override;
    virtual int GetBottomPos() override;
    virtual int GetLeftPos() override;
    virtual int GetRightPos() override;

    void NormalShot();
    void StateAnimationUpdate();
    void StateAnimationDone();

    void ChangedPosAfterMapChanged(int _x_pos);
    int GetXPos();
    int GetYPos();
    int GetSpawnXPos();
    int GetSpawnYPos();
    void SetSpawnXPos(int _spawn_x_pos);
    void SetSpawnYPos(int _spawn_y_pos);
    bool GetIsFacingRight();
    void SetXPos(int _ar_sk_velocity_x);
    void SetYPos(int _ar_sk_velocity_y);
    int GetVelocityX();
    int GetVelocityY();
    void SetIsFacingRight(bool _is_facing_right);
    void XPositionChanged();
    void SetHealthPoint(int _health_point);
    int GetHealthPoint();
    void ShowHealthPoint();
    void SetHealthProgressRect();
    void SetIsCollision(bool _is_collision);
    bool GetIsCollision();
    void HandleHurtEffect();

    SkeletonStateMachine* GetStateMachine();

public:
    SkeletonStateMachine* sk_state_machine_;
    int x_pos_;
    int y_pos_;
    int spawn_x_pos_;
    int spawn_y_pos_;
    int ar_sk_velocity_x_;
    int ar_sk_velocity_y_;
    bool is_facing_right_;
    int width_;
    int health_point_;
    game_define::EnemyHPColor enemy_hp_color_;
    game_define::EnemyBorderHPColor enemy_border_hp_color_;
    SDL_Rect health_border_rect_;
    SDL_Rect health_progress_rect_;
    bool is_collision_;
};