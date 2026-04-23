#!/bin/bash

# Force standard numeric forma
export LC_NUMERIC=C

# Configuration
POINTS=100000000 
RUNS=5           
THREADS=(2 4 8 16 32 64 128) # Đã bỏ thread 1

# Chạy thử lần đầu để lấy thông tin Baseline (luôn dùng 1 thread làm gốc)
initial_output=$(./app2 $POINTS 1)
t_single_header=$(echo "$initial_output" | grep "T_single" | awk '{print $2}')
inside_header=$(echo "$initial_output" | grep "Points_Inside_Baseline" | awk '{print $2}')

# Tự tính Pi Baseline từ kết quả Points_Inside đơn nhân
pi_baseline=$(echo "scale=10; 4 * $inside_header / $POINTS" | bc -l)

echo "======================================================================="
echo " PERFORMANCE & CORRECTNESS REPORT"
echo "======================================================================="
echo "Total Samples:   $POINTS"
echo "Points Inside:   $inside_header"
echo "Pi (Baseline):   $pi_baseline"
echo "Avg T_single:    $t_single_header s"
echo "Runs per Config: $RUNS" 
echo "-----------------------------------------------------------------------"
echo "Threads | Avg Pi (Calc)     | Avg T_parallel (s) | Avg Speedup"
echo "-----------------------------------------------------------------------"

for t in "${THREADS[@]}"; do
    total_t_p=0
    total_speedup=0
    total_inside=0
    
    for ((i=1; i<=RUNS; i++)); do
        output=$(./app2 $POINTS $t)
        
        t_p_val=$(echo "$output" | grep "T_parallel" | awk '{print $2}')
        speed_val=$(echo "$output" | grep "Speedup" | awk '{print $2}')
        # Lấy số điểm bên trong từ kết quả Parallel để tính Pi
        inside_p_val=$(echo "$output" | grep "Points_Inside_Parallel" | awk '{print $2}')
        
        total_t_p=$(echo "$total_t_p + $t_p_val" | bc -l)
        total_speedup=$(echo "$total_speedup + $speed_val" | bc -l)
        total_inside=$(echo "$total_inside + $inside_p_val" | bc -l)
    done
    
    avg_t_p=$(echo "$total_t_p / $RUNS" | bc -l)
    avg_speedup=$(echo "$total_speedup / $RUNS" | bc -l)
    
    # Tính Pi trung bình từ tổng số điểm bên trong
    avg_inside=$(echo "$total_inside / $RUNS" | bc -l)
    avg_pi=$(echo "scale=10; 4 * $avg_inside / $POINTS" | bc -l)
    
    # In kết quả theo hàng
    printf "%-7d | %-17.6f | %-18.4f | %-11.4f\n" $t $avg_pi $avg_t_p $avg_speedup
done
echo "-----------------------------------------------------------------------"