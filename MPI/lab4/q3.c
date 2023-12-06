#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank, a[3][3], key, count = 0, total_count;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank ==0){
        printf("Enter 9 elements: ");
        for(int i =0; i<3; i++)
            for(int j = 0; j<3; j++)
                scanf("%d", &a[i][j]);

        printf("Enter key: ");
        scanf("%d", &key);
    }

    for(int i =0; i<3; i++)
        MPI_Bcast(a[i], 3, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int j = 0; j<3; j++)
        if(a[rank][j] == key)
            count++;

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("count of %d == %d", key, total_count);

    MPI_Finalize();
    return 0;
}