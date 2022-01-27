#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int id, size;
    int i;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int T1 = 1;
    int T2 = 2;
    int T3 = 3;
    int T4 = 4;


    int message = 5;
    int buffer;

    if (id == 0) 
    {
        for (i = 1; i < size; i++)
        {
            if(i%2==0)
                MPI_Send(&message, 1, MPI_INT, i, T2, MPI_COMM_WORLD);
            else
                MPI_Send(&message, 1, MPI_INT, i, T1, MPI_COMM_WORLD);
        }
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&buffer, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("MPI process %d received value %d, with tag %d.\n", i, buffer, status.MPI_TAG);
        }
    }
    else if (id%2==0)
    {
        MPI_Recv(&buffer, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("MPI process %d received value %d, with tag %d. Sending acknowledgement T4..\n", id, buffer, status.MPI_TAG);
        int squared = buffer * buffer;
        MPI_Send(&squared, 1, MPI_INT, 0, T4, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&buffer, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("MPI process %d received value %d, with tag %d. Sending acknowledgement T3..\n", id, buffer, status.MPI_TAG);
        int cubed = buffer * buffer * buffer;
        MPI_Send(&cubed, 1, MPI_INT, 0, T3, MPI_COMM_WORLD);
    }


    MPI_Finalize();

    return 0;
}