#pragma once
#include "screen.h"
#include "player.h"
#include <conio.h>

class referees : public screen
{
public:

	bool gameMode;
	bool gameOver;
	int buttonIsPressed;

	player man;
	player bot;

	enum class litters { p, u, t, i, n, X, Y, I, L, O };

	referees();

	void showScreen();   // pervoe chto vidit polyzovately
	       
	void loadShips();

	void input();       // vybor rejima igry
};