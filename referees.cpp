#include "referees.h"

referees::referees() :
	gameMode(0), gameOver(0), buttonIsPressed(1), play(0), turn(0) {}

void referees::showScreen()
{
	srand(time(NULL));
	
	man.fon(); 

	man.inscriptionSeaAndBattleships();

	for (int i = 0; i < 10; ++i)
	{
		man.paintLateralShips(man.coordXYLateralShipsMan[i], man.decksShips[i], 0);
	}

	for (int i = 0; i < 10; ++i)
	{
		bot.paintLateralShips(bot.coordXYLateralShipsBot[i], bot.decksShips[i], 0);
	}

	man.paintField();

	man.bottomButtons(gameMode, buttonIsPressed, play);
	man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);
}

void referees::loadShips()
{
	man.addShips(man.decksShips, man.coordXYLateralShipsMan);
	bot.addShips(bot.decksShips, bot.coordXYLateralShipsBot);
}

void referees::input()
{
link2:
	
	man.message(man.sms.at(0));

	while (true)
	{
		int ch = 0;

		if (_kbhit())
		{
			ch = _getch();

			// bokovye knopki
			switch (ch)
			{
			case 's':   // s  vniz            
				++buttonIsPressed;
				break;
			case 'w':   // w  vverh           
				--buttonIsPressed;
				break;
			case 80:   //  vniz            
				++buttonIsPressed;
				break;
			case 72:   //  vverh           
				--buttonIsPressed;
				break;
			}

			if (buttonIsPressed < 1)           // bokovye knopki aktivnye no bez "Play"
				buttonIsPressed = 3;
			else if (buttonIsPressed > 3)
				buttonIsPressed = 1;

			man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);

			if (ch == 13)
			{
				gameMode = 1;
				break;
			}
		}
		else 
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000) // esli najali knopku mishi
			{
				man.posXY();

				if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0) >= 
					110 && man.mousePosition.at(0) < 118) && man.mousePosition.at(1) == 25)
				{
					buttonIsPressed = 1;              // knopka Randomly
					gameMode = 1;
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
				if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0) >= 110 && man.mousePosition.at(0) < 116) && man.mousePosition.at(1) == 27)
				{
					buttonIsPressed = 2;              // knopka manual
					gameMode = 1;
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
				else if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0) >= 110 && man.mousePosition.at(0) < 115) && man.mousePosition.at(1) == 29)
				{
					man.message(man.sms.at(11));      // knopka Exit
					Sleep(500);
					exit(0);
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
			}
		}
	}

	if (buttonIsPressed == 1)                // stavim korably
		man.randomSetShips();      
	else if (buttonIsPressed == 2)
	{
		man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);
		man.bottomButtons(0, 4, 1);

		man.gotoxy(100, 29);
		man.set_col(cursor::color::blue, cursor::color::white);
		std::cout << "Back b";

		man.gotoxy(110, 29);
		std::cout << "Exit e";

		if (man.mouseOrKeybordControl(0, 1) == "back")
		{
			man.clearLiterEandB();
			back();
			goto link2;
		}
		if (man.manualSetShips())
		{
			back();
			goto link2;
		}
	}
	else if (buttonIsPressed == 3)
	{
		man.message(man.sms.at(11));
		Sleep(500);
		exit(0);
	}

	bot.randomSetShips();

	man.drawOnTheField();                    // obnovlyaem risunok poley
	bot.drawOnTheField(2);

	man.shipsOnField = 1;                    // vse korably ustanovleny
	buttonIsPressed = 0;                     // cursor na knopku play

	man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);
	man.bottomButtons(gameMode, buttonIsPressed, play);

