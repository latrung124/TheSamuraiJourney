#pragma once
#include "Common/commonobject.h"

class BaseState {
public:
    BaseState();
    virtual ~BaseState();
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
    bool is_facing_right;
};
