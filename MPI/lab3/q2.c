#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank, m, n, arr[20], rec[20];
    float sum, sol[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Enter m: ");
        scanf("%d", &m);

        printf("\nEnter %d elements", m*size);
        for(int i = 0; i<m*size; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, m, MPI_INT, rec, m, MPI_INT, 0, MPI_COMM_WORLD);

    sum = 0;
    for(int i = 0; i<m; i++){
        sum += rec[i];
    }
    sum = sum/m;
    printf("\nAverage of values in process %d : is %f.\n",rank,sum);

    MPI_Gather(&sum, 1, MPI_FLOAT, sol, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        sum = 0;
        for(int i = 0; i<size; i++){
            sum += sol[i];
        }
        sum = sum/size;

        printf("\navg = %f", sum);
    }
    MPI_Finalize();
    return 0;
}