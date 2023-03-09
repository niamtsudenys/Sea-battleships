#include "player.h"

player::player() : sizeField(10), lost(0), shoot(0), shootMod(0), coordPritselX(0), coordPritselY(0),
countShip(0), firstShotI(0), firstShotJ(0), lastShotDir(0), capitulation(0), restart(0), mouseControl(0),
victory(0)
{
	field = new int* [sizeField];

	for (int i = 0; i < sizeField; ++i)
	{
		field[i] = new int[sizeField] {};
	}
}

player::~player()
{
	for (int i = 0; i < sizeField; ++i)
	{
		delete[] field[i];
	}

	delete[] field;
}

void player::addShips(std::vector<int>& decksShips, std::vector<int>& coordXYLateralShips)
{
	for (int i = 0; i < sizeField; ++i)
	{
		ships tempShip;

		tempShip.deck = decksShips.at(i);
		tempShip.latteralCoordinates = coordXYLateralShips.at(i);

		shipsPlayer.push_back(tempShip);
	}
}

void player::randomSetShips()
{
	clearMasiv();

	for (auto& ship : shipsPlayer)
	{
		int x, y;                                     // coordinaty nachalynih tochek korablya
		int direction = 0;                            // napravlenie rosta korablya
		bool setShipOnField = 0;

		while (!setShipOnField)
		{
			x = rand() % sizeField;                   // pervichnaya pozitsiya
			y = rand() % sizeField;

			int tempX = x;                            // zapominaem pervonachalynye coordinaty
			int tempY = y;

			direction = rand() % 4;                   // generatsiya sluchaynogo napravleniya rosta korablya

			if (checkSet(ship.deck, x, y, direction)) // proverka vozmojnosti postanovki korablya v pole
			{
				// obnovlyaem danye tecuchego sudna
				shipDataUpdate(ship, tempX, tempY, direction);

				// meniaem tvet bokobyh korabley
				paintLateralShips(ship.latteralCoordinates, ship.deck, ship.color);
				
				// ustanovka korablya
				setShip(ship.deck, tempX, tempY, direction, setShipOnField); 
			}
		}
	}
}

bool player::checkSet(int shipSize, int x, int y, int direction)
{
	bool installationPossible = true;

	for (int i = 0; i < shipSize; ++i)
	{
		if (x < 0 || y < 0 || x >= sizeField || y >= sizeField)
		{
			installationPossible = false;
			break;
		}

		if (field[x][y] >= 1                                   ||
			field[x][std::min(9, y + 1)] >= 1                  ||
			field[x][std::max(0, y - 1)] >= 1                  ||
			field[std::min(9, x + 1)][y] >= 1                  ||
			field[std::min(9, x + 1)][std::min(9, y + 1)] >= 1 ||
			field[std::min(9, x + 1)][std::max(0, y - 1)] >= 1 ||
			field[std::max(0, x - 1)][y] >= 1                  ||
			field[std::max(0, x - 1)][std::min(9, y + 1)] >= 1 ||
			field[std::max(0, x - 1)][std::max(0, y - 1)] >= 1)
		{
			installationPossible = false;
			break;
		}

		switch (direction)
		{
		case 0:
			y++;
			break;
		case 1:
			x++;
			break;
		case 2:
			y--;
			break;
		case 3:
			x--;
			break;
		}
	}

	return installationPossible;
}

void player::setShip(int shipSize, int x, int y, int direction, bool& setShipOnField)
{
	for (int i = 0; i < shipSize; i++)
	{
		field[x][y] = 1;

		switch (direction)
		{
		case 0:
			y++;
			break;
		case 1:
			x++;
			break;
		case 2:
			y--;
			break;
		case 3:
			x--;
			break;
		}
	}

	setShipOnField = !setShipOnField;

	++countShip;
}

void player::shipDataUpdate(ships& ship, int x, int y, int direction)
{
	ship.color = 1;
	ship.coordX = x;
	ship.coordY = y;
	ship.direction = direction;

	if (direction == 2)                    
	{
		ship.coordY = y + 1 - ship.deck;     
		ship.direction = 0;
	}

	if (direction == 3)
	{
		ship.coordX = x + 1 - ship.deck;
		ship.direction = 1;
	}
}

