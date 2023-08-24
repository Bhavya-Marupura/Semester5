#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
int rank,size;
int num;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if(rank==0)
{
printf("Master process %d send num: \n",rank);
scanf("%d",&num);
for(int i=1;i<size;i++)
{
MPI_Send(&num,1,MPI_INT,i,0,MPI_COMM_WORLD);
}
}
else
{
MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
fprintf(stdout,"Slave process %d recieved %d \n",rank,num);
fflush(stdout);
}
MPI_Finalize();
return 0;
}
