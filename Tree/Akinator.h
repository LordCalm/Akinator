#pragma once
#include "Tree.h"
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

class GM {
private:
	tree _memory;
	void play_in(node *root_ptr);
	void save_in(node *root_ptr);
public:
	GM(tree *opened = new tree(new node("Akinator")));

	void menu();
	void play();
	void save();
	void load();
};
