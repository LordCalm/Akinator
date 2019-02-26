#include "Akinator.h"

void GM::menu()
{
	while (true)
	{
		cout << "АКИНАТОР\nВведите превую букву, чтобы выбрать действие\n [и]грать\n [з]агрузить\n [с]охранить\n [в]ыход" << endl;
		string answer;
		getline(cin, answer);
		if (answer == "в") return;
		else if (answer == "и") play();
		else if (answer == "з")
		{
			load();
			cout << "Данные загружены\n" << endl;
		}
		else if (answer == "с")
		{
			save();
			cout << "Данные сохранены\n" << endl;
		}
		else cout << "Некорректный ввод\n" << endl;
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
		while (true)
		{
			string answer;
			getline(cin, answer);
			if (answer == "выход" || answer == "в" || answer == "В" || answer == "Выход" || answer == "ВЫХОД") return;
			else if (answer == "д" || answer == "да" || answer == "Да" || answer == "ДА" || answer == "Д") play_in(root_ptr->yes);
			else if (answer == "н" || answer == "нет" || answer == "Нет" || answer == "НЕТ" || answer == "Н") play_in(root_ptr->no);
			else cout << "Некорректный ввод" << endl;
		}
	}
	else
	{
		cout << "\nВаш ответ " << root_ptr->_key << "\nЭто правильный ответ?" << endl;
		while (true)
		{
			string answer;
			getline(cin, answer);
			if (answer == "выход" || answer == "в" || answer == "В" || answer == "Выход" || answer == "ВЫХОД") return;
			else if (answer == "д" || answer == "да" || answer == "Да" || answer == "ДА" || answer == "Д")
			{
				cout << "\nСохранить изменения? [д] или [н] " << endl;
				string answer1;
				getline(cin, answer1);
				if (answer == "д") save();
				else return;

				play_in(_memory._root);
			}
			else if (answer == "н" || answer == "нет" || answer == "Нет" || answer == "НЕТ" || answer == "Н")
			{
				_memory.insert(answer, root_ptr);

				cout << "Сохранить изменения? [д] или [н] " << endl;
				string answer1;
				getline(cin, answer1);
				if (answer == "д") save();
				else return;

				play_in(_memory._root);
			}
			else cout << "Некорректный ввод" << endl;
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

