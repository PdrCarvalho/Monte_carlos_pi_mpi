#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double resolve_pi(int n)
{
    int hit = 0;
    double x,y;
    srand(time(NULL));
    for (int i = 0; i < n ; i++)
    {
       x =  ((double) rand() / (RAND_MAX));
       y = ((double) rand() / (RAND_MAX));
       if (x*x + y*y < 1){
           hit++;
       }

    }
    return (4.0*((double)hit)/((double)n));
}

int main(int argc, char const *argv[])
{
    int N = atol(argv[1]);
    time_t start_process = time(NULL);
    double pi = resolve_pi(N);
    // double pi = 0.00;
    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "serial_time.txt";

    fp = fopen(outputFilename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp,"\nProblem=%d Pi=%1.15f process time=%ld\n", N,pi,(end_process-start_process));
    // printf("process time = %ld\n",(end_process-start_process));
    fclose(fp);
    return 0;
}
