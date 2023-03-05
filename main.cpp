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
		if (returnLogic == "f")
			referi.input();
		else if (returnLogic == "c")
			referi.input();
		else if (returnLogic == "r")
			referi.restart();

		while (1)
		{
			returnLogic = referi.logic();

			if (returnLogic == "r")
				break;

			if (returnLogic == "c")
				break;
		}
	}
}