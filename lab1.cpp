#include <stdio.h>

#include <iostream>

#include "mpi.h"

using namespace std;



int main(int argc, char* argv[])

{
	int M = 500;

	double start, end, wastedTime;

	int ProcNum, ProcRank;

	int message, recvmessage;

	MPI_Status Status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	if (ProcRank == 0) {
		recvmessage = 128;
		start = MPI_Wtime();
	}


	for (int i = 0; i < M; i++)
	{
		MPI_Bcast(&recvmessage, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Reduce(&recvmessage, &message, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

		if (ProcRank == 0)
			recvmessage = message;
	}

	if (ProcRank == 0) {

		end = MPI_Wtime();

		wastedTime = end - start;

		cout << "time:  " << wastedTime;

	}

	MPI_Finalize();

	return 0;

}