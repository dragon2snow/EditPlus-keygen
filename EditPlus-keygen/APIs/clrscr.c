/* 
 * File name : clrscr.c
 * API description : Has the same effect as system("cls");.
 * Author : wxx9248
 */

#include <windows.h>
#include <stdio.h>

#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void _cls_main_(HANDLE);

void clrscr(void)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	_cls_main_(hStdOut);
}

void _cls_main_(HANDLE hConsole)

{

	COORD coordScreen = {0, 0};	// When cleared, set back to (0, 0)
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;	// Save the buffer info
	DWORD dwConSize;	// How many chars can be contained ? This is set in line 28.

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);

	PERR(bSuccess, "GetConsoleScreenBufferInfo");

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;	// Line 28

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);	// Fill in the blanks
	PERR(bSuccess, "FillConsoleOutputCharacter");

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");	// Fill in the console attr.

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);	// Back to (0, 0)
	PERR(bSuccess, "SetConsoleCursorPosition");

	return;

}