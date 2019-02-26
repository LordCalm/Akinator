#include "Akinator.h"
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GM akinator;
	akinator.menu();
	return 0;
}