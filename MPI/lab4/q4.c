#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank, a[4][4], b[4][4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank ==0){
        printf("Enter 16 elements: \n");
        for(int i =0; i<4; i++){
            for(int j = 0; j<4; j++){
                scanf("%d", &a[i][j]);
                b[i][j] = 0;
            }
        }
    }
    
    for(int i =0; i<4; i++){
        MPI_Bcast(a[i], 4, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(b[i], 4, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    MPI_Scan(a[rank], b[rank], 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // for(int i =0; i<4; i++)
    //     for(int j = 0; j<4; j++)
    //         printf("%d\t", b[i][j]);
    
    MPI_Gather(b[rank], 4, MPI_INT, a[rank], 4, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for(int i =0; i<4; i++){
            for(int j = 0; j<4; j++){
                printf("%d\t", a[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}