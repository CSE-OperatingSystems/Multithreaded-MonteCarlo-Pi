#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <total_points>\n", argv[0]);
        return 1;
    }

    long long total_points = atoll(argv[1]);
    long long count_inside = 0;
    
    // REQUIREMENT: Set a fixed random seed for easy debugging
    unsigned int seed = 12345; 

    struct timeval start, end;
    
    // Start measuring computation time
    gettimeofday(&start, NULL); 

    for (long long i = 0; i < total_points; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        
        // Count how many fall inside the circle
        if (x * x + y * y <= 1.0) {
            count_inside++;
        }
    }

    // Stop measuring computation time
    gettimeofday(&end, NULL);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    double pi_estimate = 4.0 * count_inside / total_points;

    // Academic report output matching the script's parsing requirements
    printf("=== APPROACH 1: SINGLE THREAD ===\n");
    printf("Points_Total: %lld\n", total_points);
    printf("Points_Inside_Baseline: %lld\n", count_inside);
    printf("Estimated Pi: %f\n", pi_estimate);
    printf("Execution Time: %f seconds\n", time_spent);

    return 0;
}