#!/bin/bash

#SBATCH --job-name=fpu
#SBATCH --partition=jetson-tx
#SBATCH --ntasks=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:30:00
#SBATCH --output=single-core-jetsontx-%j.out

source /etc/profile.d/modules.sh
module purge

module load gcc
module load papi

export FPU_uKernel_HOME=..
export FPU_uKernel_BIN=${FPU_uKernel_HOME}/bin

##########################################################
# Compile
##########################################################
cd ${FPU_uKernel_HOME}
make ISA=jetsontx clean
make ISA=jetsontx
cd -

##########################################################
# Run
##########################################################
export OMP_NUM_THREADS=1
for isa in aarch64.sp aarch64.dp neon.sp neon.dp; do
  printf "###########################################################\n"
  printf "# ISA: ${isa}\n"
  printf "###########################################################\n"
  ${FPU_uKernel_BIN}/${isa}.x -n 1000 -r 100 --detail
  printf "\n\n"
done
