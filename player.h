#pragma once
#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <time.h>
#include "screen.h"
#include "ships.h"
 
class player : public screen
{
public:

	int sizeField;
	bool lost;
	bool shoot;
	bool shootMod;
	int countShip;

	int coordPritselX;  // coordinaty pritsela
	int coordPritselY;

	int firstShotI;
	int firstShotJ;

	int lastShotDir;

	bool capitulation;
	bool restart;

	bool mouseControl;

	int victory;

	int** field;

	std::vector <ships> shipsPlayer;

	std::vector<int> dirs{ 3, 2, 1, 0 };       // konteiner dlya hraneniya napravleniya poiska korablya chtoby dobity

	player();
	~player();

	// sozdaem 10 corablei 
	void addShips(std::vector<int>& decksShips, std::vector<int>& coordXYLateralShips);

	void randomSetShips();
	
	//proverka vozmojnosti postanovki korablya
	bool checkSet(int shipSize, int x, int y, int direction);

	// ustanovka corablya na pole
	void setShip(int shipSize, int x, int y, int direction, bool& setShipOnField);

	void shipDataUpdate(ships& ship, int x, int y, int direction);

	int manualSetShips();

	//risuem pole  1 - man, 2 - pole bota
	void drawOnTheField(int numberField = 1);

	void clearMasiv();                         

	void attackMan(bool& turn, player& bot);

	void attackBot(bool& turn, player& man);

	// proveryaem esli kakie korabli potoplenye
	bool checkIfTheShipIsAlive(player& Player);

	// risuem granitsu vokrug potoplenogo korablya
	void sketchingTheBorderAroundTheSunkenShip(ships& ship, player& Player);

	void showMasiv();

	void navedenieNaTseliMishkoi();

	std::string mouseOrKeybordControl(int i = 0, int instalOrHit = 0);

	void forMouseOrKeybordControl(int i = 0, int instalOrHit = 0);
};