#pragma once

#include "Common/commonobject.h"
#include "character/ArcherSkeleton.h"

class ArcherSkeletonBaseState {
public:
    ArcherSkeletonBaseState();
    virtual ~ArcherSkeletonBaseState();
    virtual void Enter(ArcherSkeleton* _ar_sk) = 0;
    virtual void Update(ArcherSkeleton* _ar_sk) = 0;
    virtual void Exit(ArcherSkeleton* _ar_sk) = 0;
};
