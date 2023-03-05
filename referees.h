#pragma once
#include "player.h"

class referees
{
public:

	bool gameMode;
	bool gameOver;
	int buttonIsPressed;
	bool play;
	bool turn;

	player man;
	player bot;

	enum class litters { p, u, t, i, n, X, Y, I, L, O };

	referees();

	void showScreen();   // pervoe chto vidit polyzovately
	       
	void loadShips();

	void input();       // vybor rejima igry

	std::string logic();

	void firstMove();

	void coordinatesFirstCellField();

	void shuffleManShips();

	void back();

	void restart();

	void showScore();

	std::string menuAfterTheBattle(bool i = 0);

	void forMenuAfterTheBattlel(bool i);
};