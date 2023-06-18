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
    player.x = 0;
    player.y = 0;
}

void Maze::generateMaze() {

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      maze[i][j] = '#';
    }
  }

  int x = 0;
  int y = 0;

  dfs(x, y);

  maze[0][0] = 'P';
  maze[size - 1][size - 1] = '$';
}

void Maze::dfs(int x, int y) {
  maze[x][y] = ':';

  std::vector<std::pair<int, int>> neighbors;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i != 0 || j != 0) {
        neighbors.push_back({x + i, y + j});
      }
    }
  }

  for (auto neighbor : neighbors) {
    if (maze[neighbor.first][neighbor.second] == '#') {
      dfs(neighbor.first, neighbor.second);
    }
  }
}

char** Maze::movePlayer(int x, int y){

    if(x < 0 || x > size || y < 0 || y > size)
        return maze;

    if(maze[x][y] == '#')
        return maze;

    maze[x][y] = 'P';
    maze[player.x][player.y] = ':';

    player.x = x;
    player.y = y;

    return maze;

}
