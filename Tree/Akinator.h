#pragma once
#include "Tree.h"
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

typedef struct GM {
	tree _memory;

	GM(tree *opened = new tree(new node("Akinator")));

	void menu();
	void play();
	void play_in(node *root_ptr);
	void save();
	void save_in(node *root_ptr);
	void load();
}GM;
