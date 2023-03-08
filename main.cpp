#include "screen.h"
#include "referees.h"
#include "saveData.h"

int main()
{
	srand(time(NULL));
	
	referees referi;
	
	// scityvaem danye iz file chtoby obnovity kolichestvo poped man i bot
	referi.SaveData.getDataFromFile(referi.man.victory, referi.bot.victory); 

	referi.showScreen();                     // risuem console

	referi.loadShips();                      // sozdaem korabli dlya man i bot

	std::string returnLogic = "f";           // peremenaya dlya pervoi iteratsii tsikla na 20 storke

	while (true)
	{
		if (returnLogic == "f")              // pervyi vhod tsikl i sootvetstveno v input
			referi.input();
		else if (returnLogic == "c")         // povtor tsikla pri kapitulyatsii
			referi.input();
		else if (returnLogic == "r")         // povtor tsikla s random set ships pri oconchanii partii
			referi.restart(false);
		else if (returnLogic == "m")         // povtor tsikla s manual set ships pri oconchanii partii
			referi.restart(true);

		while (1)
		{
			returnLogic = referi.logic();

			if (returnLogic == "r")               // restart s random set ships
				break;
			else if (returnLogic == "m")          // restart s manual set ships
				break;
			else if (returnLogic == "c")          // kapitulyatsyia man
				break;
		}
	}
}