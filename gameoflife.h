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
	int getRows();
	int getColumns();
	void update();
	void cellState(GameGrid&);
	void stepForward();

	
private:

	int rows;
	int cols;

	void blankBoard(GameGrid&);
    void copyGrid(GameGrid&, GameGrid&);	
	GameGrid pentomino();	
	void addFigureToBoard(GameGrid&, GameGrid);
	
};

#endif // GAMEOFLIFE_H
