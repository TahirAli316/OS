#include <stdio.h>
#include <pthread.h>
//#include <linux/time.h>
#include <time.h>

// size of array 
#define MAX 16 
 
// maximum number of threads 

#define NUM_THREADS 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 }; 
    int sum[NUM_THREADS] = { 0 }; 
    int part = 0;

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
   
    
     int thread_part = part++; 
 
    for (int i = thread_part * (MAX / NUM_THREADS); i < (thread_part + 1) * (MAX / NUM_THREADS); i++) 
        sum[thread_part] += a[i]; 

    printf("Thread %d computed sum of part %d: %d\n", thread_id, thread_part, sum[thread_part]);

    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    struct timespec start, end;
    double elapsed_timep, elapsed_timet;

    clock_gettime(CLOCK_MONOTONIC, &start);

    

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_timep = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

   // printf("Execution time: %f seconds\n", elapsed_timep);
   
   clock_gettime(CLOCK_MONOTONIC, &start);
  int total_sum = 0; 
    for(int i = 0; i < NUM_THREADS; i++){ 
        total_sum += sum[i]; 

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_timet = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    }
 
    printf("in main Total sum: %d\n", total_sum);
    printf("Execution time subparts: %f seconds\n", elapsed_timep);
    printf("Execution time total: %f seconds\n", elapsed_timet);

    return 0;
}