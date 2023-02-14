#include "screen.h"
#include "referees.h"

int main()
{
	referees referi;

	//referi.showScreen();

	referi.loadShips();

	//referi.input();

	referi.man.randomSetShips();

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << referi.man.field[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

//int main(int argc, char** argv)
//{
//	HWND console = GetConsoleWindow();
//
//	for (;;)
//	{
//		POINT pos;
//		GetCursorPos(&pos);
//		ScreenToClient(console, &pos);
//
//		std::cout << "cursor x = " << pos.x << std::endl;
//		std::cout << "cursor y = " << pos.y << std::endl;
//
//		//Sleep(1000);
//		_getch();
//		//system("cls");
//	}
//	
//
//	return 0;
//}

//int main()
//{
//    Battleship a;
//    a.print();
//
//    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
//    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
//    DWORD Events; // unsigned long
//    COORD coord; // для координат X, Y
//
//    /*Запретить выделение консоли*/
//    DWORD prev_mode;
//    GetConsoleMode(hin, &prev_mode);
//    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
//
//    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши
//
//    while (true)
//    {
//        ReadConsoleInput(hin, &InputRecord, 1, &Events); // считывание 
//
//        if (InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED) // нажато колесико
//        {
//            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
//            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//            cout << "Kolesiko nazhato - X" << coord.X << ", Y = " << coord.Y << endl;
//        }
//        else if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) // правая кнопка
//        {
//            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
//            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//            cout << "right - X" << coord.X << ", Y = " << coord.Y << endl;
//        }
//        else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // левая кнопка
//        {
//            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
//            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//            cout << "left - X" << coord.X << ", Y = " << coord.Y << endl;
//        }
//
//    }
//
//    return 0;
//}


//black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
//lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white