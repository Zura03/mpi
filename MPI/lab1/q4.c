#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char * argv[]){
    int size, rank;
    char str[5] = "Hello";
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    if(str[rank] >= 'A' && str[rank] <= 'Z')
        str[rank] += 32;
    else
        str[rank] -= 32;
    
    printf("Process %d : %s\n",rank,str);
    MPI_Finalize();
}