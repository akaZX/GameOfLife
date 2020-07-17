#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H


#include <vector>


typedef std::vector<std::vector<int> > GameGrid;



class GameOfLife
{
public:
	
    GameOfLife();
    ~GameOfLife();
	GameGrid gameBoard;
	
	void reset();	
	void setRows(int);
	void setColumns(int);
	void update();
	void cellState(GameGrid&);
	void manageColumns();
	void stepForward();
	void copyGrid(GameGrid&, GameGrid&);
	void blankBoard(GameGrid&);
	
private:

	int rows;
	int cols;
	void manageColumns(std::vector<int>&, int&, GameGrid&);
	GameGrid pentomino();	
	void addFigureToBoard(GameGrid&, GameGrid);
	
};

#endif // GAMEOFLIFE_H
