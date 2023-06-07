#ifndef GAME_H
#define GAME_H
#include "Maze.h"


class Game{
    private:
        Maze* maze;
        void printMaze();
    public:
        Game(int size);
        void play();
};

#endif