link:
	// nijnie knopki
	int ch = 0;
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 'd':   // d  vpravo           
				++buttonIsPressed;
				break;
			case 'a':   // a  vlevo           
				--buttonIsPressed;
				break;
			case 77:   // -> vpravo            
				++buttonIsPressed;
				break;
			case 75:   // <-  vlevo          
				--buttonIsPressed;
				break;
			}

			if (!play)
			{
				if (buttonIsPressed < 0)           // aktivnye toliko Play, Shuffle, Back i Exit
					buttonIsPressed = 5;
				else if (buttonIsPressed > 5)
					buttonIsPressed = 0;
				else if (buttonIsPressed == 2)
					buttonIsPressed = 4;
				else if (buttonIsPressed == 3)
					buttonIsPressed = 1;
			}
			else
			{
				if (buttonIsPressed < 1)           // aktivnye toliko Surrender i Exit
					buttonIsPressed = 3;
				else if (buttonIsPressed > 3)
					buttonIsPressed = 1;
			}

			man.bottomButtons(gameMode, buttonIsPressed, play);

			if (ch == 13 && !play)
				break;
		}
		else
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000) // esli najali knopku mishi
			{
				man.posXY();

				if ((man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && man.mousePosition.at(0) >= 63 && man.mousePosition.at(0) < 67) && man.mousePosition.at(1) == 29)
				{
					buttonIsPressed = 0;
					man.bottomButtons(gameMode, buttonIsPressed, play);
					play = 1;
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
				else if ((man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && man.mousePosition.at(0)
					>= 71 && man.mousePosition.at(0) < 78) && man.mousePosition.at(1) == 29)
				{
					shuffleManShips();
					buttonIsPressed = 1;
					man.bottomButtons(gameMode, buttonIsPressed, play);
					goto link;
					
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
				}
				else if ((man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && man.mousePosition.at(0)
					>= 100 && man.mousePosition.at(0) < 105) && man.mousePosition.at(1) == 29)
				{
					buttonIsPressed = 4;
					man.bottomButtons(gameMode, buttonIsPressed, play);
					Sleep(150);
					back();
					goto link2;
					
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
				else if ((man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && man.mousePosition.at(0)
					>= 110 && man.mousePosition.at(0) < 115) && man.mousePosition.at(1) == 29)
				{
					man.message(man.sms.at(11));
					Sleep(500);
					exit(0);
					man.mousePosition.at(0) = 0;
					man.mousePosition.at(1) = 0;
					break;
				}
			}
		}
	}

	if (buttonIsPressed == 0)                // stavim korably
	{
		if (man.mouseOrKeybordControl() == "back")
		{
			back();
			goto link2;
		}

		play = 1;
	}
	else if (buttonIsPressed == 1)
	{
		shuffleManShips();
		goto link;
	}
	else if (buttonIsPressed == 4)
	{
		back();
		goto link2;
	}
	else if (buttonIsPressed == 5)
	{
		man.message(man.sms.at(11));
		Sleep(500);
		exit(0);
	}

	man.bottomButtons(gameMode, buttonIsPressed, play);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void referees::firstMove() { turn = rand() % 2; }      // true man hodit pervym, false - bot

void referees::coordinatesFirstCellField()
{
	man.coordPritselX = 70;
	man.coordPritselY = 11;

	bot.coordPritselX = 30;
	bot.coordPritselY = 11;
}

std::string referees::logic()
{
	firstMove();
	coordinatesFirstCellField();

	man.capitulation = 0;
	bot.capitulation = 0;

	while (!gameOver)
	{
		showScore();
		
		if (man.countShip == 0 || bot.countShip == 0)
		{
			gameOver = true;
		}
		
		if (turn)
		{
			man.attackMan(turn, bot);
		}
		else
		{
			bot.attackBot(turn, man);
		}

		if (man.capitulation)
		{
			back();

			man.countShip = 0;
			bot.countShip = 0;

			man.clearLiterEandB();

			man.message(man.sms.at(10));
			man.message(man.sms.at(8), 2);

			gameOver = 0;
			Sleep(2000);
			
			man.lost = 1;
			++bot.victory;

			showScore();

			return "c";
		}
	}

	Sleep(1000);

	if (gameOver)
	{
		if (bot.lost == 1)
		{
			man.message(man.sms.at(9));
			man.message(man.sms.at(7), 2);

			++man.victory;
		}
		else if (man.lost == 1)
		{
			man.message(man.sms.at(10));
			man.message(man.sms.at(8), 2);
			++bot.victory;
		}

		showScore();

		back();

		man.countShip = 0;
		bot.countShip = 0;

		gameMode = 1;

		man.clearLiterEandB();

		Sleep(2000);
		gameOver = 0;

		return menuAfterTheBattle();  // vybiraem kak ustanovity korabli dlya sleduiushei partii
	}
}

void referees::shuffleManShips()
{
	for (int i = 0; i < man.sizeField; ++i)
		for (int j = 0; j < man.sizeField; ++j)
			man.field[i][j] = 0;
	
	man.randomSetShips();
	man.drawOnTheField(1);

	man.gotoxy(119, 0);
}

