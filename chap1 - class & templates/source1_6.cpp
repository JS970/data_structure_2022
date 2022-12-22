// source code 1.6 class representing matrix
// use class which use get_data() function to calculate different sizes of matrix
// rewrite C program code to calculate matrix using class
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
using namespace std;
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5

class Matrix
{
private:
	int rows, cols;
	int* data;
public:
	Matrix(int rows_input, int cols_input)
	{
		rows = rows_input;
		cols = cols_input;

		data = new int(rows * cols); // need to delete dynamic allocation
	}
	int get_data();
	int show_data();
	int sort_data();
	Matrix &addMatrix(Matrix&);
	int MultiplyMatrix(Matrix&, Matrix&);
};

int Matrix::get_data()
{
	for (int i = 0; i < rows * cols; i++)
		data[i] = rand() % (rows * cols);

	return 1;
}

int Matrix::show_data()
{
	int idx;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			idx = i * cols + j;
			cout << data[idx] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 1;
}

int Matrix::sort_data()
{
	return 1;
}

Matrix& Matrix::addMatrix(Matrix& m)
{
	Matrix tmp(rows, cols);
	for (int i = 0; i < rows * cols; i++)
	{
		tmp.data[i] = data[i] + m.data[i];
	}
	return tmp;
}

int Matrix::MultiplyMatrix(Matrix& m1, Matrix& m2)
{
	int tmpM = 0;
	int idx = 0;
	int idx_m1 = 0;
	int idx_m2 = 0;

	for (int i = 0; i < m1.rows; i++)
	{
		for (int j = 0; j < m2.cols; j++)
		{
			idx = i * (m2.cols) + j;
			for (int k = 0; k < m1.cols; k++)
			{
				idx_m1 = i * (m1.rows + 1) + k;
				idx_m2 = k * m2.cols + j;


				tmpM += m1.data[idx_m1] * m2.data[idx_m2];
			}
			data[i*m2.cols+j] = tmpM;
			tmpM = 0;
		}
	}

	return 1;
}

int main(void)
{
	Matrix matrixA(AROWS, ACOLS);
	Matrix matrixA1(AROWS, ACOLS);
	Matrix matrixA2(AROWS, ACOLS);
	Matrix matrixB(BROWS, BCOLS);
	Matrix matrixC(CROWS, CCOLS);

	srand(time(NULL));


	matrixA.get_data();
	matrixB.get_data();
	cout << "<MatrixA>" << endl;
	matrixA.show_data();
	cout << endl;
	matrixA1.get_data();
	cout << "<MatrixA1>" << endl;
	matrixA1.show_data();
	cout << endl;
	//matrixA2 = matrixA1.addMatrix(matrixA);
	//cout << "<MatrixA2 = MatrixA + MatrixA1>" << endl;
	//matrixA2.show_data();
	//cout << endl;
	cout << "<MatrixA>" << endl;
	matrixA.show_data();
	cout << endl;
	cout << "<MatrixB>" << endl;
	matrixB.show_data();
    cout << "<MatrixB>" << endl;
	matrixB.show_data();
	cout << endl;
	//matrixC.MultiplyMatrix(matrixA, matrixB);
	//cout << "<MatrixC = MatrixA * MatrixB>" << endl;
	//matrixC.show_data();

	system("pause");
}
