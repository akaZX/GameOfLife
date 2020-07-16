#include "pch.h"
#include "../gameoflife.h"

TEST(TestCaseName, sample) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(GameOfLife, CopyArrayTest)
{
	GameOfLife game;

	GameGrid grid1 = {
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0} };

	GameGrid grid2;


	//game.copyGrid(grid1, grid2);
	
	
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gtest_death_test_style = "fast";
	return RUN_ALL_TESTS();
}