void referees::back()
{
	for (auto& ship : man.shipsPlayer)
	{
		ship.color = 0;
		ship.life = 1;
		man.paintLateralShips(ship.latteralCoordinates, ship.deck, ship.color);
	}

	for (auto& ship : bot.shipsPlayer)
	{
		ship.color = 0;
		ship.life = 1;

		bot.paintLateralShips(ship.latteralCoordinates, ship.deck, ship.color);
	}

	man.clearMasiv();
	bot.clearMasiv();

	man.countShip = 0;
	bot.countShip = 0;

	gameMode = 0;
	gameOver = 0;
	buttonIsPressed = 1;
	play = 0;

	man.drawOnTheField(1);
	bot.drawOnTheField(2);

	man.lost = 0;
	bot.lost = 0;

	man.capitulation = 0;

	man.bottomButtons(gameMode, buttonIsPressed, play);
	man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);

	man.mousePosition.at(0) = 0;
	man.mousePosition.at(1) = 0;
}

void referees::restart(bool modeSetShips)
{
	back();

	if (!modeSetShips)
	{
		man.randomSetShips();
		bot.randomSetShips();
	}
	else
	{
		man.manualSetShips();
		bot.randomSetShips();
	}
	
	man.drawOnTheField();                    // obnovlyaem risunok poley
	bot.drawOnTheField(2);

	man.shipsOnField = 1;                    // vse korably ustanovleny
	buttonIsPressed = 0;                     // cursor na knopku 

	play = 1;

	buttonIsPressed = 0;
	gameMode = 1;

	man.buttonsOnTheRightSide(gameMode, buttonIsPressed, play);
	man.bottomButtons(gameMode, buttonIsPressed, play);
}

void referees::showScore()
{
	std::string s = std::to_string(man.victory); 
	
	man.gotoxy(120 / 2 - 5 - s.length(), 18);
	man.set_col(cursor::color::lightmagenta, cursor::color::white);
	std::cout << "man " << man.victory << " : " << bot.victory << " bot";
}

std::string referees::menuAfterTheBattle()
{
	bool i = 0;
	
	man.message(man.sms.at(18));
	man.message(man.sms.at(19), 2);

	bool stopCicl = 0;

	forMenuAfterTheBattlel(i);

	while (!stopCicl)
	{
		if (_kbhit())
		{
			int ch = _getch();

			switch (ch)
			{
			case 80:
				i = !i;          // peremechaem vniz
				break;
			case 's':
				i = !i;
				break;
			case 72:
				i = !i;           // peremechaem vverh
				break;
			case 'w':
				i = !i;
				break;
			case 13:
				stopCicl = true;
				break;
			case 'e':
				man.message(man.sms.at(11));
				Sleep(500);
				exit(0);
				break;
			}

			forMenuAfterTheBattlel(i);
		}
		else
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000) // esli najali knopku mishi
			{
				man.posXY();

				if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0) >=
					50 && man.mousePosition.at(0) < 70) && man.mousePosition.at(1) == 13)
				{
					i = 0;
					break;
				}
				else if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0)
					>= 50 && man.mousePosition.at(0) < 70) && man.mousePosition.at(1) == 15)
				{
					i = 1;

					break;
				}
				else if (man.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (man.mousePosition.at(0)
					>= 110 && man.mousePosition.at(0) < 115) && man.mousePosition.at(1) == 29)
				{
					man.message(man.sms.at(11));
					Sleep(500);
					exit(0);
				}

				forMenuAfterTheBattlel(i);

			}
		}

		man.gotoxy(0, 0);
		man.set_col(cursor::color::blue, cursor::color::white);
		std::cout << i;
	}

	if (!i)
		return "r";
	else
		return "m";
}

void referees::forMenuAfterTheBattlel(bool i)
{
	if (!i)
	{
		man.gotoxy(120 / 2 - man.sms.at(18).length() / 2, 13);
		man.set_col(cursor::color::red, cursor::color::white);
		std::cout << man.sms.at(18);

		man.gotoxy(120 / 2 - man.sms.at(19).length() / 2, 15);
		man.set_col(cursor::color::blue, cursor::color::white);
		std::cout << man.sms.at(19);
	}
	else
	{
		man.gotoxy(120 / 2 - man.sms.at(18).length() / 2, 13);
		man.set_col(cursor::color::blue, cursor::color::white);
		std::cout << man.sms.at(18);

		man.gotoxy(120 / 2 - man.sms.at(19).length() / 2, 15);
		man.set_col(cursor::color::red, cursor::color::white);
		std::cout << man.sms.at(19);
	}

	man.gotoxy(119, 0);
}
