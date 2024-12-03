#ifndef __GAME_HPP___
#define __GAME_HPP___

namespace game
{

    class IGame
    {
    public:
        virtual void wordInit(void*&) = 0;
        virtual void playerInit(void*&) = 0;
    };
}


#endif