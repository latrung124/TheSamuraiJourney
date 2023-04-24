#include "GameWorld/gameworld.h"

int main(int argc, char* args[])
{
    printf("Run the game!");
    GameWorld::Instance()->RunningTheGame();
    GameWorld::Instance()->CleanUp();
    return 0;
}