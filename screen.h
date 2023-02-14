#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

class screen
{
public:
	screen();

	int colorLateralShips;

	std::vector<int> coordXYLateralShipsMan{ 612, 614, 1514, 616, 1316, 2016, 618, 1118, 1618, 2118 };
	std::vector<int> coordXYLateralShipsBot{ 9612, 9614, 10514, 9616, 10316, 11016, 9618, 10118, 10618, 11118 };

	// jizni korablei, kolichestvo palub
	std::vector<int> decksShips{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	
	enum class color
	{
		black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
		lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
	};

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	void set_col(color foreground, color background);

	void gotoxy(int x, int y);
	
	void fon();     // zalivka ekrana

	void inscriptionSeaAndBattleships(); 

	void paintLateralShips(int coordinates, int numberOfDecks, int colorLateralShips);

	void paintField();

	void buttonsOnTheRightSide(bool& gameMode, int& buttonIsPressed);

	void midButtons(bool& gameMode);
};