#pragma once
#include "cursor.h"

class screen : public cursor
{
public:
	int colorLateralShips;
	bool shipsOnField;

	screen();

	std::vector<int> coordXYLateralShipsMan{ 612, 614, 1514, 616, 1316, 2016, 618, 1118, 1618, 2118 };
	std::vector<int> coordXYLateralShipsBot{ 9612, 9614, 10514, 9616, 10316, 11016, 9618, 10118, 10618, 11118 };
	
	std::vector<int> decksShips{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };   // jizni korablei, kolichestvo palub

	std::vector<std::string> sms
	{
		"Welcome!", "Your turn!", "Opponent turn!", "You hit!", "Opponent hit!", "Miss!", "Ship destroyed!", 
		"You have won!", "You lose!", "Congratulations!", "Unfortunately!", "See you later!!", 
		"Shoot with keyboard", "Shoot with mouse", "Keybord control", "Mouse control", "Put ships", "Go!!! Go!!! Go!!!",
		"Go random", "Go manual"
	};
	
	void fon();                                                      // zalivka ekrana

	void inscriptionSeaAndBattleships(); 

	void paintLateralShips(int coordinates, int numberOfDecks, int colorLateralShips);

	void paintField();

	void buttonsOnTheRightSide(bool& gameMode, int& buttonIsPressed, bool& play);

	void bottomButtons(bool gameMode, int buttonIsPressed, bool play);

	void message(std::string sMs, int str = 1);

	void clearLiterEandB();

	void clearLiterC();
};