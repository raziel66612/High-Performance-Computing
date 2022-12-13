/****************************************************************
 ****
 **** This program is part of the my learning track of Petsc
 **** by Aniket R Vishwakarma aniketvishwakarma@gmail.com
 ****
 **** copyright Aniket R Vishwakarma 2022
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "petsc.h"
#include "math.h"

static char help[] = "Hello world using Petsc this is Aniket from help flag";

// PetscErrorCode this_is_a_subroutine_for_error() {
//     PetscFunctionBegin;
// SETERRQ(PETSC_COMM_SELF,1,">> FOUND ERROR!!!!!! <<");
//     PetscFunctionReturn(0);
// }

PetscErrorCode square_root(PetscReal x,PetscReal* sqrt_of_x){
    PetscFunctionBegin;
            if(x<0){
            SETERRQ(PETSC_COMM_SELF,1,">> FOUND ERROR!!!!!! cannot compute sqrt of %f <<",x);
            PetscFunctionReturn(0);
            }
        *sqrt_of_x=sqrt(x);
    PetscFunctionReturn(0);
}

int main(int argc,char** argv)
{
PetscErrorCode ierr;  /*ierr==is a variable to catch error thrown by any of the subroutine*/ 
ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);
ierr= PetscPrintf(PETSC_COMM_WORLD,"---Hello to world from PetscPrintf-- \n"); CHKERRQ(ierr);

PetscReal sqrt_of_x;
PetscReal x1=4;
ierr= square_root(x1,&sqrt_of_x); CHKERRQ(ierr);
PetscPrintf(PETSC_COMM_WORLD,"\n \n Square root of %f is %f \n \n",x1, sqrt_of_x);  CHKERRQ(ierr);

PetscReal x2=-4;
ierr= square_root(x2,&sqrt_of_x); CHKERRQ(ierr);
PetscPrintf(PETSC_COMM_WORLD,"Square root of %f is %f",x2, sqrt_of_x); CHKERRQ(ierr);

ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}
