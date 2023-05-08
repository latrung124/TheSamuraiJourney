#pragma once
#include <vector>
#include <memory>
#include "Common/commonobject.h"
#include "character/character.h"
#include "character/ArcherSkeleton.h"

class CharacterPool {
public:
    CharacterPool();
    ~CharacterPool();
    static CharacterPool* Instance();

    void InitializeArcherSkeletonSpawnPosition();
    void InitializeArcherSkeletonPool();
    std::shared_ptr<ArcherSkeleton> GetArcherSkeleton();
    void ReturnArcherSkeleton(std::shared_ptr<ArcherSkeleton> _ar_sk);
protected:
    std::vector<std::shared_ptr<ArcherSkeleton>> ar_sk_pool_;
    int ar_sk_pool_size_;
    std::vector<std::pair<int, int>> ar_sk_spawn_pos_vector_;
};

