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
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -dm_plex_box_faces $i,$i -dm_distribute -log_view -error_view > grid_$i.txt;
done


echo "DONE !!!!"
