// Vector13.cpp: определяет точку входа для консольного приложения.
// Заменить все положительные числа квадратом минимального числа. Контейнер: вектор (std::vector)

/*
1. Функцию заполнения текстового файла N целыми случайными числами в диапазоне от -M до M. 
Имя файла, N и M поступают на вход функции, файл возвращается функцией как результат (использовать потоки ввода-вывода). 
Реализовать два варианта генерации чисел — в цикле и с использованием алгоритма std::generate.
2. Функцию, получающую файл на вход, и возвращающую последовательный контейнер, заполненный числами из файла.
3. Функцию modify, выполняющую преобразование полученного контейнера. На вход функции должен поступать контейнер,
в качестве результата функция должна возвращать модифицированный контейнер.
4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца обрабатываемой части контейнера.
5. Функцию, реализующую требуемое преобразование с использованием алгоритма std::transform вместо функции modify.
6. Функцию, реализующую требуемое преобразование с использованием алгоритма std::for_each вместо функции modify.
7. Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в контейнере.
8. Функцию вывода результата в файл и на экран (опционально).
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <string>
#include <io.h>
#include <conio.h>

using namespace std;

int InputNumber() 
{
	int num;
	try 
	{
		cin >> num;
		cout << endl;
	}
	catch (int) 
	{
		exception("Ошибка ввода.\n");
		num = 0;
	}
	while (num <= 0)
	{
		cout << "Число должно быть больше нуля. Повторите ввод: ";
		try 
		{
			cin >> num;
			cout << endl;
		}
		catch (int) 
		{
			exception("Ошибка ввода.\n");
			num = 0;
		}
	}
	return num;
};

// Проверка существования файла с именем fname
bool FileExists(const char* fname) 
{
	bool res;
	if (!_access(fname, 0))
		res = true;
	else res = false;
	return res;
}

// Ввод имени файла
string InputFileName(string txt) 
{
	string fname;
	cout << txt << endl;
	cin >> fname;
	return fname;
}

//1. Функция заполнения текстового файла N целыми случайными числами в диапазоне от -M до M. 
//Имя файла, N и M поступают на вход функции, файл возвращается функцией как результат(используем потоки ввода - вывода).
//Реализовать два варианта генерации чисел — в цикле и с использованием алгоритма std::generate.

ofstream FillOut(string FileName, int N, int M)
{
	ofstream fout;
	fout.open(FileName);
	//Проверка успешности открытия файла:
	if (!fout.is_open())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	srand(time(0));
	for (auto i = 0; i < N; i++) 
	{
		fout << rand() % (M + M + 1) - M << " ";
	}
	fout << "\n";

	/*vector<int> v (N);
	generate(v.begin(), v.end(), rand() % (M + M + 1) - M); // Используем C-функцию rand()
	for (auto iv : v) 
	{
		fout << iv << " ";
	}
	fout << "\n";*/

	cout << "Данные в файл успешно загружены" << endl;
	fout.close();
	return fout;
}

//2. Функция, получающая файл на вход, и возвращающая последовательный контейнер, заполненный числами из файла.
vector<int> GetVectorFromFile(ifstream &fin)
{
	vector<int> vec;
	if (!fin) {
		cout << "Файл не найден." << endl;
		return vec;
	}

	int x;
	if (!(fin >> x)) {
		cout << "Неверный формат данных" << endl;
		return vec;
	}
	if (fin.eof()) {
		cout << "Файл пуст." << endl;
	}
	else
	{
		while (!fin.eof()) {
			vec.push_back(x);
			if (!(fin >> x) && !fin.eof())
			{
				cout << "Неверный формат данных" << endl;
				vec.clear();
				return vec;
			}
				
		}
	}
	return vec;
}

// Функция нахождения минимального числа
int FindMin(vector<int> vec)
{
	int min = vec[0];
	for (const int i : vec)
	{
		if (i < min) 
		{
			min = i;
		}
	}
	return min*min; //возвращаем квадрат минимума
}

int FindMin(vector<int>::iterator a, vector<int>::iterator b)
{
	vector<int>::iterator it=a; //объявляю итератор it
	int min = *it;
	for (; it != b; it++)
	{
		if (*it < min) 
		{
			min = *it;
		}
	}
	return min*min; //возвращаем квадрат минимума
}

