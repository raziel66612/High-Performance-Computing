#include <stdio.h>
#include "petsc.h"

static char help[] = "\n\n We can change the value of int stored in variable \"x\" to 200 using PetscOptionsGetInt with flag \"-n 200\" \n\n";

int main(int argc,char** argv)
{

PetscErrorCode ierr;


Mat U,V,V_trans;  // MAt V constains the input set of vectors, mat U is the orthogonalized vectors of V
PetscInt i,p;
PetscInt g_start,g_end;
PetscInt nrowG = 3; //No. of rows : Global
PetscInt ncolG = 3; //No. of columns : Global
PetscRandom ran;

Vec x;

ierr = PetscInitialize(&argc, &argv,NULL,help); CHKERRQ(ierr);

ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
ierr = VecSetSizes(x,PETSC_DECIDE,nrowG);CHKERRQ(ierr);
ierr = VecSetFromOptions(x); CHKERRQ(ierr);

//ierr = MatCreate(PETSC_COMM_WORLD,&V); CHKERRQ(ierr);
ierr = MatCreateSeqDense(PETSC_COMM_WORLD,nrowG,ncolG,PETSC_NULL,&V); CHKERRQ(ierr);
// ierr = MatSetSizes(V,PETSC_DECIDE,PETSC_DECIDE,nrowG,ncolG); CHKERRQ(ierr);
ierr = MatSetFromOptions(V); CHKERRQ(ierr);
ierr = MatSetUp(V); CHKERRQ(ierr);

ierr = PetscRandomCreate(PETSC_COMM_WORLD, &ran); CHKERRQ(ierr);
ierr = MatSetRandom(V,ran) ; CHKERRQ(ierr);

ierr = PetscRandomSetFromOptions(ran); CHKERRQ(ierr);
ierr = MatGetOwnershipRange(V,&g_start,&g_end); CHKERRQ(ierr);
ierr = MatAssemblyBegin(V,MAT_FINAL_ASSEMBLY);  CHKERRQ(ierr);
ierr = MatAssemblyEnd(V,MAT_FINAL_ASSEMBLY);  CHKERRQ(ierr);

ierr = MatDuplicate(V, MAT_DO_NOT_COPY_VALUES,&U) ; CHKERRQ(ierr);
ierr = MatZeroEntries(U);
// //do not need it rn // ierr = MatTranspose(V,MAT_INITIAL_MATRIX,&V_trans) ; CHKERRQ(ierr);
// //do not need it rn // ierr = MatNorm(V_trans,NORM_1,x); CHKERRQ(ierr);

/* 
//TEST: get colm vect and print 
PetscInt col=1;
ierr = MatGetColumnVector(V_trans,x,col);CHKERRQ(ierr);
ierr = PetscPrintf(PETSC_COMM_WORLD,"\n colm no. %d (vector) of mat V :\n",col); CHKERRQ(ierr);
ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD); CHKERRQ(ierr);
*/

for(i=g_start;i<g_end;i++){
PetscInt col=i;
ierr = MatGetColumnVector(V,x,col);CHKERRQ(ierr);
if(i==0){
    for(p=0;p<g_end;p++){
        MatSetValues(U,nrowG,&p,1,&i,x,INSERT_VALUES);
    }
}
}
MatAssemblyBegin(U,MAT_FINAL_ASSEMBLY);
MatAssemblyEnd(U,MAT_FINAL_ASSEMBLY);


ierr = MatDestroy(&V);CHKERRQ(ierr);
ierr = MatDestroy(&U);CHKERRQ(ierr);
ierr = VecDestroy(&x); CHKERRQ(ierr);
ierr = PetscFinalize(); CHKERRQ(ierr);
return 0;
}