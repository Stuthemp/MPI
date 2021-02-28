#include <stdio.h>

#include <iostream>

#include "mpi.h"

using namespace std;



int main(int argc, char* argv[])

{
	int M = 20000000;

	double start, end, wastedTime;

	int ProcNum, ProcRank;

	int message = 128, recvmessage;

	MPI_Status Status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	if (ProcRank == 0)

		start = MPI_Wtime();


	for (int i = 0; i < M; i++)

	{

		if (ProcRank == 0) {


			for (int k = 1; k < ProcNum; k++) {

				//Отправляем сообщение от процесса ранга 0 всем остальным
				MPI_Send(&message, 1, MPI_INT, k, 0, MPI_COMM_WORLD);

			}

			for (int k = 1; k < ProcNum; k++) {

				//Получаем сообщения от процессов
				MPI_Recv(&recvmessage, 1, MPI_INT, k, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

			}

		}

		else { 

			//Получаем сообщения от процесса 0 ранга
			MPI_Recv(&recvmessage, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

			//Отправляем сообщения обратно в процесс 0
			MPI_Send(&recvmessage, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

		}

	}

	if (ProcRank == 0) {

		end = MPI_Wtime();

		wastedTime = end - start;

		cout << "time:  " << wastedTime;

	}

	MPI_Finalize();

	return 0;

}
