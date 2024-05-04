# CS5504-project

This project is the final project for CS5504 in Spring 2024 semester. It is the project to observe different combinations of hardware architecture with gem5 simulator.

Here is the git repository link for the project.
https://github.com/rufquf2628/CS5504-project

## Usage

To use the project, the gem5.opt of X86 architecture is needed in linux server. 

### Compilation

The project uses three workloads (matmul, lts, and nq). They are written with C language and needed to compiled with gcc compiler.

Matrix Multiply:
```bash
gcc -O0 -ggdb3 -std=c99 -static matmul.c -o matmul86
```

N-queens:
```bash
gcc -O0 -ggdb3 -std=c99 -static nq.c -o nq86
```

Lower Triangular Solve:
```bash
gcc -O0 -ggdb3 -std=c99 -static lts.c -o lts86
```

### Hardware Combination

To observe different combination of hardware, the cache.py and multi_args.py are needed to be modified.

caches.py
```python
class L2Cache(Cache):
    # Broadwell
    size = "256kB"
    assoc = 8
    tag_latency = 12
    data_latency = 12
    response_latency = 12

    # Skylake
    # size = "1024kB"
    # assoc = 16
    # tag_latency = 14
    # data_latency = 14
    # response_latency = 14

...

class L3Cache(Cache):
    # Broadwell
    size = '32768kB'
    assoc = 8
    tag_latency = 50
    data_latency = 50
    response_latency = 50

    # Skylake
    # size = '16384kB'
    # assoc = 8
    # tag_latency = 50
    # data_latency = 50
    # response_latency = 50
```
Comment one of two structures to see the difference between Broadwell and Skylake.

multi_args.py
```python
default_binary = os.path.join(
    thispath,
    "./matmul86",
    # "./nq86",
    # "./lts86",
)

...

# Create a simple CPU
system.cpu = X86TimingSimpleCPU()
# system.cpu = X86MinorCPU()
# system.cpu = X86O3CPU()

...

# Branch Prediction Policy
system.cpu.branchPred = LocalBP() # sets branch prediction to localBP
# system.cpu.branchPred = TournamentBP() # sets branch prediction to tournament
# system.cpu.branchPred = TAGE() # sets branch prediction to TAGE
```
Choose one of each workload, CPU, and Branch Prediction Policy.

### Script

Use script.sh to get result from gem5 simulator.

script.sh
```bash
#!/bin/bash

wl=lts
cpu=o3
bp=tage
cache=sky

../gem5/build/X86/gem5.opt -d ./results/$wl/$wl-$cpu-$bp-$cache multi_args.py
```
Modify the path of gem5.opt file to your server. Change each parameter (wl, cpu, bp, cache) to get stat file with correct name and path.
