/**
 * Created on - Fri Apr 17 2020 9:16:32 
 * @author Berkant Güneş 20160807013
 * PI calculation with multithreading by using of Taylor Series
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define PI 3.141592

void *runner(void *arg);
double getTime();


pthread_t *workers;
double *nodeResult;

typedef struct Range
{	int index,first,nodeLength;
} Range;

int main(int argc, char** args){
    int i = 0, j = 0;

    //starts thread and node count
    int threadCount = 1;
    int nodeCount = 1;
    double pi = 0.0;
    double start_t = 0, elapsed_t = 0;

    // thread and node number are entered by the user
    printf("Input the number of threads:");
    scanf("%d", &threadCount);
    printf("\nInput the number of nodes:");
    scanf("%d", &nodeCount);
   

    workers = (pthread_t*)malloc(sizeof(pthread_t) * threadCount);
    nodeResult = (double *)malloc(sizeof(double) * nodeCount);

    // record the start time
    start_t = getTime();

    // create threads
    int last_node = -1;
    int range_len = nodeCount /threadCount;

    for(i = 0; i < threadCount; i++)
    {
    	// Assigning the range to the thread
    	Range rng;
        rng.index = i;
        rng.first = last_node + 1;
        rng.nodeLength = (i + 1 == threadCount ? range_len + (nodeCount % threadCount) : range_len);
        last_node = rng.first + rng.nodeLength - 1;

        pthread_create(&workers[i], NULL, runner, &rng); 
        pthread_join(workers[i], NULL);
    }
    	
	// Waiting for threads to complete
	for (i = 0; i < threadCount; i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
    //calculate PI number
    for(i = 0; i < threadCount; i++) 
    {
        pi += nodeResult[i];
    }
    pi *= 4;
    printf("---------------------------Output-----------------------------\n");  
    printf("Pi: %f, ", pi);
    printf("Appoximaion Error: %f, ", (PI - pi));

    elapsed_t = (getTime() - start_t) * 1000;

    printf("Elapsed time: %fms\n", elapsed_t);

}

double calcSingleNode(int idx) 
{
    int denominator = (idx *2 + 1) * (int)pow(-1.0, (double)idx);

    printf("Polynomial: 1/%d\n", denominator);

    return 1.0 / denominator;
}

void *runner(void *arg)
{
    Range rng = *(struct Range *)arg;
    int count = 0;
    double res = 0;

    while(count < rng.nodeLength) 
    {
    	int node_idx = rng.first + count;
	    res += calcSingleNode(node_idx);

    	count++;
    }

    nodeResult[rng.index] = res;
}

double getTime() {
	struct timeval  tv;
	gettimeofday(&tv, NULL);

	double time_in_millisecond = (double)(tv.tv_sec) + (double)(tv.tv_usec) / 1000000;

    return time_in_millisecond;
}


