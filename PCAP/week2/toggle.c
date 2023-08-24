#include "mpi.h"
#include <stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
int rank,size;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
char word[10];
int count=0;
if(rank==0)
{
printf("word sent by process %d: ",rank);
scanf("%s",word);
count=strlen(word);
MPI_Send(&count,1,MPI_INT,1,0,MPI_COMM_WORLD);
MPI_Ssend(word,count,MPI_CHAR,1,0,MPI_COMM_WORLD);
MPI_Recv(word,count,MPI_CHAR,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Modified word %s recieved by process %d: ",word,rank+1);
}
else if(rank==1)
{
MPI_Recv(&count,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
MPI_Recv(word,count,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
for(int i=0;i<count;i++)
{
if(word[i]>='a' && word[i]<='z')
{
word[i]=word[i]-32;
}
else
{
word[i]=word[i]+32;
}
}
MPI_Ssend(word,count,MPI_CHAR,0,1,MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}