//3. Функцию modify, выполняющую преобразование полученного контейнера. На вход функции должен поступать контейнер,
//в качестве результата функция должна возвращать модифицированный контейнер.
vector<int> Modify(vector<int> &vec)
{
	int min = FindMin(vec);
	for (int &i:vec) 
	{
		if (i > 0)
			i = min;
	}
	return vec;
}

//4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца обрабатываемой части контейнера.
vector<int> Modify(vector<int>::iterator &a, vector<int>::iterator b)
{
	vector<int> vec;
	int min = FindMin(a,b);
	
	vector<int>::iterator it=a; //объявляю итератор it
	for (; it != b; ++it) //использую итератор для доступа к элементам вектора
	{
		if (*it > 0) 
		{
			*it = min;
		}
		vec.push_back(*it);
	}
	return vec;
}

//5. Функцию, реализующую требуемое преобразование с использованием алгоритма std::transform вместо функции modify.
vector<int> Trnsfrm(vector<int> &vec)
{
	int min = FindMin(vec);
	transform(vec.begin(), vec.end(), vec.begin(), [min](int &i) {if (i > 0) i = min; return i;});
	return vec;
}

//6. Функцию, реализующую требуемое преобразование с использованием алгоритма std::for_each вместо функции modify.
vector<int> ForEach(vector<int> &vec)
{
	vector<int> NewVec;
	int min = FindMin(vec);
	for_each(vec.begin(), vec.end(), [min](int &i) {if (i > 0) i = min; return i;});
	return vec;
}

//7. Функция, вычисляющая сумму чисел в векторе
int SumVector(vector<int> vec)
{
	int sum = 0;
	for (const int n : vec)
		sum += n;
	return sum;
}

//7. Функция, вычисляющяя среднее арифметическое чисел в векторе
//Округляю до сотых
double Average(vector<int> vec)
{
	return round((1. * SumVector(vec) / vec.size()) * 100) / 100;	
}

//8. Функции вывода результата в файл и на экран.
//Сохраняет данные (вектор vec) в текстовый файл с именем fname
int SaveToFile(ofstream &fout, vector<int> vec)
{
	for (const int n : vec)
		fout << n << " ";	
	cout << "Данные в файл успешно загружены" << endl;
	return 0;
}

// вывод на экран вектора vec
void PrintVector(vector<int> vec)
{
	for_each(vec.begin(), vec.end(), [](int i) {cout << i << " "; });
	cout << endl;
}


// Меню
int PrintMenu(int flag)
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "[1] — Посмотреть работу функций 1-8" << endl;
	cout << "[2] — Заполнить текстовый файл N целыми случайными числами в диапазоне от -M до M" << endl;
	cout << "[3] — Получить последовательный контейнер, заполненный числами из файла" << endl;
	if (flag > 0) {
		cout << "[4] — Заменить все положительные числа квадратом минимального числа." << endl;
		cout << "[5] — Вывод результатов на экран" << endl;
		cout << "[6] — Запись результатов в текстовый файл" << endl;
		cout << "[7] — Вычислить сумму и среднее арифметическое чисел, содержащихся в контейнере" << endl;
	}
	cout << "[0] — Выход" << endl;
	cout << "---------------------------------------------------------------" << endl;
	int res;
	while (!(cin >> res) || flag <= 0 && (res > 3) || (flag > 0) && (res > 7));
	return res;
};

void PrintMenuSmall()
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "[1] — modify с контейнером на входе" << endl;
	cout << "[2] — modify с итераторами начала и конца на входе" << endl;
	cout << "[3] — Преобразование с использованием алгоритма std::transform" << endl;
	cout << "[4] — Преобразование с использованием алгоритма std::for_each" << endl;
	cout << "---------------------------------------------------------------" << endl;
};

void DoAll(vector<int> v, vector<int> vctr) 
{
	int NN = 10;
	int MM = 100;
	string FileName = "test.txt";
	ifstream fin;
	ofstream fout = FillOut(FileName, NN, MM);
	fin.open(FileName);
	v = GetVectorFromFile(fin);
	fin.close();
	PrintVector(v);

	vctr = Modify(v);
	cout << "Проверка modify с контейнером на входе: \n";
	PrintVector(vctr);

	vctr = Modify(v.begin(), v.end());
	cout << "Проверка modify с итераторами начала и конца на входе: \n";
	PrintVector(vctr); 

	vctr = Trnsfrm(v);
	cout << "Проверка преобразования с использованием алгоритма std::transform: \n";
	PrintVector(vctr);

	vctr = ForEach(v);
	cout << "Проверка преобразования с использованием алгоритма std::for_each: \n";
	PrintVector(vctr);

	SaveToFile(fout, vctr);

	cout << "Сумма чисел исходного вектора: \n";
	int sum = SumVector(v);
	cout << sum << "\n";

	cout << "Среднее арифметическое чисел исходного вектора: \n";
	double av = Average(v);
	cout << av << "\n";

	cout << "Сумма чисел модифицированного вектора: \n";
	sum = SumVector(vctr);
	cout << sum << "\n";

	cout << "Среднее арифметическое чисел модифицированного вектора: \n";
	av = Average(vctr);
	cout << av << "\n";
	getch();
}

