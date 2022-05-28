#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

//#define n 10000

using namespace std::chrono;

//int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


int temp[100000000];

int main(int argc, char* argv[])
{	int n = 1000000;
	int a[n];
    for(int i=0;i<n;i++)
        a[i]=rand()%10;
	int rank, size, elements_per_process, n_elements_recieved;
	double starttime, stoptime, duration;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	starttime = MPI_Wtime();
	if (rank == 0) {
		int index, i;
		elements_per_process = n / size;

		if (size > 1) {
			for (i = 1; i < size - 1; i++) {
				index = i * elements_per_process;

				MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&a[index],elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			index = i * elements_per_process;
			int elements_left = n - index;

			MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&a[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		int sum = 0;
		for (i = 0; i < elements_per_process; i++)
			sum += a[i];
		int tmp;
		for (i = 1; i < size; i++) {
			MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,&status);
			int sender = status.MPI_SOURCE;
			sum += tmp;
		}

		printf("Sum of array is : %d\n", sum);
		stoptime = MPI_Wtime();
		duration = stoptime - starttime;
    	std::cout<< "duration " << duration <<std::endl;
	}
	else {
		MPI_Recv(&n_elements_recieved,1, MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
		MPI_Recv(&temp, n_elements_recieved,MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
		int partial_sum = 0;
		for (int i = 0; i < n_elements_recieved; i++)
			partial_sum += temp[i];

		MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}