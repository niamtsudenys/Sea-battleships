#include "screen.h"
#include "referees.h"

int main()
{
	srand(time(NULL));
	
	referees referi;

	referi.showScreen();

	referi.loadShips();

	std::string returnLogic = "f";

	while (true)
	{
		if (returnLogic == "f")              // pervyi vhod v input
			referi.input();
		else if (returnLogic == "c")
			referi.input();
		else if (returnLogic == "r")
			referi.restart(false);
		else if (returnLogic == "m")
			referi.restart(true);

		while (1)
		{
			returnLogic = referi.logic();

			if (returnLogic == "r")          // restart s random set ships
				break;
			else if (returnLogic == "m")          // restart s manual set ships
				break;
			else if (returnLogic == "c")          // kapitulyatsyia man
				break;
		}
	}
}