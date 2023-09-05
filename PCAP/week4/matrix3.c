#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[])
{
int rank,size;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size); 
int mat[3][3],row[3],i,j,key,count,tot_count;
if(rank==0)
{
printf("Enter the elements for 3X3 MAT: \n");
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
scanf("%d",&mat[i][j]);
}
}
printf("Enter element to be searched= \n");
scanf("%d",&key);
}
MPI_Bcast(&key,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Scatter(mat,3,MPI_INT,row,3,MPI_INT,0,MPI_COMM_WORLD);
for(i=0;i<3;i++)
{
if(row[i]==key)
{
count++;
}
}
printf("Process %d found %d occurences of %d\n",rank,count,key);
MPI_Reduce(&count,&tot_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
MPI_Bcast(&tot_count,1,MPI_INT,0,MPI_COMM_WORLD);
if(rank==size-1)
{
printf("Total Occurences of %d in 3X3 MAT = %d\n",key,tot_count);
}
MPI_Finalize();
return 0;
}
