#define N 8000

#include "mpi.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void add(float** a, float** b, float** result) {

	auto beginT = chrono::high_resolution_clock::now();	

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			result[i][j] = a[i][j] + b[i][j];	

	auto endT = chrono::high_resolution_clock::now();

	cout << "Add time: " << chrono::duration_cast<chrono::nanoseconds>(endT - beginT).count()<<"ns\n";	
}

void div(float** a, float** b, float** result) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			result[i][j] = a[i][j] / b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Div time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void sub(float** a, float** b, float** result) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			result[i][j] = a[i][j] - b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Sub time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void mult(float** a, float** b, float** result) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			result[i][j] = a[i][j] * b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Mult time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void fillMatrix(float** a) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			a[i][j] = rand() % 1000 - 499;
			if (a[i][j] == 0)
				a[i][j] = 1;
		}
}

void printMatrix(float** a) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << a[i][j] << "\t";
		cout << "\n";
	}
	cout << "\n";
}

float** create_float_array(int dim) {
	float** a = new float* [dim];
	for (int i = 0; i < dim; i++) {
		a[i] = new float[dim];
	}
	return a;
}

int free_memory(float** aArray, int dim) {
	for (int i = 0; i < dim; i++) {
		free(aArray[i]);
	}
	free(aArray);

	return 0;
}


int main(int *argc, char **argv) {
	srand(time(nullptr));

	float** a = create_float_array(N);
	float** b = create_float_array(N);
	float** c = create_float_array(N);

	fillMatrix(a);
	fillMatrix(b);
	
	add(a, b, c);
	sub(a, b, c);
	mult(a, b, c);
	div(a, b, c);

	free_memory(a, N);
	free_memory(b, N);
	free_memory(c, N);
	_sleep(10000);
}




