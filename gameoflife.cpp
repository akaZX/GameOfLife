#include "gameoflife.h"

#include <iostream>
#include <thread>
#include <mutex>






GameOfLife::GameOfLife()
{
	
}


GameOfLife::~GameOfLife()
{

}


//
// std::mutex mtx;
// std::vector<std::thread> threads;

void GameOfLife::cellState(GameGrid& mainGrid)
{

    GameGrid grid2(mainGrid.size(), std::vector<int>(mainGrid[0].size(), 0));
    copyGrid(mainGrid, grid2);

    for (unsigned int i = 1; i < mainGrid.size() - 1; i++) {

        // threads.push_back(std::thread([&mainGrid, i, &grid2] {
        	
        
            for (int j = 1; j < mainGrid[i].size() - 1; j++) {
                int life = 0;
                for (int c = -1; c < 2; c++) {
                    for (int d = -1; d < 2; d++) {
                        if (!(c == 0 && d == 0)) {
                            if (grid2[i + c][j + d] == 1) {
                                ++life;
                            }
                        }
                    }
                }

                if (life < 2) {
                    mainGrid[i][j] = 0;
                }
                else if (life == 3) {
                    mainGrid[i][j] = 1;
                }
                else if (life > 3) {
                    mainGrid[i][j] = 0;
                }
            }
            
            // }));
    }
      
}




void GameOfLife::stepForward(){

    // threads.clear();
    cellState(gameBoard);
    // for (auto &t: threads)
    // {
	   //  if(t.joinable())
	   //  {
    //         t.join();
	   //  }
    // }
	
}


void GameOfLife::update()
{
    blankBoard(gameBoard);
    addFigureToBoard(gameBoard, pentomino());
	
	
}

void GameOfLife::blankBoard(GameGrid& board)
{
	
    if (rows > 0 && cols > 0) {
        for (int i = 0; i < rows; i++)
        {
            board.push_back(std::vector<int>(cols, 0));

        }
    }else
    {
        std::cout << "rows or columns are less than 1..." << std::endl;
    }
	
}

void GameOfLife::copyGrid(GameGrid& grid1, GameGrid& grid2) {

    for (unsigned int i = 0; i < grid1.size(); i++) {

            for (unsigned int j = 0; j < grid1[i].size(); j++) {
               
                    grid2[i][j] = grid1[i][j];
                

            }
        

    }
}


void GameOfLife::addFigureToBoard(GameGrid& board, GameGrid figure)
{
    for (unsigned int i = 0; i < figure.size(); ++i) {
        for (unsigned int j = 0; j < figure[i].size(); j++) {
            board[rows / 4 + i][cols / 4 + j] = figure[i][j];
        }
    }
}


GameGrid GameOfLife::pentomino() {

    GameGrid rPentomino =
    {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    return rPentomino;

}



void GameOfLife::reset()
{
    gameBoard.clear();
}

void GameOfLife::setRows(int r)
{
    rows = r;
}

void GameOfLife::setColumns(int c)
{
    cols = c;
}


