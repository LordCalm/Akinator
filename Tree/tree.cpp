#include "Tree.h"

node::node(string key) :
	_key(key),
	yes(NULL),
	no(NULL)
{}

tree::tree(node *root) :
_root(root)
{}

void tree::insert(string data, node *root_ptr)
{
	cout << "Введите новый вопрос" << endl;
	string question;
	getline(cin, question);
	if (question == "выход") return;
	root_ptr->yes = new node(root_ptr->_key);
	root_ptr->_key = question;
	cout << "Введите нового персонажа" << endl;
	string stringacter;
	getline(cin, stringacter);
	if (stringacter == "выход") return;
	cout << "Новый персонаж положительно отвечает на вопрос?\n[д] или [н]" << endl;
	string answer;
	getline(cin, answer);
	if (answer == "н")
	{
		root_ptr->no = new node(stringacter);
	}
	else
	{
		root_ptr->no = new node(root_ptr->yes->_key);
		root_ptr->yes->_key = stringacter;
	}
}

