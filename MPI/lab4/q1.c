#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int fact = 1, factsum;
    for(int i = 2; i<=rank+1; i++)
        fact = fact * i;

    MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("process %d gave sum %d\n", rank, factsum);

    MPI_Finalize();
    return 0;
}