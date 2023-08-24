#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
int rank,size,N,M,a[100],sum=0;
double total_avg=0,sum_avg=0;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
N=size;
if(rank==0)
{
printf("Enter M value= \n");
scanf("%d",&M);
printf("Enter NxM values into array= \n");
for(int i=0;i<N*M;i++)
{
scanf("%d",&a[i]);
}
}
MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
int b[M];
MPI_Scatter(a,M,MPI_INT,b,M,MPI_INT,0,MPI_COMM_WORLD);
fprintf(stdout,"Process %d recieved %d elemnts \n",rank,M);
fflush(stdout);
for(int i=0;i<M;i++)
{
sum=sum+b[i];
}
double average=(double)sum/M;
double avg[size];
MPI_Gather(&average,1,MPI_DOUBLE,avg,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
if(rank==0)
{
for(int i=0;i<size;i++)
{
sum_avg=sum_avg+avg[i];
fprintf(stdout,"Process %d average is %lf \n",i,avg[i]);
fflush(stdout);
}
total_avg=sum_avg/size;
printf("TOTAL AVERAGE= %lf\n",total_avg);
}
MPI_Finalize();
return 0;
}
