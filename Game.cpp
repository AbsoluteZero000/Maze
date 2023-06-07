#include "Game.h"
#include <iostream>
Game::Game(int s){
    maze = new Maze(s);
}

void Game::printMaze(){
    for(int i = 0 ; i < maze->getSize()*2 + 2; i++)
        std::cout<<(char)(196);
    std::cout<<std::endl;

    for(int i = 0 ; i < maze->getSize(); i++){
        std::cout<<"|";
        for(int j = 0; j < maze->getSize(); j++){
            std::cout<<" "<< maze->getIndex(i,j);
        }
        std::cout<<" |"<<std::endl;
    }

    for(int i = 0 ; i < maze->getSize() * 2 + 2; i++)
        std::cout<<(char)(196);

}
void Game::play(){
    printMaze();


}
