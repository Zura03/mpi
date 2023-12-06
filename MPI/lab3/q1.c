#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]){
    int size, rank;
    int a[size], fact[size], c, sum = 0, ans = 1;;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        for(int i =0; i<size; i++)
            scanf("%d", &a[i]);
    }

    MPI_Scatter(a, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD );
    
    for(int i = 1; i<=c; i++){
        ans = ans*i;
    }

    MPI_Gather(&ans, 1, MPI_INT, fact, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for(int i = 0; i<size; i++){
            sum += fact[i];
        }
        printf("sum = %d", sum);
    }

    // MPI_Reduce(&ans, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // if(rank == 0){
    //     printf("sum = %d", sum);
    // }
    MPI_Finalize();
    return 0;
}