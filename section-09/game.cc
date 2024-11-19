#include <iostream>

#include "game.hpp"

using namespace std;

class OneGame: public game::IGame
{
    public:
        virtual void playerInit(void*&);
        virtual void wordInit(void*&);
};


void OneGame::playerInit(void *& cfg)
{
    cout << "玩家初始化" << endl;
}

void OneGame::wordInit(void *& cfg)
{
    cout << "初始化" << endl;
}

void init(game::IGame *interface)
{
    void* cfg = NULL;
    interface->wordInit(cfg);
    interface->playerInit(cfg);
}

int main()
{
    init(new OneGame);
    return EXIT_SUCCESS;
}