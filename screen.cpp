#include "screen.h"

screen::screen(): colorLateralShips(0), shipsOnField(0) {}

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
	// field man
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

    // field bot
	gotoxy(70, 10);
	set_col(color::black, color::white);
	std::cout << "p u t i n X Y I L O ";

	gotoxy(75, 21);
	set_col(color::brown, color::white);
	std::cout << "Bot field";

	for (int i = 0; i < 10; ++i)
	{
		gotoxy(90, 11 + i);
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

void screen::buttonsOnTheRightSide(bool& gameMode, int& buttonIsPressed, bool& play)
{
	gotoxy(110, 25);
	if (!gameMode)
	{
		if (buttonIsPressed == 1)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Randomly";

	gotoxy(110, 27);
	if (!gameMode)
	{
		if (buttonIsPressed == 2)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Manual";

	gotoxy(110, 29);
	if (!gameMode)
	{
		if (buttonIsPressed == 3)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Exit";

	gotoxy(119, 0);
}

void screen::bottomButtons(bool gameMode, int buttonIsPressed, bool play)
{
	gotoxy(63, 29);
	if (gameMode && !play)
	{
		if (buttonIsPressed == 0)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Play";

	gotoxy(71, 29);
	if (gameMode && !play)
	{
		if (buttonIsPressed == 1)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Shuffle";
	
	gotoxy(82, 29);
	if (gameMode && play)
	{
		if (buttonIsPressed == 2)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	std::cout << "Capitulation c";

	gotoxy(100, 29);
	if (gameMode && !play)
	{
		if (buttonIsPressed == 4)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	if (play)
		std::cout << "Back b";
	else
		std::cout << "Back";
		
	
	gotoxy(110, 29);
	if (gameMode)
	{
		if (buttonIsPressed == 5)
			set_col(color::red, color::white);
		else
			set_col(color::blue, color::white);
	}
	else
		set_col(color::lightgray, color::white);
	if (play)
		std::cout << "Exit e";
	else
		std::cout << "Exit";

	gotoxy(119, 0);
}

void screen::message(std::string sMs, int str)
{
	set_col(color::white, color::white);                 // udalyaem starye sms

	if (str == 1)
	{
		gotoxy(120 / 2 - 10, 13);                        // esli menyaetsya hod to chistim i 1 i 2 ryad
		std::cout << "                    ";
		gotoxy(120 / 2 - 10, 15);
		std::cout << "                    ";
		gotoxy(119, 0);
	}
	else
	{
		gotoxy(120 / 2 - 8, 15);                         // histim tolyko vtoroi riad
		std::cout << "                ";
		gotoxy(119, 0);
		Sleep(500);
	}
	
	if (str == 1)
		gotoxy(120 / 2 - sMs.length() / 2, 13);         // stavim kursor na 1 str
	else
		gotoxy(120 / 2 - sMs.length() / 2, 15);         // stavim kursor na 2 str
		
	if (sMs == "Welcome!")
		set_col(color::lightblue, color::yellow);
	else
		set_col(color::red, color::white);
	
	std::cout << sMs;

	gotoxy(119, 0);
}

void screen::clearLiterEandB()
{
	set_col(color::white, color::white);

	gotoxy(115, 29);
	std::cout << " ";

	gotoxy(105, 29);
	std::cout << " ";

	gotoxy(120, 0);
}

void screen::clearLiterC()
{
	set_col(color::white, color::white);

	gotoxy(95, 29);
	std::cout << " ";

	gotoxy(120, 0);
}