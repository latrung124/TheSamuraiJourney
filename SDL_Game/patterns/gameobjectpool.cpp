#include "gameobjectpool.h"

static CharacterPool* character_pool_ = nullptr;
CharacterPool::CharacterPool() {
    ar_sk_pool_size_ = AR_SK_NUMBER;
    InitializeArcherSkeletonSpawnPosition();
    InitializeArcherSkeletonPool();
}

CharacterPool::~CharacterPool() {
    if (character_pool_ != nullptr) {
        delete character_pool_;
        character_pool_ = nullptr;
    }
}

void CharacterPool::InitializeArcherSkeletonSpawnPosition() {
    printf("%s \n", __FUNCSIG__);
    ar_sk_spawn_pos_vector_.push_back({300, 0});
    ar_sk_spawn_pos_vector_.push_back({600, 0});
    ar_sk_spawn_pos_vector_.push_back({900, 0});
}


void CharacterPool::InitializeArcherSkeletonPool() {
    printf("%s \n", __FUNCSIG__);
    for (int i = 0; i < AR_SK_NUMBER; ++i) {
        std::shared_ptr<ArcherSkeleton> ptr(new ArcherSkeleton(ar_sk_spawn_pos_vector_[i].first, ar_sk_spawn_pos_vector_[i].second));
        ar_sk_pool_.push_back(ptr);
    }
    printf("%s successfully\n", __FUNCSIG__);
}

CharacterPool* CharacterPool::Instance() {
    if (character_pool_ == nullptr) {
        character_pool_ = new CharacterPool();
    }
    return character_pool_;
}

std::shared_ptr<ArcherSkeleton> CharacterPool::GetArcherSkeleton() {
    if (ar_sk_pool_.empty()) {
        return std::make_shared<ArcherSkeleton>();
    } else {
        auto ar_sk = ar_sk_pool_.back();
        ar_sk_pool_.pop_back();
        // ar_sk->GetStateMachine()->StateAnimationDone();
        return ar_sk;
    }
}

void CharacterPool::ReturnArcherSkeleton(std::shared_ptr<ArcherSkeleton> _ar_sk) {
    ar_sk_pool_.push_back(_ar_sk);
} 