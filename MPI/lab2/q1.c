#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char * argv[]){
    int size, rank;
    char str[20];

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Enter word: ");
		scanf("%s",str);
        printf("sending --%s-- to process 1 \n", str);
        MPI_Ssend(&str, sizeof(str), MPI_CHAR, 1, 42, MPI_COMM_WORLD);

        MPI_Recv(&str, sizeof(str), MPI_CHAR, 1, 43, MPI_COMM_WORLD, &status);
        printf("recieved --%s-- from process 1\n", str);    
    }

    if(rank == 1){
        MPI_Recv(&str, sizeof(str), MPI_CHAR, 0, 42, MPI_COMM_WORLD, &status);
        printf("recieved --%s-- from process 0\n", str);   
        
        for(int i =0; i< strlen(str); i++){
            if(str[i] >= 'A' && str[i] <= 'Z')
                str[i] += 32;
            else
                str[i] -= 32;
        }
        printf("sending --%s-- to process 0 \n", str);
        MPI_Send(&str, sizeof(str), MPI_CHAR, 0, 43, MPI_COMM_WORLD);
    }

    MPI_Finalize();

}

