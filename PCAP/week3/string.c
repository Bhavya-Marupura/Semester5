#include "mpi.h"
#include <stdio.h>
#include<string.h>
int is_vowel(char c) {
char vowels[] = "AEIOUaeiou";
for (int i = 0; i < strlen(vowels); i++) {
if (c == vowels[i]) {
return 1;
}
}
return 0;
}

int main(int argc, char *argv[])
{
int rank,size,n=0,chunck=0;
char string[50];
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
int f_vowel[size];
int fin_vowels=0;
if(rank==0)
{
printf("Enter the string= \n");
scanf("%s",string);
n=strlen(string);
}
MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

MPI_Bcast(string,n,MPI_CHAR,0,MPI_COMM_WORLD);
if(n%size==0)
{
chunck=n/size;
}
else
{
printf("String not divisible");
}
int vowels=0,nvowels=0;
for(int i=rank*chunck;i<(rank+1)*chunck;i++)
{
vowels=is_vowel(string[i]);
nvowels=nvowels+vowels;
}
int f=chunck-nvowels;
MPI_Gather(&f,1,MPI_INT,f_vowel,1,MPI_INT,0,MPI_COMM_WORLD);
if(rank==0)
{
for(int i=0;i<size;i++)
{
fin_vowels+=f_vowel[i];
printf("Process %d found %d non-vowels\n",i,f_vowel[i]);
}
printf("Root process %d has %d total number of vowels\n ",rank,fin_vowels);
}
MPI_Finalize();
return 0;
}