int player::manualSetShips()
{
	message(sms.at(16));
	clearMasiv();

	int x = 30;                                      // coordinaty nachalynih tochek korablya
	int y = 11;
	int direction = 0;                               // napravlenie rosta korablya

	for (auto& ship : shipsPlayer)
	{
		bool setShipOnField = false;
		
		while (!setShipOnField)
		{
			bool set = false;

			drawOnTheField();                        // risuem pole s uchetom izmeneniy

			if (direction == 0)
			{
				for (int i = 0; i < ship.deck; ++i)  //risuem corabely gorizontalino
				{
					gotoxy(x + 2 * i, y);

					set_col(color::blue, color::blue);
					std::cout << "OO";

					gotoxy(x, y);
				}
			}
			else
			{
				for (int i = 0; i < ship.deck; ++i)  //risuem corabely gorizontalino
				{
					gotoxy(x, y + i);
					set_col(color::blue, color::blue);
					std::cout << "OO";
					gotoxy(x, y);
				}
			}
			
			if (!mouseControl)   // upravlenie klaviaturoi
			{
				int ch = _getch();

				switch (ch)
				{
				case 77:                        // peremechaem corabeli vpravo
					x += 2;
					break;
				case 'd':
					x += 2;
					break;
				case 75:
					x -= 2;                     // peremechaem corabeli vlevo
					break;
				case 'a':
					x -= 2;
					break;
				case 80:
					++y;                        // peremechaem corabeli vniz
					break;
				case 's':
					++y;
					break;
				case 72:
					--y;                        // peremechaem corabeli vverh
					break;
				case 'w':
					--y;
					break;
				case 32:
					direction += 1;             // menyaem polojenie
					break;
				case 'q':
					direction += 1;
					break;
				case 13:
					set = true;                 // stavim korabeli
					break;
				case 'b':
					countShip = 0;
					clearLiterEandB();
					return 1;
					break;
				case 'e':
					message(sms.at(11));        // knopka exit
					Sleep(500);
					exit(0);
					break;
				}
			}
			else                                // upravlenie mishkoi
			{
				navedenieNaTseliMishkoi();

				clearLiterEandB();

				if (mousePosition.at(0) >= 30 && mousePosition.at(0) <= 49 && mousePosition.at(1) >= 11 && mousePosition.at(1) <= 20)
				{
					x = mousePosition.at(0);   // pritsel dvigaetsya toliko togda kogda mishka vnutri polya bota
					y = mousePosition.at(1);
				}

				if (x % 2 != 0)
					x = x - 1;

				if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				{
					direction += 1;            // menyaem polojenie
				}

				if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					set = true;                // stavim korabeli
				}

				if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePosition.at(0) >= 110
					&& mousePosition.at(0) <= 114 && mousePosition.at(1) == 29)
				{
					message(sms.at(11));      // knopka exit
					Sleep(500);
					exit(0);
				}

				if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePosition.at(0) >= 100
					&& mousePosition.at(0) < 104 && mousePosition.at(1) == 29)
				{
					countShip = 0;
					clearLiterEandB();   // knopka back
					return 1;
				}
			}

			if (direction > 1)
				direction = 0;
            
			// ne vihodim iz polya s pravoi storony kogda sudno stoit gorizontalyno
			if (direction == 0 && x > 50 - ship.deck * 2)
				x = 50 - ship.deck * 2; 
			
			// ne vihodim iz polya s pravoi storony kogda sudno stoit vertikalino
			if (direction == 1 && x > 30 + 2 * sizeField - 2)
				x = 30 + 2 * sizeField - 2;     
			
			// ne vihodim iz polya s levoi storony 
			if (x < 30)
				x = 30;                                     
	
			// ne vihodim iz polya snizu  kogda sudno stoit vertikalino
			if (direction && y > 21 - ship.deck)
				y = 21 - ship.deck;
			
			// ne vihodim iz polya snizu  kogda sudno stoit gorizontalyno
			if (!direction && y > 11 + sizeField - 1)
				y = 11 + sizeField - 1;
			
            // ne vihodim iz polya sverhu
			if (y < 11)
				y = 11;
			
			if (set)
			{
				int i = y - 11;
				int j = (x - 30) / 2;
				
				if (checkSet(ship.deck, i, j, direction)) // proverka vozmojnosti postanovki korablya v pole
				{
					// obnovlyaem danye tecuchego sudna
					shipDataUpdate(ship, i, j, direction);

					// meniaem tvet bokobyh korabley
					paintLateralShips(ship.latteralCoordinates, ship.deck, ship.color);

					// ustanovka korablya
					setShip(ship.deck, i, j, direction, setShipOnField);
				}
			}
		}

		gotoxy(120 / 2 - 3, 15);
		set_col(color::red, color::white);
		std::cout << (10 - countShip) << " more";        // vyvodim sms o kolichestve neustanovlenyh korabley na pole

		if (countShip == 10)
			message(sms.at(17));
	}

	return 0;
}

