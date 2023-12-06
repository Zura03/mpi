#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank, recvd;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    int arr[size];
    
    if(rank == 0){
        for(int i =0; i<size; i++){
            scanf("%d", &arr[i]);
            MPI_Send(&arr[i], 1, MPI_INT, i, 42, MPI_COMM_WORLD);
        }
    }
    
    if(rank%2 == 0){
        MPI_Recv(&recvd, 1, MPI_INT, 0, 42, MPI_COMM_WORLD, &status);
        printf("Recieved %d from process 0 in process %d\n", recvd, rank);
        
        recvd = recvd*recvd;
        printf("value = %d in process %d\n", recvd, rank);
    }

    if(rank%2 != 0){
        MPI_Recv(&recvd, 1, MPI_INT, 0, 42, MPI_COMM_WORLD, &status);
        printf("Recieved %d from process 0 in process %d\n", recvd, rank);
        
        recvd = recvd*recvd*recvd;
        printf("value = %d in process %d\n", recvd, rank);
    }

    MPI_Finalize();
    return 0;
}