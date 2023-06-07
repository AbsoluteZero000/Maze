#include "Maze.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <vector>
#include <algorithm>

Maze::Maze(int s){

    size = s;
    maze = new char*[size];
    for(int i = 0; i < size; i++)
        maze[i] = new char[size];
    generateMaze();
}



void Maze::dfs(int x, int y) {
    std::vector<int> directions = {0, 1, 2, 3};
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine());

    int DX[] = {0, 0, 1, -1};
    int DY[] = {1, -1, 0, 0};

    for (int d : directions) {
        int nx = x + DX[d];
        int ny = y + DY[d];

        if (nx < 0 || nx >= size || ny < 0 || ny >= size || maze[nx][ny] != '#'){
            continue;
        }

        maze[x + DX[d] / 2][y + DY[d] / 2] = ' ';
        maze[nx][ny] = ' ';

        dfs(nx, ny);
    }
}

void Maze::generateMaze(){
    for(int i = 0 ; i < size; i++){
        for(int j = 0 ; j < size; j++){
            maze[i][j] = '#';
        }
    }
    srand(time(0));

    maze[rand()%(size - 2)][rand()%(size - 2) + 2] = 'G';
    maze[size-1][0] = 'P';
    dfs(size-1, 0);
}
