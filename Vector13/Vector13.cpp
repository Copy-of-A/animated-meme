// Vector13.cpp: ���������� ����� ����� ��� ����������� ����������.
// �������� ��� ������������� ����� ��������� ������������ �����. ���������: ������ (std::vector)

/*
1. ������� ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M. 
��� �����, N � M ��������� �� ���� �������, ���� ������������ �������� ��� ��������� (������������ ������ �����-������). 
����������� ��� �������� ��������� ����� � � ����� � � �������������� ��������� std::generate.
2. �������, ���������� ���� �� ����, � ������������ ���������������� ���������, ����������� ������� �� �����.
3. ������� modify, ����������� �������������� ����������� ����������. �� ���� ������� ������ ��������� ���������,
� �������� ���������� ������� ������ ���������� ���������������� ���������.
4. ������������� ������� modify, ����������� �� ���� ��������� ������ � ����� �������������� ����� ����������.
5. �������, ����������� ��������� �������������� � �������������� ��������� std::transform ������ ������� modify.
6. �������, ����������� ��������� �������������� � �������������� ��������� std::for_each ������ ������� modify.
7. �������, ����������� ����� � ������� �������������� �����, ������������ � ����������.
8. ������� ������ ���������� � ���� � �� ����� (�����������).
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
		exception("������ �����.\n");
		num = 0;
	}
	while (num <= 0)
	{
		cout << "����� ������ ���� ������ ����. ��������� ����: ";
		try 
		{
			cin >> num;
			cout << endl;
		}
		catch (int) 
		{
			exception("������ �����.\n");
			num = 0;
		}
	}
	return num;
};

// �������� ������������� ����� � ������ fname
bool FileExists(const char* fname) 
{
	bool res;
	if (!_access(fname, 0))
		res = true;
	else res = false;
	return res;
}

// ���� ����� �����
string InputFileName(string txt) 
{
	string fname;
	cout << txt << endl;
	cin >> fname;
	return fname;
}

//1. ������� ���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M. 
//��� �����, N � M ��������� �� ���� �������, ���� ������������ �������� ��� ���������(���������� ������ ����� - ������).
//����������� ��� �������� ��������� ����� � � ����� � � �������������� ��������� std::generate.

ofstream FillOut(string FileName, int N, int M)
{
	ofstream fout;
	fout.open(FileName);
	//�������� ���������� �������� �����:
	if (!fout.is_open())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	srand(time(0));
	for (auto i = 0; i < N; i++) 
	{
		fout << rand() % (M + M + 1) - M << " ";
	}
	fout << "\n";

	/*vector<int> v (N);
	generate(v.begin(), v.end(), rand() % (M + M + 1) - M); // ���������� C-������� rand()
	for (auto iv : v) 
	{
		fout << iv << " ";
	}
	fout << "\n";*/

	cout << "������ � ���� ������� ���������" << endl;
	fout.close();
	return fout;
}

//2. �������, ���������� ���� �� ����, � ������������ ���������������� ���������, ����������� ������� �� �����.
vector<int> GetVectorFromFile(ifstream &fin)
{
	vector<int> vec;
	if (!fin) {
		cout << "���� �� ������." << endl;
		return vec;
	}

	int x;
	if (!(fin >> x)) {
		cout << "�������� ������ ������" << endl;
		return vec;
	}
	if (fin.eof()) {
		cout << "���� ����." << endl;
	}
	else
	{
		while (!fin.eof()) {
			vec.push_back(x);
			if (!(fin >> x) && !fin.eof())
			{
				cout << "�������� ������ ������" << endl;
				vec.clear();
				return vec;
			}
				
		}
	}
	return vec;
}

// ������� ���������� ������������ �����
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
	return min*min; //���������� ������� ��������
}

int FindMin(vector<int>::iterator a, vector<int>::iterator b)
{
	vector<int>::iterator it=a; //�������� �������� it
	int min = *it;
	for (; it != b; it++)
	{
		if (*it < min) 
		{
			min = *it;
		}
	}
	return min*min; //���������� ������� ��������
}

//3. ������� modify, ����������� �������������� ����������� ����������. �� ���� ������� ������ ��������� ���������,
//� �������� ���������� ������� ������ ���������� ���������������� ���������.
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

//4. ������������� ������� modify, ����������� �� ���� ��������� ������ � ����� �������������� ����� ����������.
vector<int> Modify(vector<int>::iterator &a, vector<int>::iterator b)
{
	vector<int> vec;
	int min = FindMin(a,b);
	
	vector<int>::iterator it=a; //�������� �������� it
	for (; it != b; ++it) //��������� �������� ��� ������� � ��������� �������
	{
		if (*it > 0) 
		{
			*it = min;
		}
		vec.push_back(*it);
	}
	return vec;
}

//5. �������, ����������� ��������� �������������� � �������������� ��������� std::transform ������ ������� modify.
vector<int> Trnsfrm(vector<int> &vec)
{
	int min = FindMin(vec);
	transform(vec.begin(), vec.end(), vec.begin(), [min](int &i) {if (i > 0) i = min; return i;});
	return vec;
}

//6. �������, ����������� ��������� �������������� � �������������� ��������� std::for_each ������ ������� modify.
vector<int> ForEach(vector<int> &vec)
{
	vector<int> NewVec;
	int min = FindMin(vec);
	for_each(vec.begin(), vec.end(), [min](int &i) {if (i > 0) i = min; return i;});
	return vec;
}

//7. �������, ����������� ����� ����� � �������
int SumVector(vector<int> vec)
{
	int sum = 0;
	for (const int n : vec)
		sum += n;
	return sum;
}

//7. �������, ����������� ������� �������������� ����� � �������
//�������� �� �����
double Average(vector<int> vec)
{
	return round((1. * SumVector(vec) / vec.size()) * 100) / 100;	
}

