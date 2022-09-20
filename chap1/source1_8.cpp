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
	Matrix& addMatrix(Matrix&);
	// int MultiplyMatrix(Matrix&, Matrix&);

	Matrix(int rows_input, int cols_input)
	{
		rows = rows_input;
		cols = cols_input;

		TermElement = new Term[rows * cols];
	}

	Matrix operator=(const Matrix& m)
	{
		Matrix res(m);
		return res;
	}
};

int Matrix::get_data()
{
	for (int i = 0; i < rows * cols; i++)
	{
		TermElement[i].coef = rand() % (rows * cols);
		TermElement[i].exp = rand() % (rows * cols);
	}
	return 1;
}

int Matrix::show_data()
{

	return 1;
}

int Matrix::sort_data()
{
	return 1;
}
Matrix& Matrix::addMatrix(Matrix& m)
{
	Matrix tmp(rows, cols);

	return tmp;
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

	cout << "MatrixB :" << endl;
	matrixB.get_data();
	matrixB.show_data();
	
	cout << "MatrixC = A + B :" << endl;
	matrixC = matrixA.addMatrix(matrixB);
	matrixC.show_data();

	system("pause");
	return 0;
}