void player::drawOnTheField(int numberField)
{
	int coordX0 = 0;
	int coordY0 = 0;
	
	if (numberField == 1)
	{
		coordX0 = 30;                                  // coordinaty pervoi tochki polya cheloveka
		coordY0 = 11;

		for (int i = 0; i < sizeField; ++i)
		{
			for (int j = 0; j < sizeField; ++j)
			{
				gotoxy(coordX0 + 2 * j, coordY0 + i);  // risuem pole s uchetom izmeneniy 

				if (field[i][j] == 1)
					set_col(color::blue, color::blue);
				else if (field[i][j] == 0)
					set_col(color::lightcyan, color::lightcyan);
				else if (field[i][j] == 2)
					set_col(color::red, color::red);
				else if (field[i][j] == 3)
					set_col(color::lightgray, color::lightgray);

				std::cout << "OO";
			}
		}
	}
	else if (numberField == 2)
	{
		coordX0 = 70;                                 // coordinaty pervoi tochki polya bota
		coordY0 = 11;

		for (int i = 0; i < sizeField; ++i)
		{
			for (int j = 0; j < sizeField; ++j)
			{
				gotoxy(coordX0 + 2 * j, coordY0 + i);  // risuem pole s uchetom izmeneniy 

				if (field[i][j] == 1)
					set_col(color::lightcyan, color::lightcyan);
				else if (field[i][j] == 0)
					set_col(color::lightcyan, color::lightcyan);
				else if (field[i][j] == 2)
					set_col(color::red, color::red);
				else if (field[i][j] == 3)
					set_col(color::lightgray, color::lightgray);

				std::cout << "OO";
			}
		}
	}

	set_col(color::black, color::lightcyan);
}

void player::clearMasiv()
{
	for (int i = 0; i < sizeField; ++i)
	{
		for (int j = 0; j < sizeField; ++j)
		{
			field[i][j] = 0;
		}
	}
}

