#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "cstdlib"
#include "ctime"
#include <iostream>
#include "algorithm"
#include "stack"
#include<conio.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

enum Directions{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    INVALID
};


class Player {
    private:
        int x, y;
        int tempX, tempY;

        void moveRight(){tempY++;}
        void moveLeft(){tempY--;}
        void moveUp(){tempX--;}
        void moveDown(){tempX++;}

    public:
        Player() {
            x = 0;
            y = 0;
            tempX = 0;
            tempY = 0;
        }
        void movePlayer(Directions directions){
            if(directions == RIGHT)
                moveRight();
            else if(directions == LEFT)
                moveLeft();
            else if(directions == UP)
                moveUp();
            else if(directions == DOWN)
                moveDown();
        }
        void revert(){
            tempX = x;
            tempY = y;
        }
        void confirm(){
            x = tempX;
            y = tempY;
        }
        void reset(){
            x = y = tempX = tempY = 0;
        }
        int getTempY(){return tempY;}
        int getTempX(){return tempX;}
        int getY(){return y;}
        int getX(){return x;}

};

class Maze{
private:
    vector<vector<char>> map;
    Player player;

    void initializeMaze(){
        //U unvisited, ' ' visited
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                map[i][j] = '0';
            }
        }
        DFSGenerator(0,0);
    }

    void DFSGenerator(int i, int j){
        int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
        int visitOrder[] = {0,1,2,3};

        if(i < 0 || j < 0 || i >= map.size() || j >= map[0].size()) return ;

        #ifdef DEBUG
        cout<<"("<<i<<", "<<j<<")"<<endl;
        #endif

        if(map[i][j] == ' ') return;

        if(countVisitedNeighbor(i, j) > 1) return ;

        map[i][j] = ' ';

        shuffle(visitOrder, 4);

        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[visitOrder[k]][0];
            int nj = j + direct[visitOrder[k]][1];
            DFSGenerator(ni, nj);
        }
    }

    int countVisitedNeighbor(int i, int j){
        int direct[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        int count = 0;
        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[k][0];
            int nj = j + direct[k][1];

            if(ni < 0 || nj < 0 || ni >= map.size() || nj >= map[0].size()) continue;
            if(map[ni][nj] == ' ') count++;
        }
        return count;
    }
    void shuffle(int a[], int n){
        for (int i = 0; i < n; ++i)
        {
            swap(a[i], a[rand() % n]);
        }
    }
    void swap(int & a, int &b){
        int c = a;
        a = b;
        b = c;
    }

public:
    Maze(int height, int width){
        vector<char> row(width);
        for (int i = 0; i < height; ++i)
            map.push_back(row);
        initializeMaze();
        map[0][0] = 'P';
        map[map.size() - 1][map.size() - 1] = 'G';

    }

    void generateMaze(){
        DFSGenerator(0, 0);
        map[0][0] = 'P';
        map[map.size() - 1][map.size() - 1] = 'G';

    }
    bool checkGoal(){
        if(map.size() == player.getX()+1)
            if(map[0].size() == player.getY()+1)
                return true;
        return false;
    }

    void updateMaze(Directions directions){
        player.movePlayer(directions);
        if(player.getTempX() >= map.size() || player.getTempY() >= map[0].size() || map[player.getTempX()][player.getTempY()] == '0')
            player.revert();
        else{

            map[player.getX()][player.getY()] = ' ';
            map[player.getTempX()][player.getTempY()] = 'P';
            player.confirm();}


    }

    void printMaze(){
        for(int i = 0; i < map.size()*2+2; ++i)
            cout<<"_";
        cout<<endl;

        for (int i = 0; i < map.size(); ++i)
        {
            cout<<"|";
            for (int j = 0; j < map[0].size(); ++j)
            {
                cout<<" "<<map[i][j];
            }
            cout<<"|"<<endl;
        }
        for(int i = 0; i < map.size()*2+2; ++i)
            cout<<"_";
        cout<<endl;

    }
};

class Game{
private:

    Maze* maze;

    void Clear(){
        system("CLS");
    }
public:
    Game(int height, int width){
        maze = new Maze(height, width);
    }
    void play(){
        char input = 'Y';
        int c;
        Directions directions;
        while(input = 'Y'){
            c = 0;
            directions = INVALID;
            switch((c=getch())) {
            case KEY_UP:
                directions = UP;
                break;
            case KEY_DOWN:
                directions = DOWN;
                break;
            case KEY_LEFT:
                directions = LEFT;
                break;
            case KEY_RIGHT:
                directions = RIGHT;
                break;
            default:
                continue;
            }

            maze->updateMaze(directions);
            Clear();
            maze->printMaze();
            if(maze->checkGoal()){

            }

        }
    }
    void print(){
        maze->printMaze();
    }

};
int main()
{
    Game game(20,20);
    game.print();
    game.play();
    srand(time(0));
    return 0;
}
