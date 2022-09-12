#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5

/*

행렬이 여러 개일 때 하나의 function으로 처리하는 방법을 고안

*/


int get_data(int(*p)[ACOLS], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < ACOLS; j++)
			p[i][j] = rand() % (n * n);
	return 1;
}

int get_data2(int(*p)[BCOLS], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < BCOLS; j++)
			p[i][j] = rand() % (n * n);
	return 1;
}



void show_data(int(*p)[ACOLS], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < ACOLS; j++)
			printf("%d ", p[i][j]);
				printf("\n");
	}
	printf("\n");
}

void show_data2(int(*p)[BCOLS], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < BCOLS; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
	printf("\n");
}

void show_data3(int(*p)[CCOLS], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < CCOLS; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
	printf("\n");
}

void multiply(int matrixA[][ACOLS], int ar, int matrixB[][BCOLS], int br, int matrixC[][CCOLS], int cr) 
{
	int tmpC = 0;
	for (int i = 0; i < AROWS; i++) 
	{
		for (int j = 0; j < BCOLS; j++)
		{
			for (int k = 0; k < ACOLS; k++)
				tmpC += matrixA[i][k] * matrixB[k][j];
			matrixC[i][j] = tmpC;
			tmpC = 0;
		}
	}
	printf("\n");
}

int main(void)
{
	int matrixA[AROWS][ACOLS];
	int matrixB[BROWS][BCOLS];
	int matrixC[CROWS][CCOLS];

	srand(time(NULL));

	get_data(matrixA, AROWS);
	show_data(matrixA, AROWS);
	get_data2(matrixB, BROWS);
	show_data2(matrixB, BROWS);

	multiply(matrixA, AROWS, matrixB, BROWS, matrixC, CROWS);
	show_data3(matrixC, CROWS);
	system("pause");

	return 0;
}