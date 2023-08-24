#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
int rank,size;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if(rank%2==0)
{
int fact=1;
for(int i=1;i<=rank;i++)
{
fact=fact*i;
}
printf("Rank=%d factorial=%d \n",rank,fact);
}
else
{
int a=0,b=1,c=0;
for(int i=3;i<=rank;i++)
{
c=a+b;
a=b;
b=c;
}
printf("Rank=%d fibonacci number=%d \n",rank,c);
}
MPI_Finalize();
return 0;
}
