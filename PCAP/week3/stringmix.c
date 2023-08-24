#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
int rank,size;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
char str1[50], str2[50], str[50], temp[50];
int n;
if(rank==0)
{
printf("Enter the first string= \n");
scanf("%s",str1);
printf("ENter the second string= \n");
scanf("%s",str2);
n=strlen(str1);
}
MPI_Scatter(str1,1,MPI_CHAR,&temp[0],1,MPI_CHAR,0,MPI_COMM_WORLD);
MPI_Scatter(str2,1,MPI_CHAR,&temp[1],1,MPI_CHAR,0,MPI_COMM_WORLD);
temp[2]='\0';
MPI_Gather(temp,2,MPI_CHAR,str,2,MPI_CHAR,0,MPI_COMM_WORLD);
if(rank==0)
{
str[n*2]='\0';
printf("OUTPUT STRING = %s ",str);
}
MPI_Finalize();
return 0;
}
