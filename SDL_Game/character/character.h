#pragma once

class Character {
public:
    virtual void NormalAttack() = 0;
    virtual void SpecialAttack() = 0;
    virtual void StrongAttack() = 0;
    virtual void Walk() = 0;
    virtual void Defend() = 0;
    virtual void Hurt() = 0;
    virtual void Idle() = 0;
    virtual void Die() = 0;
    virtual void Run() = 0;
    virtual void Jump() = 0;
    virtual int GetBottomPos() = 0;
    virtual int GetTopPos() = 0;
    virtual int GetLeftPos() = 0;
    virtual int GetRightPos() = 0;

};
