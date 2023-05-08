#pragma once
#include "character.h"
class SkeletonStateMachine;
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

    void NormalShot();
    void StateAnimationUpdate();

    void ChangedPosAfterMapChanged(int _x_pos);
    int GetXPos();
    int GetYPos();
    bool GetIsFacingRight();
    void SetXPos(int _ar_sk_velocity_x);
    void SetYPos(int _ar_sk_velocity_y);
    int GetVelocityX();
    int GetVelocityY();
    void SetIsFacingRight(bool _is_facing_right);
    void XPositionChanged();

    SkeletonStateMachine* GetStateMachine();

public:
    SkeletonStateMachine* sk_state_machine_;
    int x_pos_;
    int y_pos_;
    int ar_sk_velocity_x_;
    int ar_sk_velocity_y_;
    bool is_facing_right_;
};