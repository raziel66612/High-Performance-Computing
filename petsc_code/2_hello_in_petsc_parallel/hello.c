/****************************************************************
 ****
 **** This program is part of the my learning track of Petsc
 **** by Aniket R Vishwakarma aniketvishwakarma@gmail.com
 ****
 **** copyright Aniket R Vishwakarma 2022
 ****
 ****************************************************************/

#include <stdio.h>
#include "petsc.h"

static char help[] = "Hello world using Parallel Petsc this is Aniket V from help flag";
int main(int argc,char** argv)
{

int rank,size; 
PetscErrorCode ierr;
//ierr==is a variable to catch error thron by any of the subroutine 
//rank == processor, 
//size== number of processors

ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);
MPI_Comm_rank(PETSC_COMM_WORLD,&rank);
MPI_Comm_size(PETSC_COMM_WORLD,&size);

printf("Hello to world from rank %d out of family of %d processors \n \n",rank,size);
/* Above printf statement will be read and printed by all the other invoked processors */

ierr= PetscPrintf(PETSC_COMM_WORLD,"---Hello to world from rank %d-- \n \n",rank); CHKERRQ(ierr);
/* We can observe the differnce if use invoke PetscPrintf then only one processor will print the statement and 
which thereby eliminate the printing of the same statment over and over by all the other processors*/
ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}
