#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank, x = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(rank == 0){
        for(int i = 1; i < size; i++){
            MPI_Send(&x, 1, MPI_INT, i, 42, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(&x, 1, MPI_INT, 0, 42, MPI_COMM_WORLD, &status);
        printf("recieved %d from process 0 in process %d\n", x, rank);
    }

    MPI_Finalize();
    return 0;
}