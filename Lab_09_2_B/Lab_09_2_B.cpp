#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Specialty { КН, ІТ, ПЗ, ВП, СА };

string specialtyStr[] = { "КН", "ІТ", "ПЗ", "ВП", "СА" };

struct Student
{
	string prizv;
	int kurs;
	Specialty specialty;
	int physics;
	int mathematics;
	union
	{
		int programming;
		int NumericalMethods;
		int pedagogy;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const int kurs, const Specialty specialty);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть N: "; cin >> N;

	Student* p = new Student[N];

	int ispecialty;
	Specialty specialty;
	int kurs;
	string prizv;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід фізично впорядкованого масиву" << endl;
		cout << " [4] - вивід індексно впорядкованого масиву" << endl;
		cout << " [5] - вивід результату бінарного пошуку" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			break;
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			do
			{
				cout << "Спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): ";
				cin >> ispecialty;
				specialty = (Specialty)ispecialty;
			} while (!(specialty >= 0 && specialty <= 4));
			cin.sync();
			cout << " Прізвище: "; cin >> prizv;
			do
			{
				cout << " Курс: "; cin >> kurs;
			} while (!(kurs > 0));
			if ((found = BinSearch(p, N, prizv, kurs, specialty)) != -1)
				cout << "Знайдено працівника в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	system("pause");
	return 0;
}

void Create(Student* p, const int N)
{
	int specialty;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.sync();
		cout << " Прізвище: "; cin >> p[i].prizv;
		do
		{
			cout << " Курс: "; cin >> p[i].kurs;
		} while (!(p[i].kurs > 0));
		do
		{
			cout << " Спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): ";
			cin >> specialty;
			p[i].specialty = (Specialty)specialty;
		} while (!(specialty >= 0 && specialty <= 4));
		do
		{
			cout << " Оцінка з фізики: "; cin >> p[i].physics;
		} while (!(p[i].physics >= 0 && p[i].physics <= 5));
		do
		{
			cout << " Оцінка з математики: "; cin >> p[i].mathematics;
		} while (!(p[i].mathematics >= 0 && p[i].mathematics <= 5));
		do
		{
			switch (p[i].specialty)
			{
			case КН:
				cout << " Оцінка з програмування : "; cin >> p[i].programming;
				break;
			case ІТ:
				cout << " Оцінка з чисельних методів: "; cin >> p[i].NumericalMethods;
				break;
			case ПЗ:
				cout << " Оцінка з педагогіки: "; cin >> p[i].pedagogy;
				break;
			case ВП:
				cout << " Оцінка з педагогіки: "; cin >> p[i].pedagogy;
				break;
			case СА:
				cout << " Оцінка з педагогіки: "; cin >> p[i].pedagogy;
				break;
			}
			cout << endl;
		}while (!((p[i].programming >= 0 && p[i].programming <= 5) || (p[i].NumericalMethods >= 0 && p[i].NumericalMethods <= 5) || (p[i].pedagogy >= 0 && p[i].pedagogy <= 5)));
	}
}

void Print(Student* p, const int N)
{
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			 << "| " << setw(4) << left << p[i].kurs << " "
			 << "| " << setw(14) << left << specialtyStr[p[i].specialty]
			 << "| " << setw(6) << left << p[i].physics << " "
			 << "| " << setw(10) << left << p[i].mathematics << " ";
		switch (p[i].specialty)
		{
		case КН:
			cout << "| " << setw(13) << left
				<< p[i].programming << " |" << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case ІТ:
			cout << "| " << setw(16) << right
				<< "| " << setw(16) << left << p[i].NumericalMethods << "|" << setw(13) << right << "|" << endl;
			break;
		case ПЗ:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				<< "| " << setw(12) << left << p[i].pedagogy << "|" << endl;
			break;
		case ВП:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				<< "| " << setw(11) << left << p[i].pedagogy << "|" << endl;
			break;
		case СА:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				<< "| " << setw(11) << left << p[i].pedagogy << "|" << endl;
			break;
		}
		cout << "------------------------------------------------------------------------------------------------------------"
			<< endl;
	}
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].specialty > p[i1 + 1].specialty)
				||
				(p[i1].specialty == p[i1 + 1].specialty &&
				 p[i1].prizv < p[i1 + 1].prizv)
				||
				(p[i1].specialty == p[i1 + 1].specialty &&
				 p[i1].prizv == p[i1 + 1].prizv &&
			     p[i1].kurs > p[i1 + 1].kurs))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];

	for (int i = 0; i < N; i++)
		I[i] = i;

	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].specialty > p[value].specialty)
				||
				(p[I[j]].specialty == p[value].specialty &&
				 p[I[j]].prizv < p[value].prizv)
				||
				((p[I[j]].specialty == p[value].specialty &&
				 p[I[j]].prizv == p[value].prizv &&
				 p[I[j]].kurs > p[value].kurs)));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[I[i]].prizv
			<< "| " << setw(4) << left << p[I[i]].kurs << " "
			<< "| " << setw(14) << left << specialtyStr[p[I[i]].specialty]
			<< "| " << setw(6) << left << p[I[i]].physics << " "
			<< "| " << setw(10) << left << p[I[i]].mathematics << " ";
			switch (p[i].specialty)
			{
			case КН:
				cout << "| " << setw(13) << left
					<< p[i].programming << " |" << setw(18) << right << "|" << setw(13) << right << "|" << endl;
				break;
			case ІТ:
				cout << "| " << setw(16) << right
					<< "| " << setw(16) << left << p[i].NumericalMethods << "|" << setw(13) << right << "|" << endl;
				break;
			case ПЗ:
				cout << "| " << setw(15) << right << "|" << setw(19) << right
					<< "| " << setw(12) << left << p[i].pedagogy << "|" << endl;
				break;
			case ВП:
				cout << "| " << setw(15) << right << "|" << setw(19) << right
					<< "| " << setw(11) << left << p[i].pedagogy << "|" << endl;
				break;
			case СА:
				cout << "| " << setw(15) << right << "|" << setw(19) << right
					<< "| " << setw(11) << left << p[i].pedagogy << "|" << endl;
				break;
			}
		cout << "------------------------------------------------------------------------------------------------------------"
			<< endl;
	}
}

int BinSearch(Student* p, const int N, const string prizv, int kurs, const Specialty specialty)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].specialty == specialty && p[m].kurs == kurs)
			return m;

		if ((p[m].specialty < specialty)
			||
			(p[m].specialty == specialty &&
			 p[m].prizv < prizv)
			||
			(p[m].specialty == specialty &&
			 p[m].prizv == prizv &&
			 p[m].kurs < kurs))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
