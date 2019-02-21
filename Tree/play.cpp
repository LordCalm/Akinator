#include "Tree.h"
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GM akinator(new tree(new node("Это мужчина?")));
	akinator._memory._root->yes = new node("Арагорн");
	akinator._memory._root->no = new node("Галадриэль");
	akinator.load();
	akinator.play();
	return 0;
}