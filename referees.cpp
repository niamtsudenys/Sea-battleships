#include "referees.h"

referees::referees() :
	gameMode(0), gameOver(0), buttonIsPressed(0) {}

void referees::showScreen()
{
	fon();

	inscriptionSeaAndBattleships();

	for (int i = 0; i < 10; ++i)
	{
		paintLateralShips(coordXYLateralShipsMan[i], decksShips[i], 0);
	}

	for (int i = 0; i < 10; ++i)
	{
		paintLateralShips(coordXYLateralShipsBot[i], decksShips[i], 0);
	}

	paintField();

	buttonsOnTheRightSide(gameMode, buttonIsPressed);

	midButtons(gameMode);
}

void referees::loadShips()
{
	man.addShips(decksShips, coordXYLateralShipsMan);
	bot.addShips(decksShips, coordXYLateralShipsBot);
}


void referees::input()
{
	for (;;)
	{
		int ch = _getch();

		switch (ch)
		{
		case 's':   // s  vniz            
			++buttonIsPressed;
			break;
		case 'w':   // w  vverh           
			--buttonIsPressed;
			break;
		case 80:   // s  vniz            
			++buttonIsPressed;
			break;
		case 72:   // w  vverh           
			--buttonIsPressed;
			break;
		}

		if (buttonIsPressed < 0)
			buttonIsPressed = 2;
		else if (buttonIsPressed > 2)
			buttonIsPressed = 0;

		buttonsOnTheRightSide(gameMode, buttonIsPressed);
		
		if (ch == 13)
			break;
	}



	/*if (buttonIsPressed == 0)
		randomInstallationOfShips(fieldMan, shipsMan);
	else if (buttonIsPressed == 1)
		manualInstallationOfShips(fieldMan, shipsMan);
	else if (buttonIsPressed == 2)
		exit(0);*/

	//randomInstallationOfShips(fieldBot, shipsBot);


	//gameMode = 1;

	//buttonsOnTheRightSide();
	//midButtons();

	/*gotoxy(0, 31);
	set_col(color::black, color::white);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << field[i][j];
		}
		std::cout << std::endl;
	}*/
}
