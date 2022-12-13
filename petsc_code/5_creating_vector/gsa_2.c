#include <stdio.h>
#include "petsc.h"

static char help[] = "\n\n We can change the value of int stored in variable \"x\" to 200 using PetscOptionsGetInt with flag \"-n 200\" \n\n";

int main(int argc,char** argv)
{

/*
Vec x,y;
PetscInt n=3;
PetscBool flg;
PetscErrorCode ierr;  //ierr==is a variable to catch error thrown by any of the subroutine
ierr= PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);

ierr= PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-n",&n,&flg); CHKERRQ(ierr);
ierr= PetscPrintf(PETSC_COMM_WORLD,"Size of vector x,y is %d \n",n); CHKERRQ(ierr);
ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
ierr = VecSetSizes(x,PETSC_DECIDE,n);CHKERRQ(ierr);
ierr = VecSetFromOptions(x); CHKERRQ(ierr);

ierr = VecDuplicate(x,&y); CHKERRQ(ierr);
ierr = VecDestroy(&x); CHKERRQ(ierr);
ierr = VecDestroy(&y); CHKERRQ(ierr);
ierr = PetscFinalize(); CHKERRQ(ierr);
*/

Mat U,V;  // MAt V constains the input set of vectors, mat U is the orthogonalized vectors of V
//PetscInt i;
PetscInt g_start,g_end;
PetscInt nrowG = 5; //No. of rows : Global
PetscInt ncolG = 5; //No. of columns : Global
PetscRandom ran;
PetscReal normV;

PetscErrorCode ierr;

ierr = PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);

//ierr = MatCreate(PETSC_COMM_WORLD,&V); CHKERRQ(ierr);
ierr = MatCreateSeqDense(PETSC_COMM_WORLD,nrowG,ncolG,PETSC_NULL,&V); CHKERRQ(ierr);
// ierr = MatSetSizes(V,PETSC_DECIDE,PETSC_DECIDE,nrowG,ncolG); CHKERRQ(ierr);
ierr = MatSetFromOptions(V); CHKERRQ(ierr);
ierr = MatSetUp(V); CHKERRQ(ierr);

ierr = MatSetRandom(V,ran) ; CHKERRQ(ierr);
ierr = PetscRandomCreate(PETSC_COMM_WORLD, &ran); CHKERRQ(ierr);
ierr = PetscRandomSetFromOptions(ran); CHKERRQ(ierr);
ierr = MatGetOwnershipRange(V,&g_start,&g_end); CHKERRQ(ierr);
ierr = MatAssemblyBegin(V,MAT_FINAL_ASSEMBLY);  CHKERRQ(ierr);
ierr = MatAssemblyEnd(V,MAT_FINAL_ASSEMBLY);  CHKERRQ(ierr);

ierr = MatDuplicate(V, MAT_DO_NOT_COPY_VALUES,&U) ; CHKERRQ(ierr);

ierr = MatNorm(V,NORM_2,&normV); CHKERRQ(ierr);
PetscPrintf(PETSC_COMM_WORLD,"norm of mat V :",normV);

ierr = MatDestroy(&V);CHKERRQ(ierr);
ierr = MatDestroy(&U);CHKERRQ(ierr);
ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}