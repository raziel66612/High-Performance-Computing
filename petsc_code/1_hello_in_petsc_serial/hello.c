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

static char help[] = "Hello world using Petsc this is Aniket from help flag";

int main(int argc,char** argv)
{

PetscErrorCode ierr;  /*ierr==is a variable to catch error thrown by any of the subroutine*/ 
ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);
ierr= PetscPrintf(PETSC_COMM_WORLD,"---Hello to world from PetscPrintf-- \n"); CHKERRQ(ierr);
ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}
