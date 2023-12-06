#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char * argv[]){
    int size, rank, l, sum;
    char str[20], recv[20];
    int nonv_p[20];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("enter string: ");
        scanf("%s", str);
        l = strlen(str)/size;
    }
    MPI_Bcast(&l, 1,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, l, MPI_CHAR, recv, l, MPI_CHAR, 0, MPI_COMM_WORLD);

    int nvowels = 0;
    for(int i =0; i<l; i++){
        if(recv[i] =='a' || recv[i] == 'e' || recv[i] == 'i' || recv[i] == 'o' || recv[i] == 'u')
            continue;
        nvowels++;
    }

    MPI_Gather(&nvowels, 1, MPI_INT, nonv_p, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        sum = 0;
        for(int i =0; i<size; i++){
            printf("\nprocess %d found %d non-vowels\n", i, nonv_p[i]);
            sum += nonv_p[i];
        }
        printf("\ntotal non-vowels: %d", sum);
    }
    MPI_Finalize();
    return 0;
}