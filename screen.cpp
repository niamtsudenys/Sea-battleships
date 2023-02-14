#include "screen.h"

screen::screen(): colorLateralShips(0) {}

void screen::set_col(color foreground, color background)
{
	SetConsoleTextAttribute(hout, ((short)background << 4) | (short)foreground);
}

void screen::gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void screen::fon()
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 120; ++j)
		{
			set_col(color::white, color::white);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void screen::inscriptionSeaAndBattleships()
{
	gotoxy(57, 4);
	set_col(color::red, color::white);
	std::cout << "S E A";

	gotoxy(50, 6);
	set_col(color::blue, color::white);
	std::cout << "B A T T L E S H I P S";
}

void screen::paintLateralShips(int coordinates, int numberOfDecks, int colorLateralShips)
{
	gotoxy(coordinates / 100, coordinates % 100);

	if (colorLateralShips == 0)
		set_col(color::darkgray, color::lightgray);
	else if (colorLateralShips == 1)
		set_col(color::green, color::lightgreen);
	else
		set_col(color::red, color::lightred);

	if (numberOfDecks == 4)
		std::cout << "|_|_|_|_|";
	else if (numberOfDecks == 3)
		std::cout << "|_|_|_|";
	else if (numberOfDecks == 2)
		std::cout << "|_|_|";
	else if (numberOfDecks == 1)
		std::cout << "|_|";
}

void screen::paintField()
{
	//////////////////////////////////////////////field1////////////////////////////
	gotoxy(30, 10);
	set_col(color::black, color::white);
	std::cout << "p u t i n X Y I L O ";

	gotoxy(35, 21);
	set_col(color::brown, color::white);
	std::cout << "Your field";

	for (int i = 0; i < 10; ++i)
	{
		gotoxy(29, 11 + i);
		set_col(color::black, color::white);
		std::cout << i;
	}

	for (int i = 0; i < 10; ++i)
	{
		gotoxy(30, 11 + i);
		for (int j = 0; j < 20; ++j)
		{
			set_col(color::lightcyan, color::lightcyan);
			std::cout << "O";
		}
	}

	///////////////////////////////////////////////field2/////////////////////////////////////////
	gotoxy(70, 10);
	set_col(color::black, color::white);
	std::cout << "p u t i n X Y I L O ";

	gotoxy(75, 21);
	set_col(color::brown, color::white);
	std::cout << "Bot field";

	for (int i = 0; i < 10; ++i)
	{
		gotoxy(69, 11 + i);
		set_col(color::black, color::white);
		std::cout << i;
	}

	for (int i = 0; i < 10; ++i)
	{
		gotoxy(70, 11 + i);
		for (int j = 0; j < 20; ++j)
		{
			set_col(color::lightcyan, color::lightcyan);
			std::cout << "O";
		}
	}
}

void screen::buttonsOnTheRightSide(bool& gameMode, int& buttonIsPressed)
{
	// buttons
	gotoxy(103, 23);
	if (!gameMode)
	{
		if (buttonIsPressed == 0)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Randomly";


	gotoxy(103, 25);
	if (!gameMode)
	{
		if (buttonIsPressed == 1)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Manual";

	gotoxy(103, 27);
	if (!gameMode)
	{
		if (buttonIsPressed == 2)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Exit";

	gotoxy(0, 30);
}

void screen::midButtons(bool& gameMode)
{
	gotoxy(57, 13);
	if (!gameMode)
		set_col(color::lightgray, color::white);
	else
		set_col(color::blue, color::white);
	std::cout << "Play";

	gotoxy(56, 15);
	if (!gameMode)
		set_col(color::lightgray, color::white);
	else
		set_col(color::blue, color::white);
	std::cout << "Restart";

	gotoxy(55, 17);
	if (!gameMode)
		set_col(color::lightgray, color::white);
	else
		set_col(color::blue, color::white);
	std::cout << "Surrender";

	gotoxy(0, 30);
}
