#include <iostream>
#include <Windows.h>
#include <ctime>
#include <algorithm>
using namespace std;
typedef  bool (*PR)(int);

template<class T>
T** createArr2D(int  rows, int cols) {
	T** mas = new T * [rows];
	for (size_t r = 0; r < rows; r++)
		mas[r] = new T[cols]{ 0 };
	return mas;
}
template<class T>
void deleteArr2D(T** mas, int rows) {
	for (size_t r = 0; r < rows; r++)
		delete[]  mas[r];
	delete[]  mas;
}
template<class T>
void Print(T** mas2d, int ryadkiv, int stovpciv) {
	for (size_t r = 0; r < ryadkiv; r++)
	{
		for (size_t c = 0; c < stovpciv; c++)
			//cout << mas2d[r][c] << "\t";
			cout << *(*(mas2d + r) + c) << "\t";
		cout << endl;
	}
	cout << "-----------------------------" << endl;
}
template<class T>
void Set(T** mas2d, int ryadkiv, int stovpciv) {
	for (size_t r = 0; r < ryadkiv; r++)
		for (size_t c = 0; c < stovpciv; c++)
			mas2d[r][c] = (-100 + rand() % 201) / 13.9;
}

void AddColumn(int**& mas2d, int r, int& c, int pos) {

	int** nmat = createArr2D<int>(r, c + 1);
	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < pos; j++)
		{
			nmat[i][j] = mas2d[i][j];
		}
	}
	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = pos; j < c; j++)
		{
			nmat[i][j + 1] = mas2d[i][j];
		}
	}
	deleteArr2D(mas2d, r);
	mas2d = nmat;
	c++;
}
void AddColumn2(int**& mas2d, int r, int& c, int pos) {
	int** nmat = createArr2D<int>(r, c + 1);
	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < c; j++)
		{
			if (j < pos)
				nmat[i][j] = mas2d[i][j];
			else
				nmat[i][j + 1] = mas2d[i][j];
		}
	}
	deleteArr2D(mas2d, r);
	mas2d = nmat;
	c++;
}
template<class T>
void Insert(T*& mas, int& n, T el, int pos = 0) {
	T* nmas = new T[n + 1];
	for (size_t j = 0; j < n; j++)
		if (j < pos)
			nmas[j] = mas[j];
		else
			nmas[j + 1] = mas[j];
	nmas[pos] = el;
	delete[] mas;
	mas = nmas;
	n++;
}
template<class T>
void AddColumn3(T**& mas2d, int r, int& c, int pos) {

	for (size_t i = 0; i < r; i++)
	{
		Insert(mas2d[i], c, (T)(555 / 2.9), pos);
		c--;
	}
	c++;
}
template<class T>
size_t CountPos(T* mas, size_t n) {
	size_t k = 0;
	for (size_t j = 0; j < n; j++)
		if (mas[j] > 0)
			k++;
	return k;
}
template<class T>
size_t CountNeg(T* mas, size_t n) {
	size_t k = 0;
	for (size_t j = 0; j < n; j++)
		if (mas[j] < 0)
			k++;
	return k;
}
template<class T>
size_t CountEven(T* mas, size_t n) {
	size_t k = 0;
	for (size_t j = 0; j < n; j++)
		if (mas[j] % 2 == 0)
			k++;
	return k;
}

template<class T>
size_t Count(T* mas, size_t n, PR Pred) {
	//size_t Count(T* mas, size_t n, bool (*Pred)(T)) {
	size_t k = 0;
	for (size_t j = 0; j < n; j++)
		if (Pred(mas[j]))
			k++;
	return k;
}
int Test()
{
	int rows, cols;
	cout << "rows="; cin >> rows;
	cout << "cols="; cin >> cols;
	int** arr = createArr2D<int>(rows, cols);
	Set(arr, rows, cols);
	Print(arr, rows, cols);
	//exit(2);

	AddColumn3(arr, rows, cols, 4);
	Print(arr, rows, cols);
	deleteArr2D(arr, rows);


	double** arrd = createArr2D<double>(rows, cols);
	Set(arrd, rows, cols);
	Print(arrd, rows, cols);
	AddColumn3(arrd, rows, cols, 0);
	Print(arrd, rows, cols);

	deleteArr2D(arrd, rows);
	return 0;
}
int Start()
{
	cout << "Start\n";
	return 0;
}
bool AboveZero(int el) {
	return el > 0 ? true : false;
}
bool LessZero(int el) {
	return el < 0 ? true : false;
}
int main()
{
	int a = 10;
	cout << a << endl;
	cout << &a << endl;
	cout << Test << endl;

	//auto f=Test;
	/*int (*f)() = Test;
	f();
	f = Start;
	f();*/

	int mas[]{ -2,3,0,6,9,2,3,5,-25,-5 };
	//bool (*pr)(int ) = [](int a)->bool {return a > 0 ? true : false; };
	PR pr = [](int a)->bool {return a > 0; };
	cout << "CountPos =" << CountPos(mas, 10) << endl;
	cout << "Count >0 =" << Count(mas, 10, AboveZero) << endl;
	cout << "Count >0 =" << Count(mas, 10, pr) << endl;

	cout << "Count <0 =" << Count(mas, 10, LessZero) << endl;
	pr = [](int a)->bool {return a < 0;  };
	cout << "Count <0 =" << Count(mas, 10, pr) << endl;

	cout << "Count =0 =" << Count(mas, 10, [](int a) {return a == 0; }) << endl;

}