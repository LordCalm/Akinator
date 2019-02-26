#include "Akinator.h"

void GM::menu()
{
	while (true)
	{
		cout << "��������\n������� ������ �����, ����� ������� ��������\n [�]�����\n [�]��������\n [�]��������\n [�]����" << endl;
		string answer;
		getline(cin, answer);
		if (answer == "�") return;
		else if (answer == "�") play();
		else if (answer == "�")
		{
			load();
			cout << "������ ���������\n" << endl;
		}
		else if (answer == "�")
		{
			save();
			cout << "������ ���������\n" << endl;
		}
		else cout << "������������ ����\n" << endl;
	}
}

void GM::play()
{
	cout << "���� �� ������ ���������, ������� \"�����\" � ����� ������" << endl;
	play_in(_memory._root);
}

void GM::play_in(node *root_ptr)
{
	if (root_ptr->yes != NULL)
	{
		cout << root_ptr->_key << endl;
		while (true)
		{
			string answer;
			getline(cin, answer);
			if (answer == "�����" || answer == "�" || answer == "�" || answer == "�����" || answer == "�����") return;
			else if (answer == "�" || answer == "��" || answer == "��" || answer == "��" || answer == "�") play_in(root_ptr->yes);
			else if (answer == "�" || answer == "���" || answer == "���" || answer == "���" || answer == "�") play_in(root_ptr->no);
			else cout << "������������ ����" << endl;
		}
	}
	else
	{
		cout << "\n��� ����� " << root_ptr->_key << "\n��� ���������� �����?" << endl;
		while (true)
		{
			string answer;
			getline(cin, answer);
			if (answer == "�����" || answer == "�" || answer == "�" || answer == "�����" || answer == "�����") return;
			else if (answer == "�" || answer == "��" || answer == "��" || answer == "��" || answer == "�")
			{
				cout << "\n��������� ���������? [�] ��� [�] " << endl;
				string answer1;
				getline(cin, answer1);
				if (answer == "�") save();
				else return;

				play_in(_memory._root);
			}
			else if (answer == "�" || answer == "���" || answer == "���" || answer == "���" || answer == "�")
			{
				_memory.insert(answer, root_ptr);

				cout << "��������� ���������? [�] ��� [�] " << endl;
				string answer1;
				getline(cin, answer1);
				if (answer == "�") save();
				else return;

				play_in(_memory._root);
			}
			else cout << "������������ ����" << endl;
		}
	}
}

void GM::save()
{
	FILE *archive = fopen("archive.txt", "w");
	fclose(archive);
	save_in(_memory._root);
}

GM::GM(tree *memory) :
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

void load_in(FILE * file, node ** root_ptr)
{
	size_t str_size = 0;
	fread(&str_size, 1, sizeof(size_t), file);
	string str(str_size, '\0');
	fread(&str[0], sizeof(char), str_size, file);
	*root_ptr = new node(str);
	if ((int)str[str.length() - 1] == 63)
	{
		load_in(file, &(*root_ptr)->yes);
		load_in(file, &(*root_ptr)->no);
	}
	else return;
}

void GM::load()
{
	FILE *archive = fopen("archive.txt", "r");
	load_in(archive, &_memory._root);
	fclose(archive);
}

