#pragma once

class GameMechanismController {
public:
    GameMechanismController();
    ~GameMechanismController();

    static GameMechanismController* Instance();

    int GetRealXPosOfMap();
    void IncreaseRealXPosOfMap(int _x_pos);
    void DecreaseRealXPosOfMap(int _x_pos);

    int real_x_pos_of_map_;
};