//ввод ответа да/нет
bool Answer(string question)
{
	int answer;
	cout << question << endl;
	while (!(cin >> answer) || answer != 0 && answer != 1);
	cout << endl;
	return answer == 1;
}

void ChooseModification(vector<int> v, vector<int> &vctr)
{
	PrintMenuSmall();
	cout << "Введите команду: ";
	int p;
	cin >> p;
	cout << endl;
	cin.clear();

	switch (p)
	{
	case 1:
	{
		vctr = Modify(v);
		PrintVector(vctr);
		break;
	}
	case 2: 
	{
		vector<int>::iterator it; //объявляю итератор it
		vctr = Modify(v.begin(), v.end());
		PrintVector(vctr);
		break;
	}
	case 3: 
	{
		vctr = Trnsfrm(v);
		PrintVector(vctr);
		break;
	}
	case 4: 
	{
		vctr = ForEach(v);
		PrintVector(vctr);
		break;
	}
	default:
		cout << "Неправильно введена команда" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int NN,MM;
	vector<int> v; // Исходный вектор
	vector<int> vctr; // Модифицированный вектор
	string FileName ="";
	ofstream ofs;
	ifstream ifs;
	bool flag = true;
	do
	{
		switch (PrintMenu(v.size()))
		{
			case 1:
			{
				DoAll(v, vctr);
				break;
			}
			case 2: //Заполнить текстовый файл N целыми случайными числами в диапазоне от -M до M"
			{
				cout << "Введите количество чисел: \n";
				NN = InputNumber();
				cout << "Введите диапазон(-число,+число) одним числом \n";
				MM = InputNumber();
				FileName = InputFileName("Введите имя файла");
				ofs = FillOut(FileName, NN, MM);
				break;
			}
			case 3: //Получить последовательный контейнер, заполненный числами из файла
			{
				if (FileName == "") FileName = InputFileName("Введите имя файла");
				else if (!Answer("Использовать текущий файл? 1-да, 0-нет")) {
					FileName = InputFileName("Введите имя файла");
				}
				ifs.open(FileName);
				v = GetVectorFromFile(ifs);
				ifs.close();
				PrintVector(v);
				break;
			}
			case 4: //Заменить все положительные числа квадратом минимального числа.
			{
				ChooseModification(v, vctr);
				break;
			}
			case 5://Вывод результатов на экран
			{
				if (vctr.size() == 0) {
					cout << "Результирующие данные ещё не были получены" << endl;
				}
				else {
					cout << "Модифицированный вектор: \n";
					PrintVector(vctr);
				}
				break;
			case 6://Запись результатов в текстовый файл
			{
				if (vctr.size() == 0)
					cout << "Результирующие данные ещё не были получены" << endl;
				else
				{
					FileName = InputFileName("Введите имя результирующего файла(0 - output.txt по умолчанию): ");
					ofs.open(FileName);
					if (FileName == "0")
						FileName = "output.txt";
					SaveToFile(ofs, vctr);
					ofs.close();
				}
				break;
			}
			case 7: //Вычислить сумму и среднее арифметическое чисел, содержащихся в контейнере
			{
				cout << "Сумма чисел исходного вектора : \n";
				cout << SumVector(v) << "\n";

				cout << "Среднее арифметическое чисел исходного вектора: \n";
				cout << Average(v) << "\n";

				if (!vctr.size() == 0)
				{
					cout << "Сумма чисел модифицированного вектора: \n";
					cout << SumVector(vctr) << "\n";

					cout << "Среднее арифметическое чисел модифицированного вектора: \n"; 
					cout << Average(vctr) << "\n";
				}
				break;
			}
			case 0://Выход
			{
				cout << "Работа программы завершена \n";
				flag = false;
				break;
			}
			default:
				cout << "Неправильно введена команда" << endl;
			}
			
		}
		
	} while (flag);
    return 0;
}

