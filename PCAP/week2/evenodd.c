#include "mpi.h"
#include <stdio.h>
#define bufsize 50
int main(int argc, char *argv[])
{
int rank,size,x;
int n[512];
int num[10];
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Buffer_attach(n,512);
MPI_Status status;
if(rank==0)
{
printf("Enter array: ");
for(int i=0;i<size;i++)
{
scanf("%d",&num[i]);
}
for(int i=0;i<size-1;i++)
{
printf("%d ",num[i]);
}
printf("\n");
for(int i=1;i<size;i++)
{
MPI_Bsend(&num[i-1],1,MPI_INT,i,0,MPI_COMM_WORLD);
}
}
else
{
MPI_Recv(&num[rank-1],1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
if(rank%2==0)
{
fprintf(stdout,"Even rank %d gives square of %d: %d \n",rank,num[rank-1],(num[rank-1]*num[rank-1]));
fflush(stdout);
}
else
{
fprintf(stdout,"Odd rank %d gives cube of %d: %d \n",rank,num[rank-1],(num[rank-1]*num[rank-1]*num[rank-1]));
fflush(stdout);
}
}
MPI_Buffer_detach(n,&x);
MPI_Finalize();
return 0;
}
