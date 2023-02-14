#include "player.h"

player::player() : sizeField(10), defeat(0)
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
	int x = 0;                                    // coordinaty pervoy tochki korablya
	int y = 0;
	bool direction = 0;                           // napravlenie rosta korablya
	int it = 0;
	
	for (auto& ship : shipsPlayer)
	{
		bool setShip = false;                     // true esli korabeli ustanovilsya
		int iteration = 0;
		
		while (!setShip)
		{
			++iteration;
			++it;
			bool installationPossible = true;     // true esli danyi korabeli vozmojno ustanovity
			
			srand(time(NULL));
		
			int direction = 1;// rand() % 2;           // generatsiya sluchaynogo napravleniya rosta korablya

			do
			{
				x = rand() % sizeField;           // randomnaya coordinata x 
				// esli korabeli ne pomechyaetsa v pole ot tochki x, y vpravo to tsycl opyaty sraboyaet
			} while (!direction && sizeField - x < ship.deck);
		
			do
			{
				y = rand() % sizeField;          // randomnaya coordinata y 
				// esli korabeli ne pomechyaetsa v pole ot tochki x, y vniz to tsycl opyaty sraboyaet
			} while (direction && sizeField - y < ship.deck);

			////// proverka vozmojnosti postanovki korablya //////
			if (!direction)
			{
				for (int i = (y == 0) ? 0 : (y - 1); i <= (y == 9) ? 9 : (y + 1); ++i)
				{
					for (int j = (x == 0) ? 0 : (x - 1); j <= (x == 9) ? 9 : (x + ship.deck); ++j)
					{
						if (field[i][j] == 1)
						{
							// esli na mesto nashego korablya i vocrug nego stoit uje korabeli to korabeli ne stavim
							installationPossible = false;
							break;
						}
					}

					if (!installationPossible)
						break;
				}
			}
			else
			{
				for (int i = std::max(0, y - 1); i <= std::min(9, y + ship.deck); ++i)
				{
					for (int j = std::max(0, x - 1); j <= std::min(9, x + 1); ++j)
					{
						if (field[i][j] == 1)
						{
							// esli na mesto nashego korablya i vocrug nego stoit uje korabeli to korabeli ne stavim
							installationPossible = false;
							break;
						}
					}

					if (!installationPossible)
						break;
				}
			}

			// stavim korabeli na pole
			if(installationPossible)
			{ 
				if (!direction) 
				{
					for (int j = x; j < x + ship.deck; ++j)
						field[y][j] = 1;
				}
				else 
				{
					for (int i = y; i < y + ship.deck; ++i)
						field[i][x] = 1;
				}

				setShip = true;

				//ship.direction = (int)direction;
			}
		}

	}
	std::cout << it;

}