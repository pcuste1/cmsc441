#!/bin/bash
#SBATCH --job-name=8-core-algo
#SBATCH --output slurm_8.out
#SBATCH --error slurm_8.err
#SBATCH --partition=batch
#SBATCH --qos=normal
#SBATCH --constraint=hpcf2013
#SBATCH --exclusive
#SBATCH --cpus-per-task=8
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"
export OMP_NUM_THREADS=8

srun ./c.out data.txt 10