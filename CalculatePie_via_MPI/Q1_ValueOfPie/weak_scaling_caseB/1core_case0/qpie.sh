#!/bin/bash
#SBATCH --account=hpc1
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:02:00
#SBATCH --constraint=IB
#SBATCH --constraint=IB&CPU-Gold-6230
#SBATCH --job-name="JOB_pie_2_"
#SBATCH --output=JOB_pi_2_-%j.out
#SBATCH --error=JOB_pi_2_-%j.err
module load intel/17.0
module load intel-mpi/2017.0.1
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so
srun ./pie.mpi
echo "DONE !!!!"
