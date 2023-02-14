#pragma once
#include <iostream>
//#define NOMINMAX
#include "ships.h"
#include <vector>
#include <time.h>

class player
{
public:

	int sizeField;
	
	bool defeat;

	int** field;

	std::vector <ships> shipsPlayer;

	player();
	~player();

	void addShips(std::vector<int>& decksShips, std::vector<int>& coordXYLateralShips);

	void randomSetShips();
};