void player::attackMan(bool& turn, player& bot)
{
	message(sms.at(1));                      // sms chto nash hod

	int x = coordPritselX;
	int y = coordPritselY;

	while (true)
	{
		if (bot.countShip == 0)              // proveryaem esli esti korabli u bota
		{
			bot.lost = 1;
			break;
		}

		if (countShip == 0)                  // proveryaem esli esti korabli u bota
		{
			lost = 1;
			break;
		}

		bot.drawOnTheField(2);              // obnovlyaem pole bota

		shoot = false;

		gotoxy(x, y);
		set_col(color::darkgray, color::darkgray);   //risuem pritsel
		std::cout << "OO";
		gotoxy(x, y);

		int ch = 0;

		if (!mouseControl)      // upravlenie klaviaturoi
		{
			ch = _getch();

			switch (ch)
			{
			case 77:            // peremechaem pritsel vpravo
				x += 2;
				break;
			case 'd':
				x += 2;
				break;
			case 75:
				x -= 2;        // peremechaem pritsel vlevo
				break;
			case 'a':
				x -= 2;
				break;
			case 80:
				++y;          // peremechaem pritsel vniz
				break;
			case 's':
				++y;
				break;
			case 72:
				--y;          // peremechaem pritsel vverh
				break;
			case 'w':
				--y;
				break;
			case 13:
				shoot = true; // vystrel man
				break;
			case 'e':
				message(sms.at(11));
				Sleep(500);
				exit(0);
				break;
			case 'c':
				capitulation = 1;
				countShip = 0;
				break;
			}
		}
		else              // upravlenie mishkoi
		{
			clearLiterEandB();
			clearLiterC();
			
			navedenieNaTseliMishkoi();
			if (mousePosition.at(0) >= 70 && mousePosition.at(0) <= 89 && mousePosition.at(1) >= 11 && mousePosition.at(1) <= 20)
			{
				x = mousePosition.at(0); // pritsel dvigaetsya toliko togda kogda mishka vnutri polya bota
				y = mousePosition.at(1);
			}

			if (x % 2 != 0)
				x = x - 1;

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				shoot = true;  // vystrel

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePosition.at(0) >= 82
				&& mousePosition.at(0) <= 93 && mousePosition.at(1) == 29)
			{
				capitulation = 1;
				countShip = 0;
			}

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePosition.at(0) >= 110
				&& mousePosition.at(0) <= 114 && mousePosition.at(1) == 29)
			{
				message(sms.at(11));    // knopka exit
				Sleep(500);
				exit(0);
			}
		}

		if (x > 88)       // ne vihodim iz polya s pravoi storony 
			x = 88;

		if (x < 70)       // ne vihodim iz polya s levoi storony 
			x = 70;

		if (y > 20)       // ne vihodim iz polya snizu 
			y = 20;

		if (y < 11)       // ne vihodim iz polya sverhu
			y = 11;


		///////////////////////////////////////////////////////// proverka na popadanie ///////////////////////////
		// 0 - pustoe mesto gde eshe net popadniya
		// 1 - paluba korabelya po kotoroy eshe ne strelyali
		// 2 - povrejdenaya paluba
		// 3 - pustaya kletka po kotoroy strelyali
		if (shoot)
		{
			int i = y - 11;        // perehodim ot koordinat pikselei v konsoli k koordinatam elemenya masiva
			int j = (x - 70) / 2;

			// esly popadaem v pustoe mesto to gde net korablya to otmechaem chto po etoy cletke byl vystrel
			if (bot.field[i][j] == 0)
			{
				message(sms.at(5), 2);          // sms shto man ne popal
				Sleep(500);                     // zaderjka 
				bot.field[i][j] = 3;
				turn = !turn;                   // hod perehodit k botu

				coordPritselX = x;              // zapominaem posledniiu kletku
				coordPritselY = y;

				break;
			}

			if (bot.field[i][j] == 2 || bot.field[i][j] == 3)
				break;

			if (bot.field[i][j] == 1)
			{
				message(sms.at(3), 2);          // sms shto man popal
				Sleep(350);

				bot.field[i][j] = 2;
				checkIfTheShipIsAlive(bot);     // proveryaem esli sudno potopili
			}
		}

		coordPritselX = x;                      // zapominaem posledniiu kletku
		coordPritselY = y;
		bot.drawOnTheField(2);
	}
}

