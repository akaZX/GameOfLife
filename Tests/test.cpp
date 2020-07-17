#include "pch.h"
#include "../gameoflife.cpp"
#include <vector>
#include <iostream>

//
//
class  GameOfLifeTest : public::testing::Test
{
public:
		GameOfLife test;

};


bool compareTwoVectors(GameGrid &grid1, GameGrid& grid2)
{
	

	for (int i = 0; i < grid1.size(); i++)
	{
		for (int j = 0; j < grid1[i].size(); j++)
		{
			if(grid1[i][j] != grid2[i][j])
			{
				return false;
			}			
		}
	}

	return true;
}




TEST_F(GameOfLifeTest, CopyArray)
{
	EXPECT_EQ(1, 1);

	GameGrid grid1 = {
					{0,0,0,0},
					{1,1,1,1},
					{0,0,0,0}};
	
	GameGrid grid2 (grid1.size(), std::vector<int>(grid1[0].size(), 0));
	
	test.copyGrid(grid1, grid2);
	
	EXPECT_TRUE(compareTwoVectors(grid1, grid2));
}


TEST_F(GameOfLifeTest, CellState_Still_1)
{
	GameGrid grid1 = {
					{1,1},
					{1,1}};


	test.cellState(grid1);


	for (auto i : grid1)
	{
		for(auto j : i)
			EXPECT_EQ(j, 1);
	}
	
}

TEST_F(GameOfLifeTest, CellState_Still_2)
{
	GameGrid grid1 = {
					{0,0,0},
					{0,0,0},
					{0,0,0} };


	test.cellState(grid1);


	for (auto i : grid1)
	{
		for (auto j : i)
			EXPECT_EQ(j, 0);
	}
	
}

TEST_F(GameOfLifeTest, CellState_Still_3)
{
	GameGrid grid1 = {
			{0,0,0,0,0,0},
			{0,1,1,0,0,0},
			{0,1,0,1,0,0},
			{0,0,1,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0} };

	GameGrid grid2 = {
			{0,0,0,0,0,0},
			{0,1,1,0,0,0},
			{0,1,0,1,0,0},
			{0,0,1,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0} };


	test.cellState(grid1);



	EXPECT_TRUE(compareTwoVectors(grid1, grid2));

}


TEST_F(GameOfLifeTest, CellState_Oscilator_1)
{
	GameGrid grid1 = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{0,0,0,0,0},
		{0,0,0,0,0} };


	GameGrid grid2 = {
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0} };
	
	test.cellState(grid1);


	EXPECT_TRUE(compareTwoVectors(grid1, grid2));

}

TEST_F(GameOfLifeTest, CellState_Oscilator_2)
{
	GameGrid grid1 = {
		{0,0,0,0,0,0},
		{0,1,1,0,0,0},
		{0,1,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,1,1,0},
		{0,0,0,0,0,0} };


	GameGrid grid2 = {
		{0,0,0,0,0,0},
		{0,1,1,0,0,0},
		{0,1,1,0,0,0},
		{0,0,0,1,1,0},
		{0,0,0,1,1,0},
		{0,0,0,0,0,0} };

	test.cellState(grid1);

	EXPECT_TRUE(compareTwoVectors(grid1, grid2));

}


TEST_F(GameOfLifeTest, BlankBoard)
{
	test.setRows(3);
	test.setColumns(4);
	GameGrid grid1;
	std::cout << grid1.size() << std::endl;
	test.blankBoard(grid1);


	EXPECT_EQ(3, grid1.size());
	EXPECT_EQ(4, grid1[0].size());
}

TEST_F(GameOfLifeTest, Reset)
{
	test.gameBoard = {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{0,0,0,0,0},
		{0,0,0,0,0} };

	test.reset();

	EXPECT_EQ(0, test.gameBoard.size());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gtest_death_test_style = "fast";
	return RUN_ALL_TESTS();
}