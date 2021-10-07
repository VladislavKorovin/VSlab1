#define N 5

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

  cout << "Add time: " << chrono::duration_cast<chrono::nanoseconds>(endT - beginT).count() << "ns\n";
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

float** create_twodim_float_array(int size) {
  float** a = new float* [size];
  for (int i = 0; i < size; i++) {
    a[i] = new float[size];
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


int main(int* argc, char** argv) {
  float** A = create_twodim_float_array(N);
  fillMatrix(A);
  float** B = create_twodim_float_array(N);
  fillMatrix(B);
  float** C = create_twodim_float_array(N);
  fillMatrix(C);
  float** D = create_twodim_float_array(N);
  fillMatrix(D);
  float** E = create_twodim_float_array(N);
  fillMatrix(E);
  float** G = create_twodim_float_array(N);
  fillMatrix(G);

  int rank, size;
  double time = 0, time1, time2;
  MPI_Status status;

  //инициализация MPI
  MPI_Init(argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Started: rank %d of %d\n", rank, size);

  if (size != 4) {
    printf("Некорректное число процессов, необходимо 4 процесса.\n");
    return -1;
  }

  switch (rank) {
  case 0: {
    float** sub_res = create_twodim_float_array(N);
    sub(A, B, sub_res);

    printf("Result of A-B:\n");
    printMatrix(sub_res);

    MPI_Request requests[3];
    MPI_Isend(sub_res[0], N, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &requests[0]);

    /* float** res_of_GxG = create_twodim_float_array(N);
     MPI_Irecv(res_of_GxG, N, MPI_INT, 1, 2, MPI_COMM_WORLD, &);

     float** mult_res = create_twodim_float_array(N);
     mult(sub_res, sub_res, mult_res);

     printMatrix(mult_res);*/

    break;
  }
  case 1: {
    float** sub_res = create_twodim_float_array(N);
    
    MPI_Request requests[3];
    MPI_Status statuses[3];
    MPI_Irecv(sub_res[0], N, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &requests[0]);

    printf("WE GOT THIS:\n");
    if (MPI_Wait(&requests[0], &statuses[0]) == MPI_SUCCESS) {
      printMatrix(sub_res);
    };

    break;
  }
  case 2:
    break;
  case 3:
    break;
  }

  MPI_Finalize();
}