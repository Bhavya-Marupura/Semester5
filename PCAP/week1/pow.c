#include "mpi.h"
#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[])
{
int rank,size,x=10;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
printf("pow=%f of rank=%d \n",pow(x,rank),rank);
MPI_Finalize();
return 0;
}
