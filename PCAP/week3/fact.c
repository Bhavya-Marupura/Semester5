#include "mpi.h"
#include <stdio.h>
int fact(int num)
{
if(num==0)
{
return 1;
}
else
{
return num*fact(num-1);
}
}
int main(int argc, char *argv[])
{
int rank,size,a[10],b[10],c,N;
int sum=0;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
N=size;
if(rank==0)
{
printf("Enter the values of array= \n");
for(int i=0;i<N;i++)
{
scanf("%d",&a[i]);
}
}
MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
printf("Received %d in process %d\n",c,rank);
c=fact(c);
MPI_Gather(&c,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
if(rank==0)
{
printf("Gathered result in root process %d= ",rank);
for(int i=0;i<N;i++)
{
sum=sum+b[i];
printf("%d ",b[i]);
}
printf("SUM= %d",sum);
}

MPI_Finalize();
return 0;
}
