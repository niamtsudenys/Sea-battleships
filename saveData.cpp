#include "saveData.h"

saveData::saveData() : path("fileForScore.txt") {}

void saveData::saveDataInFile(int& victoryMan, int& victoryBot)
{
	fs.open(path, std::fstream::out);

	if (!fs.is_open())                          // esli fail ne otkrylsya to vyvodim o tom sms v console
		std::cout << "Error opening file!";
	else
		fs << victoryMan << std::endl << victoryBot;  // sohranyaem danye v file
	
	fs.close();
}

void saveData::getDataFromFile(int& victoryMan, int& victoryBot)
{
	fs.open(path, std::fstream::in);

	if (!fs.is_open())                    // esli fail ne otkrylsya znachit takogo file eshe net i poetomu vyzyvaem fn saveDataInFile(ob)
		saveDataInFile(victoryMan, victoryBot);               // chtoby ona sozdala file i zapisala danie v nem
	else
		fs >> victoryMan >> victoryBot; // scityvaem danie iz file i soxranyaem ih v polya obiecta ob
		
	fs.close();
}

