#include "gameobjectpool.h"

static CharacterPool* character_pool_ = nullptr;
CharacterPool::CharacterPool() {
    ar_sk_pool_size_ = AR_SK_NUMBER;
}

CharacterPool::~CharacterPool() {
    if (character_pool_ != nullptr) {
        delete character_pool_;
        character_pool_ = nullptr;
    }
}

void CharacterPool::InitializeArcherSkeletonPool() {
    // ar_sk_pool_.push_back(std::make_shared<ArcherSkeleton>());
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
        ar_sk->GetStateMachine()->StateAnimationDone();

        return ar_sk;
    }
}

void CharacterPool::ReturnArcherSkeleton(std::shared_ptr<ArcherSkeleton> _ar_sk) {
    ar_sk_pool_.push_back(_ar_sk);
} 