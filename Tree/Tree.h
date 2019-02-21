#pragma once
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

typedef struct node {
	string _key;
	node *yes;
	node *no;
	node(string key);
}node;

typedef struct tree {
	node *_root;
	void insert(string data, node *root_ptr);
	tree(node *root);
}tree;

typedef struct GM {
	tree _memory;
	void play();
	void play_in(node *root_ptr);
	void save();
	void save_in(node *root_ptr);
	void load();
	GM(tree *opened);
}GM;