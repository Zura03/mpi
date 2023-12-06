#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char * argv[]){
    int size, rank, l;
    char s1[20], s2[20], c1[20], f[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank = 0){
        scanf("%s", s1);
        scanf("%s", s2);

        // m = strlen(s1) / size;
        l = strlen(s1);
    }

    MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(s1, 1, MPI_CHAR, &c1[0], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, 1, MPI_CHAR, &c1[1], 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    c1[2] = '\0';
    MPI_Gather(c1, 2, MPI_CHAR, f, 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0){
        f[l*2] = '\0';
        printf("%s", f);
    }

    MPI_Finalize();
    return 0;
}