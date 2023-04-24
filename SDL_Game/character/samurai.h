#pragma once
#include "character.h"
#include "Observable.h"
#include "statemachine.h"
class Samurai : public Character, public Observable{

public:
    Samurai();
    ~Samurai();

    static Samurai* Instance();

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

    virtual void AddObserver(Observer* _observer) override;
    virtual void RemoveObserser(Observer* _observer);
    virtual void NotifyObservers();

    void UpdateAnimation();

    int GetXPos();
    int GetYPos();
    bool GetIsFacingRight();
    void SetXPos(int _smr_velocity_x);
    void SetYPos(int _smr_velocity_y);
    int GetVelocityX();
    int GetVelocityY();
    void SetIsFacingRight(bool _is_facing_right);
    void XPositionChanged();
    void HandleXPosWhenItMovesOutTheMap(int& _current_x_pos);

public:
    SamuraiStateMachine* smr_state_machine_;
    int x_pos_;
    int y_pos_;
    int smr_velocity_x_;
    int smr_velocity_y_;
    bool is_facing_right_;
};
