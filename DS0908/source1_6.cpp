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

		data = new int[rows];
		for (int i = 0; i < rows*sizeof(data); i = i + sizeof(data))
			for (int j = 0; j < cols; j++)
				(&data[i])[j] = rand() % (rows * cols);
	}
	int * get_data(); // 이것 이외의 방법이 떠오르지 않는다...
	int show_data();
	int sort_data();
	int addMatrix(Matrix&);
	int MultiplyMatrix(Matrix&, Matrix&);
};

int* Matrix::get_data()
{
	return data;
}

int Matrix::show_data()
{
	for (int i = 0; i < rows * sizeof(data); i = i + sizeof(data))
	{
		for (int j = 0; j < cols; j++)
			printf("%d ", (&data[i])[j]);
		printf("\n");
	}

	return 1;
}

int Matrix::sort_data()
{
	return rows*10 + cols;
}

int Matrix::addMatrix(Matrix& m)
{
	if (this->sort_data() == m.sort_data())
	{
		int tmp = 0;
		for (int i = 0; i <= rows*sizeof(data); i = i + sizeof(data))
		{
			for (int j = 0; j < cols; j++)
			{
				tmp = (&data[i])[j] + (&m.get_data()[i])[j];
				(&data[i])[j] = tmp;
			}
		}
		return 1;
	}
	else
		return 0;
}

int Matrix::MultiplyMatrix(Matrix& m1, Matrix& m2)
{

	return 1;
}

int main(void)
{
	Matrix matrixA(AROWS, ACOLS);
	Matrix matrixA1(AROWS, ACOLS);
	//Matrix matrixB(BROWS,BCOLS);
	//Matrix matrixB1(BROWS, BCOLS);

	srand(time(NULL));


	
	matrixA.show_data();
	cout << endl;
	matrixA1.show_data();
	cout << endl;
	matrixA.addMatrix(matrixA1);
	matrixA.show_data();
	cout << endl;

		
	system("pause");
}