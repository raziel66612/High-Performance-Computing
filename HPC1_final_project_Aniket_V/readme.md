# PART A 

## Question 1:
> first load petsc module using `module load petsc/v3.15.0`
> use `make ex5` to create executable for ex5.c 
> run the following command on terminal to get results for 64x64 grid 
> `./ex5 -da_grid_x 64 -da_grid_y 64 -pc_type lu -mms 3 `


> Alternatively, use command  on terminal 
> `for i in {16,32,64,128,256}; do  ./ex5 -da_grid_x $i -da_grid_y $i -pc_type lu -mms 3 > grid_$i.txt ; done` 
> this would generate 5 text files containing results for gird size-16,32,64,128,256 respectively.

## Question 2:
> first load petsc module using `module load petsc/v3.15.0`
> then, make file use `make ex13`
> then, run the following command to get results for grid 64x64 
> `./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -dm_plex_box_faces 64,64 -pc_type lu -error_view`
> this should give out result for 1 case

> Alternatively, use the command to get results for 5 cases{16,32,64,128,256} in the respective for text files.
> `for i in {16,32,64,128,256}; do  ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -dm_plex_box_faces $i,$i -pc_type lu -error_view > grid_$i.txt; done`

--------------------------------------------------------------------------------------
# PART B and C 
> for directory `partB` and `partC`, each directory have 2 directorie `ex5` & `ex13` and each of them is further divided into 
> 3 sections for 3 cases of `MUMPS`, `Block Jacobi` and `Algebraic multigrid`.

> first make the file using `make ex5` or `make ex13` which would generate executable and then slurm script was created with name `qPoisson.sh`
> as required 64 core were requested, and simulation was run for multiple run by varying grid  size, and each sub-directorises have `excel sheet` with plotted results.

codes used for following cases in slurm script are:

## Part B

### Part B: ex5: 1_MUMPS :
```
for i in {256,512,1024,2048};
do srun ./ex5 -pc_type lu -pc_factor_mat_solver_type mumps -da_grid_x $i -da_grid_y $i -log_view > grid_$i.txt;
done
```

### Part B: ex5: 2_Block_jacobi  :
```
for i in {256,512,1024,2048};
do srun ./ex5 -da_grid_x $i -da_grid_y $i -log_view > grid_$i.txt;
done
```

### Part B: ex5: 3_Algebraic_multigrid :
```
for i in {256,512,1024,2048};
do srun ./ex5 -pc_type gamg -da_grid_x $i -da_grid_y $i -log_view > grid_$i.txt;
done
```

### Part B: ex13: 1_MUMPS :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -pc_type lu -pc_factor_mat_solver_type mumps -dm_plex_box_faces $i,$i -dm_distribute -log_view > grid_$i.txt;
done
```

### Part B: ex13: 2_Block_jacobi   :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -dm_plex_box_faces $i,$i -dm_distribute -log_view > grid_$i.txt;
done
```

### Part B: ex13: 3_Algebraic_multigrid :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -pc_type gamg -dm_plex_box_faces $i,$i -dm_distribute -log_view > grid_$i.txt;
done
```

--------------------------------------------------------------------------------------
after successfully creating slurm script, submit the jobs on ccr using `sbatch qPoisson.sh`

each run would generate files 5 text files with respect to the changing grid size for the fixed no. of cores.i.e 64.

then for part B use the follwing command on terminal to view runtime
 `awk 'NR==11{print $0}' grid_256.txt `  

in similar manner you can view all the results 
--------------------------------------------------------------------------------------


## Part C 

### Part C: ex5: 1_MUMPS :
```
for i in {256,512,1024,2048};
do srun ./ex5 -pc_type lu -pc_factor_mat_solver_type mumps -da_grid_x $i -da_grid_y $i -mms 3 -log_view > grid_$i.txt;
done
```

### Part C: ex5: 2_Block_jacobi  :
```
for i in {256,512,1024,2048};
do srun ./ex5 -da_grid_x $i -da_grid_y $i -mms 3 -log_view > grid_$i.txt;
done
```

### Part C: ex5: 3_Algebraic_multigrid :
```
for i in {256,512,1024,2048};
do srun ./ex5 -pc_type gamg -da_grid_x $i -da_grid_y $i -mms 3 -log_view > grid_$i.txt;
done
```

### Part C: ex13: 1_MUMPS :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -pc_type lu -pc_factor_mat_solver_type mumps -dm_plex_box_faces $i,$i -dm_distribute -log_view -error_view > grid_$i.txt;
done
```

### Part C: ex13: 2_Block_jacobi   :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -dm_plex_box_faces $i,$i -dm_distribute -log_view -error_view > grid_$i.txt;
done
```

### Part C: ex13: 3_Algebraic_multigrid :
```
for i in {128,256,512,1024,2048};
do srun ./ex13 -dm_plex_simplex 0 -potential_petscspace_degree 1 -pc_type gamg -dm_plex_box_faces $i,$i -dm_distribute -log_view -error_view > grid_$i.txt;
done
``` 

--------------------------------------------------------------------------------------
> after successfully creating slurm script, submit the jobs on ccr using `sbatch qPoisson.sh`
>
> each run would generate files 5 text files with respect to the changing grid size for the fixed no. of cores.i.e 64.
>
>  then for part C use the following command on terminal to view error log and runtime , 
>  
>  `awk 'NR==1{print $0} NR==12 {print $0}' grid_256.txt `  
>
> in similar manner you can view all the results 
--------------------------------------------------------------------------------------
