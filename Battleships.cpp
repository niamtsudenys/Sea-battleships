#include "Battleships.h"

Battleships::Battleships() : sizeField(10), colorLateralShips(0), gameMode(0), gameOver(0), buttonIsPressed(0)
{
	fieldMan = new int* [sizeField];

	for (int i = 0; i < sizeField; ++i)
	{
		fieldMan[i] = new int[sizeField] {};
	}

	fieldBot = new int* [sizeField];

	for (int i = 0; i < sizeField; ++i)
	{
		fieldBot[i] = new int[sizeField] {};
	}
}

Battleships::~Battleships()
{
	for (int i = 0; i < sizeField; ++i)
	{
		delete[] fieldMan[i];
	}

	delete[] fieldMan;

	for (int i = 0; i < sizeField; ++i)
	{
		delete[] fieldBot[i];
	}

	delete[] fieldBot;
}

void Battleships::set_col(color foreground, color background)
{
	SetConsoleTextAttribute(hout, ((short)background << 4) | (short)foreground);
}

void Battleships::gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Battleships::cover()
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

	gotoxy(57, 4);
	set_col(color::red, color::white);
	std::cout << "S E A";

	gotoxy(50, 6);
	set_col(color::blue, color::white);
	std::cout << "B A T T L E S H I P S";

	// prorisovka bokobyh korabley igroka
	for (int i = 0; i < sizeField; ++i)
	{
		paintLateralShips(coordXYLateralShipsMan[i], shipsMan[i]);
	}

	// prorisovka bokobyh korabley bota
	for (int i = 0; i < sizeField; ++i)
	{
		paintLateralShips(coordXYLateralShipsBot[i], shipsBot[i]);
	}

	paintField();

	buttonsOnTheRightSide();
	midButtons();
}

void Battleships::setup()
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
			buttonIsPressed = 3;
		else if (buttonIsPressed > 2)
			buttonIsPressed = 0;

		buttonsOnTheRightSide();
		midButtons();

		if (ch == 13)
			break;
	}

	if (buttonIsPressed == 0)
		randomInstallationOfShips(fieldMan, shipsMan);
	else if (buttonIsPressed == 1)
		manualInstallationOfShips(fieldMan, shipsMan);
	else if (buttonIsPressed == 2)
		exit(0);

	//randomInstallationOfShips(fieldBot, shipsBot);
	

	gameMode = 1;

	buttonsOnTheRightSide();
	midButtons();

	gotoxy(0, 31);
	set_col(color::black, color::white);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << fieldMan[i][j];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 10; ++i)
	{
		std::cout << shipsMan[i];
	}
}

void Battleships::logic()
{
}

void Battleships::paintLateralShips(int coordinates, int numberOfDecks)
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

void Battleships::paintField()
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

void Battleships::buttonsOnTheRightSide()
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
}

void Battleships::midButtons()
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
}

void Battleships::randomInstallationOfShips(int** field, std::vector<int>& ships)
{
	for (int i = 0; i < ships.size(); ++i)
	{
		bool setShip = false;
		int sizeShip = 0;

		for (; !setShip;)
		{
			srand(time(NULL));

			int x = rand() % sizeField;             // pervichnaya pozitsiya
			int y = rand() % sizeField;

			int direction = rand() % 4;             // generatsiya sluchaynogo napravleniya rosta korablya
			
			////// proverka vozmojnosti postanovki korablya ///////////////////////////////////////////////////////////////////
			bool installationPossible = true;

			switch (direction)
			{
			case 0:
			{
				if (sizeField - x >= ships[i])  // proveryaem esli korabeli pomechyatsa v pole ot koordinat x,y vpravo
				{
					for (int j = 0; j < ships[i]; ++j)
					{
						if (x == 0 && j == 0)
						{
							if (field[y][x + j] != 0)      // proveryaem esli kletki svobodnye dlya postanovki
							{
								installationPossible = false;
								break;
							}
						}
					}
				}
				else
				{
					installationPossible = false;
					break;
				}
			}

				break;

			case 1:
			{
				if (x + 1 >= ships[i])  // proveryaem esli vesy korabeli pomechyatsa v pole ot koordinat x,y vlevo
				{
					for (int j = 0; j < ships[i]; ++j)   // proveryaem esli kletki svobodnye dlya postanovki
					{
						if (field[y][x - j] != 0)
						{
							installationPossible = false;
							break;
						}
					}
				}
				else
				{
					installationPossible = false;
					break;
				}
			}

				break;

			case 2:
			{
				if (sizeField - y >= ships[i])  // proveryaem esli vesy korabeli pomechyatsa v pole ot koordinat x,y vniz
				{
					for (int j = 0; j < ships[i]; ++j)   // proveryaem esli kletki svobodnye dlya postanovki
					{
						if (field[y + j][x] != 0)
						{
							installationPossible = false;
							break;
						}
					}
				}
				else
				{
					installationPossible = false;
					break;
				}
			}

				break;

			case 3:
			{
				if (y + 1 >= ships[i])  // proveryaem esli vesy korabeli pomechyatsa v pole ot koordinat x,y vverh
				{
					for (int j = 0; j < ships[i]; ++j)   // proveryaem esli kletki svobodnye dlya postanovki
					{
						if (field[y - j][x] != 0)
						{
							installationPossible = false;
							break;
						}
					}
				}
				else
				{
					installationPossible = false;
					break;
				}
			}

				break;
			}

			// esli est' vozmozhnost' postavit' korabl' to stavim
			if (installationPossible)
			{
				switch (direction)
				{
				case 0:
					for (int j = 0; j < ships[i]; ++j) 
					{
						field[y][x + j] = i;
					}

					break;

				case 1:
					for (int j = 0; j < ships[i]; ++j)
					{
						field[y][x - j] = i;
					}

					break;

				case 2:
					for (int j = 0; j < ships[i]; ++j)
					{
						field[y + j][x] = i;
					}

					break;

				case 3:
					for (int j = 0; j < ships[i]; ++j)
					{
						field[y - j][x] = i;
					}

					break;
				}

				setShip = true;
			}
		}
	}
}



void Battleships::manualInstallationOfShips(int** field, std::vector<int>& ships)
{

}



