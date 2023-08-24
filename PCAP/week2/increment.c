#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
int rank,size;
int num;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, & size);
if(rank==0)
{
printf("Root process %d: gets value= ",rank);
scanf("%d",&num);
num++;
MPI_Send(&num,1,MPI_INT,1,0,MPI_COMM_WORLD);
MPI_Recv(&num,1,MPI_INT,size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Root process %d recieved %d from last process %d \n",rank,num,size-1);
}
else if(rank<size-1)
{
MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Process %d recieved %d from process %d \n",rank,num,rank-1);
num++;
MPI_Send(&num,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
}
else
{
MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Process %d recieved %d from process %d\n",rank,num,rank-1);
num++;
MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
}


MPI_Finalize();
return 0;
}
