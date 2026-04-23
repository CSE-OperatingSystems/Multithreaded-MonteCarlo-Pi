# Multi-threaded Monte Carlo $\pi$ Estimation

This project was developed by **Group Eternals** for **Lab 2: Operating Systems (CO2018)** - Semester **HK252** at **Ho Chi Minh City University of Technology (HCMUT)**. The objective is to investigate how different multi-threading strategies and synchronization mechanisms affect computational performance, scalability, and system overhead.

## 👥 Team Members
* Huỳnh Tấn Tiến
* Huỳnh Hoàng Anh
* Phạm Minh Đức
## 📋 Project Overview
The project implements and compares three distinct approaches to estimate the value of $\pi$ using the Monte Carlo method:

1.  **Approach 1 (Single Thread):** Establishes a sequential baseline for speedup calculations.
2.  **Approach 2 (Local Accumulation):** A parallel design using a Map-Reduce pattern where each thread maintains a local counter to avoid contention.
3.  **Approach 3 (Shared Variable with Mutex):** Introduces a global counter protected by a mutex/semaphore to demonstrate synchronization overhead and lock contention.

## 🚀 Getting Started

### Prerequisites
* **Operating System:** Linux (Ubuntu or WSL recommended).
* **Compiler:** `gcc` with `-O3` optimization.
* **Tools:** `make`, `bc` (for mathematical calculations in scripts).

### 1. Compilation
Use the provided `Makefile` to compile all versions:
```bash
make
```
This generates two main executables: `app1` (Sequential) and `app2` (Parallel Accumulation).

### 2. Automated Testing
To run the automated experiment script which tests configurations from 2 to 128 threads with $10^8$ points:
```bash
make test
```

### 3. Manual Execution
* **Approach 1:** `./app1 <total_points>`
* **Approach 2:** `./app2 <total_points> <num_threads>`
* **Approach 3:** Compile manually using `gcc -O3 src/approach3_mutex.c -lpthread -o app3` and run `./app3`.

## 📊 Methodology
* **Input Size:** Fixed at $100,000,000$ points to ensure fair comparison.
* **Iteration:** Each configuration is executed 5 times to report the average execution time.
* **Key Metrics:**
    * **Speedup:** $S = \frac{T_{single}}{T_{parallel}}$.
    * **Efficiency:** $E = \frac{S}{N}$ (where $N$ is the number of threads).

## 📄 Academic Paper (Talented Class Requirement)
As part of the **Talented Class (KSTN)** curriculum, the group is synthesizing these findings into a short academic paper using **LaTeX** (Springer template). The paper analyzes:
* **Non-linear Speedup:** Why performance does not scale perfectly with thread counts.
* **Saturation Point:** Identifying the threshold where adding threads no longer improves performance relative to CPU cores.
* **Synchronization Cost:** Quantifying the performance degradation in Approach 3 due to critical section serialization.

## 📂 Directory Structure
```text
.
├── src/                    # Implementation of Monte Carlo strategies
│   ├── approach1.c         # Sequential baseline (Single-threaded) [cite: 96]
│   ├── approach2.c         # Parallel version using local accumulation [cite: 97]
│   ├── approach3_mutex.c   # Parallel version with shared variable and mutex [cite: 98]
│   └── Makefile            # Build system for automating compilation [cite: 112]
├── scripts/                # Automation and data collection
│   └── run_experiment.sh   # Bash script for benchmarking across thread counts [cite: 102]
├── report/                 # Academic documentation [cite: 11]
│   ├── main.tex            # LaTeX source file for the academic paper [cite: 212]
│   ├── references.bib      # Bibliography file for citations [cite: 168]
│   └── figures/            # Performance charts and speedup graphs [cite: 128]
├── data/                   # Experimental results
│   └── time_results.csv    # Raw timing data and speedup calculations
└── README.md               # Project overview and execution guide
```

---
*This project is part of the undergraduate curriculum at the Faculty of Computer Science and Engineering, HCMUT.*
