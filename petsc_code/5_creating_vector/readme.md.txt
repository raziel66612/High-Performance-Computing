> - to create executables run command `make vec` on command line

> ## To run the code serially:
> - then run the executable using `./vec`
> - this will run the code on one processor (seriall)

> ## To run the code on parallel: 
> - after you generate your executable using `make vec`, run the command `mpiexec -n 4 ./vec` , this will invoke 4 processors and distribute and run the code on 4 cores.

> - Further to change input vector use code `./ vec -n 20` or ` mpiexec -n 4 ./vec -n 20` to create a vector of 20 entries. (check PetscOptionGetInt to understand how this entry change works)