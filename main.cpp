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
//    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // �������� ����������
//    INPUT_RECORD InputRecord; // ������������ ��� ����������� ���������� � ������� ���������� � ���������� ������� ������
//    DWORD Events; // unsigned long
//    COORD coord; // ��� ��������� X, Y
//
//    /*��������� ��������� �������*/
//    DWORD prev_mode;
//    GetConsoleMode(hin, &prev_mode);
//    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
//
//    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // ��������� ��������� ����
//
//    while (true)
//    {
//        ReadConsoleInput(hin, &InputRecord, 1, &Events); // ���������� 
//
//        if (InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED) // ������ ��������
//        {
//            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
//            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//            cout << "Kolesiko nazhato - X" << coord.X << ", Y = " << coord.Y << endl;
//        }
//        else if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) // ������ ������
//        {
//            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
//            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//            cout << "right - X" << coord.X << ", Y = " << coord.Y << endl;
//        }
//        else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // ����� ������
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