void player::attackBot(bool& turn, player& man)
{
	message(sms.at(2), 1);                      // sms chto nash hod
	Sleep(700);

	while (true)
	{
		if (man.countShip == 0)              // proveryaem esli esti korabli u bota
		{
			man.lost = 1;
			break;
		}

		man.drawOnTheField(1);

		///////////////////////////////////////////////////////// proverka na popadanie ///////////////////////////
			// 0 - pustoe mesto gde eshe net popadniya
			// 1 - paluba korabelya po kotoroy eshe ne strelyali
			// 2 - povrejdenaya paluba
			// 3 - pustaya kletka po kotoroy strelyali

		if (!shootMod)
		{   
			dirs.clear();                  // ohichaem vector
			dirs = { 3, 2, 1, 0 };         // posle togo kak zatopili korabeli vostanavlivaem vse napravleniya
			
			do
			{
				firstShotI = rand() % sizeField;
				firstShotJ = rand() % sizeField;
			} while (man.field[firstShotI][firstShotJ] > 1);

			// esly popadaem v pustoe mesto to gde net korablya to otmechaem chto po etoy cletke byl vystrel
			if (man.field[firstShotI][firstShotJ] == 0)
			{
				message(sms.at(5), 2);                   // sms shto bot ne popal
				Sleep(500);                             // zaderjka 

				man.field[firstShotI][firstShotJ] = 3;
				turn = !turn;                            // hod perehodit k man

				man.drawOnTheField(1);

				break;
			}

			if (man.field[firstShotI][firstShotJ] == 1)
			{
				message(sms.at(4), 2);                  // sms shto bot popal
				Sleep(500);

				man.field[firstShotI][firstShotJ] = 2;

				if (!checkIfTheShipIsAlive(man))        // proveryaem esli sudno potopili
					shootMod = true;

				coordPritselX = firstShotJ;             // zapominaem coord pervogoego vystrela po korabliu
				coordPritselY = firstShotI;

				lastShotDir = dirs.at(dirs.size() - 1); // napravlenie ravno poslednemu elementu
				dirs.pop_back();                        // udaliaem odno napravlenie iz vektora

				man.drawOnTheField(1);
				break;
			}
		}
		else
		{
			bool changeDir = false;
			
			switch (lastShotDir)
			{
			case 0:
				if (coordPritselX < 9)
					++coordPritselX;
				else
					changeDir = true;
				break;
			case 1:
				if (coordPritselX > 0)
					--coordPritselX;
				else
					changeDir = true;
				break;
			case 2:
				if (coordPritselY < 9)
					++coordPritselY;
				else
					changeDir = true;
				break;
			case 3:
				if (coordPritselY > 0)
					--coordPritselY;
				else
					changeDir = true;
				break;
			}

			if (changeDir)
			{
				lastShotDir = dirs.at(dirs.size() - 1); // meniaem napravlenie streliby
				dirs.pop_back();                        // udaliaem odno napravlenie iz vektora

				coordPritselX = firstShotJ;             // vostanavlivaem coord pervogo vystrela
				coordPritselY = firstShotI;

				break;
			}

			if (man.field[coordPritselY][coordPritselX] == 0)
			{
				message(sms.at(5), 2);                   // sms shto bot ne popal
				Sleep(500);                             // zaderjka 

				man.field[coordPritselY][coordPritselX] = 3;
				turn = !turn;                            // hod perehodit k man

				lastShotDir = dirs.at(dirs.size() - 1); // meniaem napravlenie streliby
				dirs.pop_back();                        // udaliaem odno napravlenie iz vektora

				coordPritselX = firstShotJ;             // vostanavlivaem coord pervogo vystrela
				coordPritselY = firstShotI;

				man.drawOnTheField(1);
				break;
			}

			if (man.field[coordPritselY][coordPritselX] == 3)
			{
				lastShotDir = dirs.at(dirs.size() - 1); // meniaem napravlenie streliby
				dirs.pop_back();                        // udaliaem odno napravlenie iz vektora

				coordPritselX = firstShotJ;             // vostanavlivaem coord pervogo vystrela
				coordPritselY = firstShotI;

				break;
			}

			if (man.field[coordPritselY][coordPritselX] == 1)
			{
				message(sms.at(4), 2);                  // sms shto bot popal
				Sleep(500);

				man.field[coordPritselY][coordPritselX] = 2;

				if (checkIfTheShipIsAlive(man))         // proveryaem esli sudno potopili
				{
					shootMod = false;                   // bot opiaty budet streliati random
					dirs.clear();                       // ohichaem vector
					dirs = { 3, 2, 1, 0 };              // posle togo kak zatopili korabeli vostanavlivaem vse napravleniya
				}

				man.drawOnTheField(1);
				break;
			}
		}
	}
}

bool player::checkIfTheShipIsAlive(player& Player)
{
	bool drowned = false;                               // peremenaya v kotoroy budem hranity info utonulo sudno ili net
	int countLifeDeck = 0;                              // kolichestvo potoplenyh palub
	
	for (auto& ship : Player.shipsPlayer)
	{
		drowned = false;

		if (ship.life)                                  // proverku vypolnyaem toliko esli danyi korabely ne potoplen
		{
			switch (ship.direction)                    
			{
			case 0:                                    // korabeli stoit gorizontalyno
				countLifeDeck = 0;

				for (int i = 0; i < ship.deck; ++i)
				{
					if (Player.field[ship.coordX][ship.coordY + i] == 2)
						++countLifeDeck;
					else
						break;
					
					if (ship.deck == countLifeDeck)
						drowned = true;
				}

				break;
			case 1:                                     // korabeli stoit vertikalyno
				countLifeDeck = 0;

				for (int i = 0; i < ship.deck; ++i)
				{
					if (Player.field[ship.coordX + i][ship.coordY] == 2)
						++countLifeDeck;
					else
						break;

					if (ship.deck == countLifeDeck)
						drowned = true;
				}

				break;
			}

			if (drowned)
			{
				message(sms.at(6), 2);                  // sms shto korabely ytonul
				Sleep(450);
				ship.life = false;                      // korabely potoplen
				ship.color = 2;                         // bokovoy korablik perekrashivaem v krasnyi tsvet
				paintLateralShips(ship.latteralCoordinates, ship.deck, ship.color);
				sketchingTheBorderAroundTheSunkenShip(ship, Player);

				Player.countShip = Player.countShip - 1; // minus 1 korabeli

				break;
			}
		}
	}

	return drowned;
}

