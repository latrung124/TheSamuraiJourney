#pragma once
#include <vector>
#include <memory>
#include "character/character.h"
#include "character/ArcherSkeleton.h"

class CharacterPool {
public:
    CharacterPool();
    ~CharacterPool();
    void InitializeArcherSkeletonPool();
    static CharacterPool* Instance();
    std::shared_ptr<ArcherSkeleton> GetArcherSkeleton();
    void ReturnArcherSkeleton(std::shared_ptr<ArcherSkeleton> _ar_sk);
protected:
    std::vector<std::shared_ptr<ArcherSkeleton>> ar_sk_pool_;
    int ar_sk_pool_size_;
};

