#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

#define size 3

class matrix_args
{
public:
	int A[size][size] = {{1, 2, 3},
						 {4, 5, 6},
						 {7, 8, 9}};

	int B[size][size] = {{9, 8, 7},
						 {6, 5, 4},
						 {3, 2, 1}};
};

void *Addition(void *args)
{
	matrix_args *M = (matrix_args *)args;
	cout << "Addition of Matrices\n";
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			cout << M->A[i][j] + M->B[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << endl;

	return NULL;
}

void *Subtraction(void *args)
{
	matrix_args *M = (matrix_args *)args;
	cout << "Subtraction of Matrices\n";
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{

			cout << M->A[i][j] - M->B[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << endl;

	return NULL;
}

void *Multiplication(void *args)
{
	matrix_args *M = (matrix_args *)args;
	cout << "Multiplication of Matrices\n";
	int sum;
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			sum = 0;
			for (int k = 0; k < size; k++)
			{
				sum += M->A[i][k] * M->B[k][j];
			}
			cout << sum << "\t";
		}
		cout << "\n";
	}
	cout << endl;

	return NULL;
}

int main()
{
	matrix_args args;

	pthread_t Add, Sub, Multi;

	int ret1, ret2, ret3;

	ret1 = pthread_create(&Add, NULL, Addition, &args);
	ret2 = pthread_create(&Sub, NULL, Subtraction, &args);
	ret3 = pthread_create(&Multi, NULL, Multiplication, &args);

	if (ret1 == 0 && ret2 == 0 && ret3 == 0)
	{
		cout << "\nAll Threads created Sucessfully" << endl;
	}
	else
	{
		cout << "\nAll Threads NOT created Sucessfully" << endl;
	}

	pthread_join(Add, NULL);
	pthread_join(Sub, NULL);
	pthread_join(Multi, NULL);

	return 0;
}
