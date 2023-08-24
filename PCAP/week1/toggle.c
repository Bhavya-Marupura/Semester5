#include "mpi.h"
#include <stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
int rank,size;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
char a[5]="HELLO";
for(int i=0; i<size; i++)
{
if(i==rank)
{
a[rank]=a[rank]+32;
}
}
printf("for rank=%d word=%s \n",rank,a);
MPI_Finalize();
return 0;
}
