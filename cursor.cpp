#include "cursor.h"

void cursor::set_col(color foreground, color background)
{
	SetConsoleTextAttribute(hout, ((short)background << 4) | (short)foreground);
}

void cursor::gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void cursor::posXY()
{
    // zapreshyaem vydelenie consoli
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // razreshaem obrabotku mishi


    ReadConsoleInput(hin, &InputRecord, 1, &Events); // schityvanie 

    if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // levaya knopka
    {
        coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
        coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

        mousePosition.at(0) = coord.X;
        mousePosition.at(1) = coord.Y;

        //coord.X = 0;
       // coord.Y = 0;
    }
}
