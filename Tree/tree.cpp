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
	cout << "������� ����� ������" << endl;
	string question;
	getline(cin, question);
	if (question == "�����") return;
	root_ptr->yes = new node(root_ptr->_key);
	root_ptr->_key = question;
	cout << "������� ������ ���������" << endl;
	string stringacter;
	getline(cin, stringacter);
	if (stringacter == "�����") return;
	cout << "����� �������� ������������ �������� �� ������?\n[�] ��� [�]" << endl;
	string answer;
	getline(cin, answer);
	if (answer == "�")
	{
		root_ptr->no = new node(stringacter);
	}
	else
	{
		root_ptr->no = new node(root_ptr->yes->_key);
		root_ptr->yes->_key = stringacter;
	}
}

