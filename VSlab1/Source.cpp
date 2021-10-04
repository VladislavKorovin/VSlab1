#define N 2
#define M 2

#include "mpi.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void add(double a[N][M], double b[N][M], double result[N][M]) {

	auto beginT = chrono::high_resolution_clock::now();	

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			result[i][j] = a[i][j] + b[i][j];	

	auto endT = chrono::high_resolution_clock::now();

	cout << "Add time: " << chrono::duration_cast<chrono::nanoseconds>(endT - beginT).count()<<"ns\n";	
}

void div(double a[N][M], double b[N][M], double result[N][M]) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			result[i][j] = a[i][j] / b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Div time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void sub(double a[N][M], double b[N][M], double result[N][M]) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			result[i][j] = a[i][j] - b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Sub time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void mult(double a[N][M], double b[N][M], double result[N][M]) {

	auto beginT = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			result[i][j] = a[i][j] * b[i][j];

	unsigned int endTime = clock();
	auto endT = chrono::high_resolution_clock::now();

	cout << "Mult time: " << chrono::duration_cast<std::chrono::nanoseconds>(endT - beginT).count() << "ns\n";
}

void fillMatrix(double a[N][M]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			a[i][j] = rand() % 1000 - 499;
			if (a[i][j] == 0)
				a[i][j] = 1;
		}
}

void printMatrix(double a[N][M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << a[i][j] << "\t";
		cout << "\n";
	}
	cout << "\n";
}


int main(int *argc, char **argv) {
	srand(time(nullptr));
	double a[N][M];
	double b[N][M];
	fillMatrix(a);
	fillMatrix(b);	
	double c[N][M];
	add(a, b, c);
	sub(a, b, c);
	mult(a, b, c);
	div(a, b, c);

}




