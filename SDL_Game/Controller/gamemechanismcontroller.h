#pragma once
#include "character/ArcherSkeleton.h"
#include "character/samurai.h"
#include <vector>
#include <memory>
#include "archerskeletonstatemachine.h"
class GameMechanismController {
public:
    GameMechanismController();
    ~GameMechanismController();

    static GameMechanismController* Instance();

    int GetRealXPosOfMap();
    void IncreaseRealXPosOfMap(int _x_pos);
    void DecreaseRealXPosOfMap(int _x_pos);
    void SetIsMapMoving(bool _is_map_moving);
    void SetBackgroundOffset();
    bool GetIsMapMoving();
    int16_t GetBackgroundOffset();

    void UpdatePositionForSamurai(Samurai* _samurai);
    void UpdatePositionOfEnemies(std::vector<std::shared_ptr<ArcherSkeleton>>& _ar_sk_enemies);
    bool GuardCheck(int _enemy_x, int _samurai_x);
    bool ColisionCheck(Samurai* _samurai, std::shared_ptr<ArcherSkeleton>& _ar_sk);

private:
    int real_x_pos_of_map_;
    int last_x_pos_map_changed_;
    bool is_map_moving_;
    int background_offset_;
};