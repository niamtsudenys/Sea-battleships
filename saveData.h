#pragma once
#include <fstream>
#include <iostream>

class saveData
{
	std::string path;
	std::fstream fs;

public:

	saveData();

	void saveDataInFile(int& victoryMan, int& victoryBot);

	void getDataFromFile(int& victoryMan, int& victoryBot);
};