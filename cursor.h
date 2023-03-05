#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>


class cursor
{
public:

    ///////////////////////////////////  polojenie cursora v console  /////////////////////////////
    enum class color
    {
        black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
        lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
    };

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    void set_col(color foreground, color background);

    void gotoxy(int x, int y);

    ///////////////////////////////////  polojenie myshy v console  /////////////////////////////

    std::vector<int> mousePosition{ 0, 0 };  // conteiner dlya hraneniya coordinat mishki

    void posXY();                            // nahodim coord mouse v console

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); //  poluchayem deskriptor
    INPUT_RECORD InputRecord; // ispol'zuyetsya dlya vozvrashcheniya informatsii o vkhodnykh soobshcheniyakh v konsol'nom vkhodnom bufere
    DWORD Events; // unsigned long
    COORD coord; // dlya coordinaty X, Y
};

