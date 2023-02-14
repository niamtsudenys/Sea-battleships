#pragma once
#define NOMINMAX
#include <iostream> 
#include <Windows.h>
#include <vector>
#include <conio.h>
//#include <ctime>
//#include <string>


class Battleships
{
private:

	const int sizeField;
	int** fieldMan;
	int** fieldBot;
	int colorLateralShips;
	bool gameMode;
	bool gameOver;
	std::vector<int> coordXYLateralShipsMan{ 612, 614, 1514, 616, 1316, 2016, 618, 1118, 1618, 2118 };
	std::vector<int> coordXYLateralShipsBot{ 9612, 9614, 10514, 9616, 10316, 11016, 9618, 10118, 10618, 11118 };
	
	// jizni korablei, kolichestvo palub
	std::vector<int> shipsMan { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };  
	std::vector<int> shipsBot { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	int buttonIsPressed;

public:

	Battleships();

	~Battleships();

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	enum class color
	{
		black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
		lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
	};

	enum class litters
	{
		p, u, t, i, n, X, Y, I, L, O
	};

	void set_col(color foreground, color background);

	void gotoxy(int x, int y);

	void cover();

	void setup();

	void logic();

	/////////////////////////////////////////////////////

	void paintLateralShips(int coordinates, int numberOfDecks);

	void paintField();

	void buttonsOnTheRightSide();

	void midButtons();

	void randomInstallationOfShips(int** field, std::vector<int>& ships);

	void manualInstallationOfShips(int** field, std::vector<int>& ships);
};