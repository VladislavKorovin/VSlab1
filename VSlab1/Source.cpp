#define N 10

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

void fillMatrixWithValue(float** a, float value) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			a[i][j] = value;	
}

void negateMatrix(float** a, float** b) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			b[i][j] = (-1) * a[i][j];
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

void sendMatrix(float** matrix, int rank) {	
	for(int i = 0; i < N; i++)
		MPI_Send(matrix[i], N, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
}

void receiveMatrix(float** matrix, int rank) {
	MPI_Status status;
	for (int i = 0; i < N; i++)
		MPI_Recv(matrix[i], N, MPI_FLOAT, rank, 0, MPI_COMM_WORLD, &status);
}


int main(int argc, char **argv) {
	srand(time(nullptr));

	float** a = create_float_array(N);
	float** b = create_float_array(N);
	float** c = create_float_array(N);
	float** d = create_float_array(N);
	float** e = create_float_array(N);
	float** g = create_float_array(N);

	fillMatrix(a);
	fillMatrix(b);
	fillMatrix(c);
	fillMatrix(d);
	fillMatrix(e);
	fillMatrix(g);	

	int rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {	
		fillMatrixWithValue(a, 0.0);
		sendMatrix(a, 1);
	};

	if (rank == 1) {		
		receiveMatrix(b, 0);
		printMatrix(b);
	};
	
	MPI_Finalize();


	return(0);
	//_sleep(10000);
}




