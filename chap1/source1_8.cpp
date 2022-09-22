#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define TERMS 5
#define MaxExp 10
using namespace std;

class Matrix;

class Term
{
	friend Matrix;
private:
	float coef;
	int exp;
};

class Matrix
{
private:
	int rows, cols;
	static Term* TermElement;
	static int free;
	int start, finish;
	int terms;

public:
	int get_data();
	int show_data();
	int sort_data();
	Matrix& addMatrix(const Matrix&);
	// int MultiplyMatrix(Matrix&, Matrix&);

	Matrix(int rows_input, int cols_input)
	{
		rows = rows_input;
		cols = cols_input;
		start = free;
		finish = start + rows_input * cols_input;
		terms = rows_input * cols_input;
		free = free + rows_input * cols_input;
	}

	Matrix& operator=(const Matrix& m)
	{
		// remember this mechanism of temporary object. cf) addMatrix
		rows = m.rows;
		cols = m.cols;
		start = m.start;
		finish = m.finish;
		terms = m.terms;
		free = m.free;

		return *this;
	}
};

int Matrix::get_data()
{
	if (finish == terms)
	{
		for (int i = 0; i < terms; i++)
			TermElement[i].exp = rand() % (rows * cols);
	}
	for (int i = start; i < finish; i++)
			TermElement[i].coef = rand() % (rows * cols);
	return 1;
}

int Matrix::show_data()
{
	int j = 0;
	for (int i = start; i < finish; i++)
		cout << TermElement[i].coef << "x**" << TermElement[j++].exp << " ";
	cout << endl;
	return 1;
}

int Matrix::sort_data()
{
	return 1;
}
Matrix &Matrix::addMatrix(const Matrix& m)
{
	for (int i = start; i < finish; i++)
		TermElement[start + i].coef = TermElement[i].coef + m.TermElement[m.start + i].coef;

	return *this;
}

int Matrix::free = 0;
Term* Matrix::TermElement = new Term[100];

int main(void)
{
	Matrix matrixA(3, 4);
	Matrix matrixB(3, 4);
	Matrix matrixC(3, 4);
	// implement F[5, 6] = D[3, 4] + E[5, 6]

	srand(time(NULL));
	cout << "MatrixA :" << endl;
	matrixA.get_data();
	matrixA.show_data();
	cout << endl;
	
	cout << "MatrixB :" << endl;
	matrixB.get_data();
	matrixB.show_data();
	cout << endl;

	cout << "MatrixC = A + B :" << endl;
	matrixC = matrixA.addMatrix(matrixB);
	//matrixC = matrixA;
	matrixC.show_data();
	cout << endl;

	system("pause");
	return 0;
}