void player::sketchingTheBorderAroundTheSunkenShip(ships& ship, player& Player)
{
	// esli korabely potoplen to vokrug nego ne strelyaem uje, bokrug korablya vstavlyaem cifru 3
	switch (ship.direction)
	{
	case 0: // esli korabely stoit gorizontalyno
		for (int i = std::max(0, ship.coordX - 1); i <= std::min(9, ship.coordX + 1); ++i)
		{
			for (int j = std::max(0, ship.coordY - 1); j <= std::min(9, ship.coordY + ship.deck); ++j)
			{
				Player.field[i][j] = 3;
			}
		}

		for (int j = ship.coordY; j < ship.coordY + ship.deck; ++j)
		{
			Player.field[ship.coordX][j] = 2;
		}

		break;

	case 1:
		for (int i = std::max(0, ship.coordY - 1); i <= std::min(9, ship.coordY + 1); ++i)
		{
			for (int j = std::max(0, ship.coordX - 1); j <= std::min(9, ship.coordX + ship.deck); ++j)
			{
				Player.field[j][i] = 3;
			}
		}

		for (int i = ship.coordX; i < ship.coordX + ship.deck; ++i)
		{
			Player.field[i][ship.coordY] = 2;
		}

		break;
	}
}

void player::navedenieNaTseliMishkoi()
{
	// zapreshyaem vydelenie consoli
	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // razreshaem obrabotku mishi

	ReadConsoleInput(hin, &InputRecord, 1, &Events); // schityvanie 

	coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
	coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

	mousePosition.at(0) = coord.X;
	mousePosition.at(1) = coord.Y;
}

std::string player::mouseOrKeybordControl(int i, int instalOrHit)
{
	gotoxy(100, 29);
	set_col(color::blue, color::white);
	std::cout << "Back b";

	gotoxy(110, 29);
	std::cout << "Exit e";
	
	bool stopCicl = 0;

	forMouseOrKeybordControl(i, instalOrHit);

	while (!stopCicl)
	{
		if (_kbhit())
		{
			int ch = _getch();

			switch (ch)
			{
			case 80:
				++i;          // peremechaem vniz
				break;
			case 's':
				++i;
				break;
			case 72:
				--i;          // peremechaem vverh
				break;
			case 'w':
				--i;
				break;
			case 13:
				stopCicl = true;
				break;
			case 'b':
				clearLiterEandB();
				return "back";
				break;
			case 'e':
				message(sms.at(11));
				Sleep(500);
				exit(0);
				break;
			}

			if (i < 0)
				i = 1;

			if (i > 1)
				i = 0;

			forMouseOrKeybordControl(i, instalOrHit);
		}
		else
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000) // esli najali knopku mishi
			{
				posXY();

				if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (mousePosition.at(0) >= 50 && mousePosition.at(0) < 70) && mousePosition.at(1) == 13)
				{
					i = 0;

					break;
				}
				else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (mousePosition.at(0) >= 50 && mousePosition.at(0) < 70) && mousePosition.at(1) == 15)
				{
					i = 1;

					break;
				}
				else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (mousePosition.at(0) >= 100 && mousePosition.at(0) < 105) && mousePosition.at(1) == 29)
				{
					clearLiterEandB();

					return "back";
				}
				else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && (mousePosition.at(0) >= 110 && mousePosition.at(0) < 115) && mousePosition.at(1) == 29)
				{
					message(sms.at(11));
					Sleep(500);
					exit(0);
				}

				forMouseOrKeybordControl(i, instalOrHit);
			}
		}
	}

	if (!i)
		mouseControl = 0;
	else
		mouseControl = 1;

	return "0";
}

void player::forMouseOrKeybordControl(int i, int instalOrHit)
{
	if (!i)
		set_col(color::red, color::white);
	else
		set_col(color::blue, color::white);

	if (!instalOrHit)
	{
		gotoxy(120 / 2 - sms.at(12).length() / 2, 13);
		std::cout << sms.at(12);
	}
	else
	{
		gotoxy(120 / 2 - sms.at(14).length() / 2, 13);
		std::cout << sms.at(14);
	}

	if (i)
		set_col(color::red, color::white);
	else
		set_col(color::blue, color::white);

	
	if (!instalOrHit)
	{
		gotoxy(120 / 2 - sms.at(13).length() / 2, 15);
		std::cout << sms.at(13);
	}
	else
	{
		gotoxy(120 / 2 - sms.at(15).length() / 2, 15);
		std::cout << sms.at(15);
	}

	gotoxy(119, 0);
}