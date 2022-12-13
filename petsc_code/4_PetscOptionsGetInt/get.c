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


static char help[] = "\n\n We can change the value of int stored in variable \"x\" to 200 using PetscOptionsGetInt with flag \"-n 200\" \n\n";

int main(int argc,char** argv)
{

PetscInt x=100;
PetscBool flg;

PetscErrorCode ierr;  /*ierr==is a variable to catch error thrown by any of the subroutine*/ 
ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);

ierr= PetscPrintf(PETSC_COMM_WORLD,"Original value of x is %d \n",x); CHKERRQ(ierr);
ierr= PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-x",&x,&flg); CHKERRQ(ierr);
ierr= PetscPrintf(PETSC_COMM_WORLD,"After PetscOptionsGetInt from terminal value of x is %d \n",x); CHKERRQ(ierr);

ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}
