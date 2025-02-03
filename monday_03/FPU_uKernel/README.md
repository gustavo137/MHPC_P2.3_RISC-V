# FPU uKernel
A small microkernel code to stress the FPU and SIMD units. It performs a set number of multiply-and-add instructions and clocks the results to measure the performance in GFlop/s.

## Supported Architectures

### FPU
* Armv8 (64-bits)
* Intel x86
* Power9
* RISC-V

### SIMD
* Arm NEON
* Arm SVE
* AVX2
* AVX512
* Power9 VSX

## How to compile
Have a look at the `makefiles` directory andccheck if there is a suitable Makefile configuration for your test. If there is not, you can just copy one of the existing ones and modify it.

You just need to type `make ISA=<isa>` to generate the binaries under the `bin` directory. The parameter `ISA` indicates which Makefile under `makefiles` will be invoked.

There are some makefiles that act as a collection for a given machine:
* MareNostrum5: `mare5`
* Jetson-TX: `jetsontx`
* Arriesgado-jammy: `arriesgado`

## How to run
Once you have compiled the binaries, you should be able to run serially:
```bash
$ ./bin/x86.dp.x
```

To run un parallel with OpenMP, you can define the `OMP_NUM_THREADS` environment variable:
```bash
$ OMP_NUM_THREADS=48 ./bin/x86.dp.x
```

I suggest to use the `OMP_PROC_BIND` environment variable and/or the `taskset` utility to control how the threads are mapped/pinned to the cores.

Use the `-h` flag for a full list of available options
```bash
$ ./bin/riscv.dp.x -h
Usage: ./bin/riscv.dp.x [<options>]
  --ntimes, -n <N> Loop <N> times
                     Default: 100
  --always, -a     Loop for ever

  --report, -r <N> Report measurements each <N> iterations
                     If <N> < 0, then report once at the very end
                     Default: -1
  --detail, -d     Report measurements for each thread

  --quiet,  -q     Do not print any output
  --noheader       Omit CSV header from output

  --help,   -h     Print this message


Recommended environment variables
  OMP_NUM_THREADS
  OMP_PLACES (eg. cores)
  OMP_PROC_BIND (eg. close, spead)


Reporting
  Time (us) measured with gettimeofday
  Cycles measured with PAPI_TOT_CYC
  Floating Point operations known at compile time
    NFPOPS = 320
    NITERS = 100000
    Total FP operations: NFPOPS*NITERS = 32000000
```

## Output
By default, the program will print out the summary of the run including the total, average, maximum, minimum, and standard deviation of the measured GFlop/s *across all threads*.

If you need more insight, you can pass an extra command line argument to toggle the detailed output, which will print out the measured GFlop/s *per thread*.
```bash
$ OMP_NUM_THREADS=48 ./bin/x86.dp.x 1
```
