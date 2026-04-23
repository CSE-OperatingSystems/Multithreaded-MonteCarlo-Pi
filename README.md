# Multi-threaded Monte Carlo $\pi$ Estimation

This project was developed by **Group Eternals** for **Lab 2: Operating Systems (CO2018)** - Semester **HK252** at **Ho Chi Minh City University of Technology (HCMUT)**[cite: 2, 4]. [cite_start]The objective is to investigate how different multi-threading strategies and synchronization mechanisms affect computational performance, scalability, and system overhead[cite: 10, 72].

## 👥 Team Members
* Huỳnh Tấn Tiến
* Huỳnh Hoàng Anh
* Phạm Minh Đức
## 📋 Project Overview
[cite_start]The project implements and compares three distinct approaches to estimate the value of $\pi$ using the Monte Carlo method[cite: 88]:

1.  [cite_start]**Approach 1 (Single Thread):** Establishes a sequential baseline for speedup calculations[cite: 96].
2.  [cite_start]**Approach 2 (Local Accumulation):** A parallel design using a Map-Reduce pattern where each thread maintains a local counter to avoid contention[cite: 97].
3.  [cite_start]**Approach 3 (Shared Variable with Mutex):** Introduces a global counter protected by a mutex/semaphore to demonstrate synchronization overhead and lock contention[cite: 98].

## 🚀 Getting Started

### Prerequisites
* [cite_start]**Operating System:** Linux (Ubuntu or WSL recommended)[cite: 112].
* [cite_start]**Compiler:** `gcc` with `-O3` optimization[cite: 113].
* **Tools:** `make`, `bc` (for mathematical calculations in scripts).

### 1. Compilation
Use the provided `Makefile` to compile all versions:
```bash
make
```
This generates two main executables: `app1` (Sequential) and `app2` (Parallel Accumulation).

### 2. Automated Testing
[cite_start]To run the automated experiment script which tests configurations from 2 to 128 threads with $10^8$ points[cite: 115]:
```bash
make test
```

### 3. Manual Execution
* **Approach 1:** `./app1 <total_points>`
* **Approach 2:** `./app2 <total_points> <num_threads>`
* **Approach 3:** Compile manually using `gcc -O3 src/approach3_mutex.c -lpthread -o app3` and run `./app3`.

## 📊 Methodology
* [cite_start]**Input Size:** Fixed at $100,000,000$ points to ensure fair comparison[cite: 103].
* [cite_start]**Iteration:** Each configuration is executed 5 times to report the average execution time[cite: 102].
* **Key Metrics:**
    * [cite_start]**Speedup:** $S = \frac{T_{single}}{T_{parallel}}$[cite: 63].
    * [cite_start]**Efficiency:** $E = \frac{S}{N}$ (where $N$ is the number of threads)[cite: 125].

## 📄 Academic Paper (Talented Class Requirement)
[cite_start]As part of the **Talented Class (KSTN)** curriculum, the group is synthesizing these findings into a short academic paper using **LaTeX** (Springer template)[cite: 11, 29]. The paper analyzes:
* [cite_start]**Non-linear Speedup:** Why performance does not scale perfectly with thread counts[cite: 137].
* [cite_start]**Saturation Point:** Identifying the threshold where adding threads no longer improves performance relative to CPU cores[cite: 138].
* [cite_start]**Synchronization Cost:** Quantifying the performance degradation in Approach 3 due to critical section serialization[cite: 140, 146].

## 📂 Directory Structure
```text
.
├── src/                    # C Source code (approach1.c, approach2.c, approach3_mutex.c, Makefile)
├── scripts/                # Experimental shell scripts (run_experiment.sh)
├── report/                 # LaTeX source files and final academic paper
└── README.md               # Project documentation
```

---
*This project is part of the undergraduate curriculum at the Faculty of Computer Science and Engineering, HCMUT.*
