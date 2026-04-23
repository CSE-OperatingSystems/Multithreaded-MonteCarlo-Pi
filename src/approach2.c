#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct {
    int thread_id;
    long long points_to_generate;
    long long local_count;
} ThreadData;

void* map_monte_carlo(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long count = 0;
    unsigned int seed = 12345 + data->thread_id; 

    for (long long i = 0; i < data->points_to_generate; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            count++;
        }
    }
    data->local_count = count;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <total_points> <num_threads>\n", argv[0]);
        return 1;
    }

    long long total_points = atoll(argv[1]);
    int num_threads = atoi(argv[2]);
    struct timeval start, end;

    // --- Phase 1: Sequential Baseline (T_single) ---
    // Count how many fall inside the circle
    long long count_baseline = 0;
    unsigned int seed_single = 12345;
    gettimeofday(&start, NULL);
    for (long long i = 0; i < total_points; i++) {
        double x = (double)rand_r(&seed_single) / RAND_MAX;
        double y = (double)rand_r(&seed_single) / RAND_MAX;
        if (x * x + y * y <= 1.0) count_baseline++;
    }
    gettimeofday(&end, NULL);
    double t_single = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // --- Phase 2: Parallel Execution (T_parallel) ---
    // Each thread maintains its own local counter
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    long long points_per_thread = total_points / num_threads;
    long long remainder = total_points % num_threads;

    gettimeofday(&start, NULL); 
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].points_to_generate = points_per_thread + (i < remainder ? 1 : 0);
        pthread_create(&threads[i], NULL, map_monte_carlo, (void*)&thread_data[i]);
    }

    long long total_inside = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_inside += thread_data[i].local_count; // Results are combined
    }
    gettimeofday(&end, NULL);
    double t_parallel = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    double pi_single = 4.0 * (double)count_baseline / total_points;
    double pi_parallel = 4.0 * (double)total_inside / total_points;
    // Academic report output
    printf("Points_Total: %lld\n", total_points);
    printf("Points_Inside_Baseline: %lld\n", count_baseline);
    printf("Points_Inside_Parallel: %lld\n", total_inside);
    printf("T_single: %f\n", t_single);
    printf("T_parallel: %f\n", t_parallel);
    printf("Speedup: %f\n", t_single / t_parallel);
    printf("Estimated_Pi_Baseline: %f\n", pi_single);   
    printf("Estimated_Pi_Parallel: %f\n", pi_parallel);
    return 0;
}