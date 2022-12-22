#!/bin/bash
#SBATCH --account=hpc1
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=32
#SBATCH --time=00:20:00
#SBATCH --constraint=IB&CPU-Gold-6230
#SBATCH --job-name="Poisson_ex5_"
#SBATCH --output=Poisson_ex5_-%j.out
#SBATCH --error=Poisson_ex5_-%j.err


module load intel/17.0
module load intel-mpi/2017.0.1
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

module load petsc/v3.15.0

for i in {128,256,512,1024,2048};
do srun ./ex5 -pc_type lu -pc_factor_mat_solver_type mumps -da_grid_x $i -da_grid_y $i -log_view > grid_$i.txt;
done


echo "DONE !!!!"
