#include <stdio.h>
#include "petsc.h"


static char help[] = "\n\n We can change the value of int stored in variable \"x\" to 200 using PetscOptionsGetInt with flag \"-n 200\" \n\n";

int main(int argc,char** argv)
{

Vec x,y;
PetscInt n=10;
PetscBool flg;

PetscErrorCode ierr;  /*ierr==is a variable to catch error thrown by any of the subroutine*/ 
ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);

ierr= PetscPrintf(PETSC_COMM_WORLD,"Original value of x is %d \n",n); CHKERRQ(ierr);
ierr= PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-n",&n,&flg); CHKERRQ(ierr);

ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
ierr = VecSetSizes(x,PETSC_DECIDE,n);CHKERRQ(ierr);
ierr = VecSetFromOptions(x); CHKERRQ(ierr);

ierr = VecDuplicate(x,&y); CHKERRQ(ierr);

PetscScalar one=1.0;
//PetscScalar two=2.0;
ierr = VecSet(x,one); CHKERRQ(ierr);

PetscInt ffirst,llast,localsize,globalsize;
ierr = VecGetSize(y,&globalsize); CHKERRQ(ierr);
ierr = VecGetLocalSize(y,&localsize); CHKERRQ(ierr);
ierr = VecGetOwnershipRange(y,&ffirst,&llast); CHKERRQ(ierr);
for (PetscInt index=ffirst;index<llast; index++){
    PetscScalar value = sin(index*2*3.142/globalsize);
    ierr = VecSetValue(y,index,value,INSERT_VALUES); CHKERRQ(ierr);
}
ierr = VecAssemblyBegin(y); CHKERRQ(ierr);
ierr = VecAssemblyEnd(y); CHKERRQ(ierr);

ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD); CHKERRQ(ierr);
ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD); CHKERRQ(ierr);
// VecView(y,NULL); // or you could also use a flag in terminal saying `-vec_view`

/*-------------PART B : Vector Product -------------*/

PetscScalar product_is;
ierr = VecDot(x,y,&product_is) ; CHKERRQ(ierr);

ierr = PetscPrintf(PETSC_COMM_WORLD,"\n Product is : %f  \n\n" ,product_is); CHKERRQ(ierr);


/*-------------PART C : Compute Norm of the vector x and y -------------*/

PetscReal normx, normy;
ierr = VecNorm(x,NORM_2,&normx); CHKERRQ(ierr);
ierr = VecNorm(y,NORM_2,&normy); CHKERRQ(ierr);

ierr = PetscPrintf(PETSC_COMM_WORLD,"\n2-Norm of vector x : %f",normx); CHKERRQ(ierr);
ierr = PetscPrintf(PETSC_COMM_WORLD,"\n2-Norm of vector x : %f",normy); CHKERRQ(ierr);

ierr = VecDestroy(&x); CHKERRQ(ierr);
ierr = VecDestroy(&y); CHKERRQ(ierr);
ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}
