#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[])
{
int rank,size,num,n,fact=1,len,sum=0;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
num=rank+1;
int e1,e2;
char estr[100];
e1= MPI_Scan(&num,&fact,1,MPI_INT,MPI_PROD,MPI_COMM_WORLD);
if(e1!=MPI_SUCCESS)
{
printf("ERROR IN FACT CALCULATION\n");
MPI_Error_string(e1,estr,&len);
printf("%s",estr);
}
printf("Process:%d => (fact) %d!:%d\n",rank,num,fact);
e2=MPI_Scan(&fact,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
if(e2!=MPI_SUCCESS)
{
printf("ERROR IN SUM CALCULATION\n");
MPI_Error_string(e2,estr,&len);
printf("%s",estr);
}
printf("Process:%d => (sum) %d:%d\n",rank,num,sum);
if(rank==size-1)
{
printf("Final Sum = %d\n",sum);
}
MPI_Finalize();
return 0;
}
