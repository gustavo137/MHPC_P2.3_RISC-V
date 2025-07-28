#!/bin/bash

#SBATCH --job-name=fpu
#SBATCH --partition=pioneer
#SBATCH --ntasks=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:15:00
#SBATCH --output=single-core-pioneer-%j.out

source /etc/profile.d/modules.sh
module purge

#module load gcc # Using system-wide gcc
module load papi

export FPU_uKernel_HOME=..
export FPU_uKernel_BIN=${FPU_uKernel_HOME}/bin

##########################################################
# Compile
##########################################################
cd ${FPU_uKernel_HOME}
make ISA=arriesgado clean
make ISA=arriesgado
cd -

##########################################################
# Run
##########################################################
export OMP_NUM_THREADS=1
for isa in riscv.sp riscv.dp; do
  printf "###########################################################\n"
  printf "# ISA: ${isa}\n"
  printf "###########################################################\n"
  ${FPU_uKernel_BIN}/${isa}.x -n 1000 -r 100 --detail
  printf "\n\n"
done
