#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
int rank,size,x=10,y=5;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
switch(rank)
{
case 0:
{
printf("Add for rank=%d \n",rank);
printf("%d \n",x+y);
printf("\n");
break;
}
case 1:
{
printf("Sub for rank=%d \n",rank);
printf("%d \n",x-y);
printf("\n");
break;
}
case 2:
{
printf("Multiply for rank=%d \n",rank);
printf("%d \n",x*y);
printf("\n");
break;
}
case 3:
{
printf("Divide for rank=%d \n",rank);
printf("%d \n",x/y);
printf("\n");
break;
}
}
MPI_Finalize();
return 0;
}
