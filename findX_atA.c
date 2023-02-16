// Parallili euresi arithmou x se pinaka A[N] opou N=10mil


#include <stdio.h>
#include <stdlib.h> 
#include <mpi.h>
//#include <time.h> 

int main(int argc, char **argv)
{
//	srand(time(NULL)); //gia pragmatika random numbers
   	int rank, size;
   	double ta, tt; // metrisi xronou
	int N=2000000, A[N];
	int i, X;
	int count=0, All=0;


	MPI_Init(&argc, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) 
	{
		printf("Eisagogi arithmou X:");
  		scanf("%d", &X);
		for (i=0; i<N; i++) 
		{
			A[i]=rand() % 1000;
//			printf("\n\nTimi A=%d", A[i]);
		}
		A[N]=X;
	}

	ta = MPI_Wtime(); // Arxi metrisis xronou
   	MPI_Bcast(A, N, MPI_INT, 0, MPI_COMM_WORLD); 
	for (i=rank+1; i<N; i+=size) 
	{
		if (A[i]==A[N])
		{
			count+=1;
		}
	}

	MPI_Reduce(&count, &All, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) 
	{
      		tt = MPI_Wtime(); // Telos metrisis xronou
      		printf("\n\nO arithmos %d brethike fores:%d", X, All);
      		printf("\n\nXronos pou xreiastike:%.6f\n\n", tt-ta);
  	}		


	MPI_Finalize();
   	return 0;
}
