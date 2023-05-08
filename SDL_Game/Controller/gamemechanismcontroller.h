#pragma once
#include "character/ArcherSkeleton.h"
#include <vector>
#include <memory>
class GameMechanismController {
public:
    GameMechanismController();
    ~GameMechanismController();

    static GameMechanismController* Instance();

    int GetRealXPosOfMap();
    void IncreaseRealXPosOfMap(int _x_pos);
    void DecreaseRealXPosOfMap(int _x_pos);
    void SetIsMapMoving(bool _is_map_moving);
    bool GetIsMapMoving();

    void UpdatePositionOfEnemies(std::vector<std::shared_ptr<ArcherSkeleton>>& _ar_sk_enemies);

private:
    int real_x_pos_of_map_;
    int last_x_pos_map_changed_;
    bool is_map_moving_;
};