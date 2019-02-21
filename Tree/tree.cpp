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
	cout << "Новый персонаж положительно отвечает на вопрос?\nд или н" << endl;
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

void GM::play()
{
	cout << "Если Вы хотите завершить, введите \"выход\" в любой момент" << endl;
	play_in(_memory._root);
}

void GM::play_in(node *root_ptr)
{
	if (root_ptr->yes != NULL)
	{
		cout << root_ptr->_key << endl;
		string answer;
		getline(cin, answer);
		if (answer == "выход") return;
		if (answer == "д") play_in(root_ptr->yes);
		else play_in(root_ptr->no);
	}
	else
	{
		cout << "Ваш ответ " << root_ptr->_key << "\nЭто правильный ответ?" << endl;
		string answer;
		getline(cin, answer);
		if (answer == "выход") return;
		if (answer == "д")
		{
			save();
			play_in(_memory._root);
		}
		else
		{
			_memory.insert(answer, root_ptr);
			save();
			play_in(_memory._root);
		}
	}
}

void GM::save()
{
	FILE *archive = fopen("archive.txt", "w");
	fclose(archive);
	save_in(_memory._root);
}

GM::GM(tree *memory):
_memory(*memory)
{}

void GM::save_in(node *root_ptr)
{
	if (root_ptr == NULL) return;
	size_t str_size = root_ptr->_key.size();
	FILE *archive = fopen("archive.txt", "a");
	fwrite(&str_size, 1, sizeof(size_t), archive);
	fwrite(root_ptr->_key.data(), sizeof(char), str_size, archive);
	fclose(archive);

	save_in(root_ptr->yes);
	save_in(root_ptr->no);
}
/*
void GM::load(node *root_ptr)
{
	size_t str_size = 0;
	FILE *archive = fopen("archive.txt", "r");
	fread(&str_size, 1, sizeof(size_t), archive);
	string str(str_size, '\0');
	fread(&str[0], sizeof(char), str_size, archive);
	fclose(archive);
	root_ptr = new node(str);
	if (str[str.size() - 1] == (char)"?")
	{
		load(root_ptr->yes);
		load(root_ptr->no);
	}
	else
	{
		FILE *archive = fopen("archive.txt", "r");
		fread(&str_size, 1, sizeof(size_t), archive);
		string str1(str_size, '\0');
		fread(&str1[0], sizeof(char), str_size, archive);
		root_ptr->yes = new node(str1);
		
		fread(&str_size, 1, sizeof(size_t), archive);
		string str2(str_size, '\0');
		fread(&str2[0], sizeof(char), str_size, archive);
		fclose(archive);
		root_ptr->no = new node(str2);
	}
}
*/

void load_in(FILE * file, node ** root_ptr)
{
	size_t str_size = 0;
	fread(&str_size, 1, sizeof(size_t), file);
	string str(str_size, '\0');
	fread(&str[0], sizeof(char), str_size, file);
	*root_ptr = new node(str);
	if ((int)str[str.length() - 1] == 63)
	{
		load_in(file, & (*root_ptr)->yes);
		load_in(file, & (*root_ptr)->no);
	}
	else return;
}

void GM::load()
{
	FILE *archive = fopen("archive.txt", "r");
	load_in(archive, & _memory._root);
	fclose(archive);
}

