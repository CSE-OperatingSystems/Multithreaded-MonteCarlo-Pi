#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define NUM_ITERATIONS 1000000
#define pi 3.14159265358979323846
int num_threads;

long long global_count = 0;
pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attr;
void* monte_carlo(void* arg) {
    for (long long i = 0; i < NUM_ITERATIONS/num_threads; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            //critical section
            pthread_mutex_lock(&mutex);
            global_count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}
int main() {
    // csv file for saving time result
    FILE *fp = fopen("time_results.csv", "w");
    double base_time = 0.0;
    fprintf(fp, "Threads,Time Taken 1,Time Taken 2,Time Taken 3,Time Taken 4,Time Taken 5,Average Time,Speedup,Efficiency\n");
    for(int k=1; k<=4096; k*=2){
        double time_taken[5];
        for(int j=0; j<5; j++){
            // Measure current time
            clock_t start = clock();
            num_threads = k;
            pthread_t threads[num_threads];
            pthread_mutexattr_init(&mutex_attr);
            pthread_mutex_init(&mutex, &mutex_attr);
            for (int i = 0; i < num_threads; i++) {
                pthread_create(&threads[i], NULL, monte_carlo, NULL);
            }
            for (int i = 0; i < num_threads; i++) {
                pthread_join(threads[i], NULL);
            }
            clock_t end = clock();
            double pi_estimate = (double)global_count / (NUM_ITERATIONS/num_threads*num_threads) * 4.0;
            printf("Threads: %d, ", num_threads);
            printf("Estimated Pi: %f\n", pi_estimate);
            time_taken[j] = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Time taken: %f seconds\n", time_taken[j]);
            printf("Difference from actual Pi: %f\n\n", fabs(pi - pi_estimate));
            pthread_mutex_destroy(&mutex);
            pthread_mutexattr_destroy(&mutex_attr);
            global_count = 0; // Reset global count for the next iteration
        }
        fprintf(fp, "%d", num_threads);
        for(int j=0; j<5; j++){
            fprintf(fp, ",%f", time_taken[j]);
        }
        double average_time = 0.0;
        for(int j=0; j<5; j++){
            average_time += time_taken[j];
        }        average_time /= 5.0;
        fprintf(fp, ",%f", average_time);
        if(k == 1){
            base_time = average_time;
        }
        double speedup = base_time / average_time;
        double efficiency = speedup / num_threads;
        fprintf(fp, ",%f", speedup);
        fprintf(fp, ",%f", efficiency);
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
