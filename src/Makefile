# Compiler and Optimization Flags [cite: 112]
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lpthread

# Executables
APP1 = app1
APP2 = app2

# Default target: Compile both versions
all: $(APP1) $(APP2)

# Build Sequential Baseline
$(APP1): approach1.c
	$(CC) $(CFLAGS) approach1.c -o $(APP1)

# Build Parallel Accumulation Version [cite: 96]
$(APP2): approach2.c
	$(CC) $(CFLAGS) approach2.c -o $(APP2) $(LIBS)

# Automated testing target
test: all
	chmod +x run_experiment.sh
	./run_experiment.sh

# Clean build artifacts
clean:
	rm -f $(APP1) $(APP2)
	@echo "All executables removed."