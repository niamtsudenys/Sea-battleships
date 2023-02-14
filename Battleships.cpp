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
			buttonIsPressed = 2;
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
	

	//gameMode = 1;

	//buttonsOnTheRightSide();
	//midButtons();

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
	int it = 0;

	for (int i = 0; i < sizeField; ++i)
	{
		bool setShip = false;                 // true esli korabeli ustanovilsya
		int x = 0;                            // cordinaty pervoi tochki korablya
		int y = 0;
		bool installationPossible = true;     // true esli danyi korabeli vozmojno ustanovity

		for (; !setShip;)
		{
			++it;
			srand(time(NULL));

			// generatsiya sluchaynogo napravleniya rosta korablya
			int direction = rand() % 4;

			if (direction < 2)
				y = rand() % sizeField;
			else
				x = rand() % sizeField;


			if (direction == 0)
			{
				do                                  // ispolyzuyu tsikl do chtoby hoty odin raz tsycl srabotal
				{
					x = rand() % sizeField;         // pervichnaya pozitsiya
				} while (x > sizeField - ships[i]); // proveryaem esli korabeli pomechyaetsa v pole ot tochki x,y vpravo
			}
			else if (direction == 1)
			{
				do                                  // ispolyzuyu tsikl do chtoby hoty odin raz tsycl srabotal
				{
					x = rand() % sizeField;         // pervichnaya pozitsiya
				} while (x < ships[i] - 1);         // proveryaem esli korabeli pomechyaetsa v pole ot tochki s koordinatami x,y vlevo
			}
			else if (direction == 2)
			{
				do                                  // ispolyzuyu tsikl do chtoby hoty odin raz tsycl srabotal
				{
					y = rand() % sizeField;        // pervichnaya pozitsiya
				} while (y > sizeField - ships[i]); // proveryaem esli korabeli pomechyaetsa v pole ot tochki s koordinatami x,y vniz
			}
			else
			{
				do                                  // ispolyzuyu tsikl do chtoby hoty odin raz tsycl srabotal
				{
					y = rand() % sizeField;         // pervichnaya pozitsiya
				} while (y < ships[i] - 1);         // proveryaem esli korabeli pomechyaetsa v pole ot tochki s koordinatami x,y vverh
			}

			if (direction == 1)
			{
				x = x + 1 - ships[i]; // menyaem koordinaty pervoi paluby na posledniuiu paluby korablya i stroim                  
				direction = 0;        // korabely v druguiu storonu chtoby ne dublirovaty cod
			}

			if (direction == 3)
			{
				y = y + 1 - ships[i]; // menyaem koordinaty pervoi paluby na posledniuiu paluby korablya i stroim                  
				direction = 2;        // korabely v druguiu storonu chtoby ne dublirovaty cod
			}

			////// proverka vozmojnosti postanovki korablya ///////////////////////////////////////////////////////////////////
			if (!direction)
			{
				for (int k = std::max(0, y - 1); k <= std::min(9, y + 1); ++k)
				{
					for (int j = std::max(0, x - 1); j <= std::min(9, x + ships[i]); ++j)
					{
						if (field[k][j] == 1)
						{
							installationPossible = false;
							break;
						}
					}

					if (installationPossible == false)
						break;
				}
			}
			if (direction == 2)
			{
				for (int k = std::max(0, y - 1); k <= std::min(9, y + ships[i]); ++k)
				{
					for (int j = std::max(0, x - 1); j <= std::min(9, x + 1); ++j)
					{
						if (field[k][j] == 1)
						{
							installationPossible = false;
							break;
						}
					}

					if (installationPossible == false)
						break;
				}
			}

			// esli est' vozmozhnost' postavit' korabl' to stavim
			if (installationPossible)
			{
				if (direction == 0)
					for (int j = x; j < x + ships[i]; ++j)
						field[y][j] = 1;

				if (direction == 2)
					for (int j = y; j < y + ships[i]; ++j)
						field[j][x] = 1;

				setShip = true;
			}
		}
	}

	std::cout << it << std::endl;
}


void Battleships::manualInstallationOfShips(int** field, std::vector<int>& ships)
{

}



