#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //use sleep
#include "mpi.h"

MPI_Status status;

double resolve_pi(int n, int core, int argc, char const *argv[])
{
    int numtasks, taskid;
    int hit = 0;
    int total_hit = 0;
    double x, y;
    double pi =0.00;
    srand(time(NULL));
    // printf("helo");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    for (int i = 0; i < n / core; i++)
    {
        x = ((double)rand() / (RAND_MAX));
        y = ((double)rand() / (RAND_MAX));
        //    printf("x=%1.2f y= %1.2f\n",x,y);
        if (x * x + y * y < 1)
        {
            hit++;
        }
    }
    // printf("hit=%d", hit);
    MPI_Reduce(&hit, &total_hit, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);
    // printf("hit= %d\n",hit);
    if (taskid == 0)
    {
        pi = (4.0 * ((double)total_hit) / ((double)n));
        // printf("hit_total=%d\n",total_hit);
    } 
    MPI_Finalize();
    return pi;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    int cores = atoi(argv[2]);
    time_t start_process = time(NULL);
    double pi = resolve_pi(N, cores,argc, *argv);
    time_t end_process = time(NULL);
    if(pi==0.00){
        return 0;
    }
    FILE *fp;
    char outputFilename[] = "parallel_time.txt";

    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "\nProblem=%d Pi=%1.15f process time=%ld\n", N, pi, (end_process - start_process));
    // printf("process time = %ld\n",(end_process-start_process));
    fclose(fp);
    return 0;
}