//8. ������� ������ ���������� � ���� � �� �����.
//��������� ������ (������ vec) � ��������� ���� � ������ fname
int SaveToFile(ofstream &fout, vector<int> vec)
{
	for (const int n : vec)
		fout << n << " ";	
	cout << "������ � ���� ������� ���������" << endl;
	return 0;
}

// ����� �� ����� ������� vec
void PrintVector(vector<int> vec)
{
	for_each(vec.begin(), vec.end(), [](int i) {cout << i << " "; });
	cout << endl;
}


// ����
int PrintMenu(int flag)
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "[1] � ���������� ������ ������� 1-8" << endl;
	cout << "[2] � ��������� ��������� ���� N ������ ���������� ������� � ��������� �� -M �� M" << endl;
	cout << "[3] � �������� ���������������� ���������, ����������� ������� �� �����" << endl;
	if (flag > 0) {
		cout << "[4] � �������� ��� ������������� ����� ��������� ������������ �����." << endl;
		cout << "[5] � ����� ����������� �� �����" << endl;
		cout << "[6] � ������ ����������� � ��������� ����" << endl;
		cout << "[7] � ��������� ����� � ������� �������������� �����, ������������ � ����������" << endl;
	}
	cout << "[0] � �����" << endl;
	cout << "---------------------------------------------------------------" << endl;
	int res;
	while (!(cin >> res) || flag <= 0 && (res > 3) || (flag > 0) && (res > 7));
	return res;
};

void PrintMenuSmall()
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "[1] � modify � ����������� �� �����" << endl;
	cout << "[2] � modify � ����������� ������ � ����� �� �����" << endl;
	cout << "[3] � �������������� � �������������� ��������� std::transform" << endl;
	cout << "[4] � �������������� � �������������� ��������� std::for_each" << endl;
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
	cout << "�������� modify � ����������� �� �����: \n";
	PrintVector(vctr);

	vctr = Modify(v.begin(), v.end());
	cout << "�������� modify � ����������� ������ � ����� �� �����: \n";
	PrintVector(vctr); 

	vctr = Trnsfrm(v);
	cout << "�������� �������������� � �������������� ��������� std::transform: \n";
	PrintVector(vctr);

	vctr = ForEach(v);
	cout << "�������� �������������� � �������������� ��������� std::for_each: \n";
	PrintVector(vctr);

	SaveToFile(fout, vctr);

	cout << "����� ����� ��������� �������: \n";
	int sum = SumVector(v);
	cout << sum << "\n";

	cout << "������� �������������� ����� ��������� �������: \n";
	double av = Average(v);
	cout << av << "\n";

	cout << "����� ����� ����������������� �������: \n";
	sum = SumVector(vctr);
	cout << sum << "\n";

	cout << "������� �������������� ����� ����������������� �������: \n";
	av = Average(vctr);
	cout << av << "\n";
	getch();
}

//���� ������ ��/���
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
	cout << "������� �������: ";
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
		vector<int>::iterator it; //�������� �������� it
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
		cout << "����������� ������� �������" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int NN,MM;
	vector<int> v; // �������� ������
	vector<int> vctr; // ���������������� ������
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
			case 2: //��������� ��������� ���� N ������ ���������� ������� � ��������� �� -M �� M"
			{
				cout << "������� ���������� �����: \n";
				NN = InputNumber();
				cout << "������� ��������(-�����,+�����) ����� ������ \n";
				MM = InputNumber();
				FileName = InputFileName("������� ��� �����");
				ofs = FillOut(FileName, NN, MM);
				break;
			}
			case 3: //�������� ���������������� ���������, ����������� ������� �� �����
			{
				if (FileName == "") FileName = InputFileName("������� ��� �����");
				else if (!Answer("������������ ������� ����? 1-��, 0-���")) {
					FileName = InputFileName("������� ��� �����");
				}
				ifs.open(FileName);
				v = GetVectorFromFile(ifs);
				ifs.close();
				PrintVector(v);
				break;
			}
			case 4: //�������� ��� ������������� ����� ��������� ������������ �����.
			{
				ChooseModification(v, vctr);
				break;
			}
			case 5://����� ����������� �� �����
			{
				if (vctr.size() == 0) {
					cout << "�������������� ������ ��� �� ���� ��������" << endl;
				}
				else {
					cout << "���������������� ������: \n";
					PrintVector(vctr);
				}
				break;
			case 6://������ ����������� � ��������� ����
			{
				if (vctr.size() == 0)
					cout << "�������������� ������ ��� �� ���� ��������" << endl;
				else
				{
					FileName = InputFileName("������� ��� ��������������� �����(0 - output.txt �� ���������): ");
					ofs.open(FileName);
					if (FileName == "0")
						FileName = "output.txt";
					SaveToFile(ofs, vctr);
					ofs.close();
				}
				break;
			}
			case 7: //��������� ����� � ������� �������������� �����, ������������ � ����������
			{
				cout << "����� ����� ��������� ������� : \n";
				cout << SumVector(v) << "\n";

				cout << "������� �������������� ����� ��������� �������: \n";
				cout << Average(v) << "\n";

				if (!vctr.size() == 0)
				{
					cout << "����� ����� ����������������� �������: \n";
					cout << SumVector(vctr) << "\n";

					cout << "������� �������������� ����� ����������������� �������: \n"; 
					cout << Average(vctr) << "\n";
				}
				break;
			}
			case 0://�����
			{
				cout << "������ ��������� ��������� \n";
				flag = false;
				break;
			}
			default:
				cout << "����������� ������� �������" << endl;
			}
			
		}
		
	} while (flag);
    return 0;
}

