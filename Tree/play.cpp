#include "Tree.h"
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GM akinator(new tree(new node("��� �������?")));
	akinator._memory._root->yes = new node("�������");
	akinator._memory._root->no = new node("����������");
	akinator.load();
	akinator.play();
	return 0;
}