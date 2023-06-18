#include<iostream>
#include <random>

#ifndef MAZE_H
#define MAZE_H
struct Player{
    int x;
    int y;
};
class Maze{
    private:
        char ** maze;
        unsigned int size;
        Player player;
        void generateMaze();

        void dfs(int x, int y);

    public:
        Maze(int size);

        char** movePlayer(int x, int y);

        int getSize(){return size;}


        char getIndex(int row, int col){
                if (row < 0 || row >= size || col < 0 || col >= size) {
                throw std::out_of_range("Index out of range");
            }

            return maze[row][col];
        }
};
#endif
