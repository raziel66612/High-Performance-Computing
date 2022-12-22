
#include "petsc.h"

static char help[] = "\n\n This code take k vectors of size N and check their orthogonality by gram schmidt algorithm \n\n";


int main(int argc,char **args)
{
PetscInt k=64,n=100000;
PetscInt i,j; // number of vectors
PetscBool flg;
PetscRandom rann;
PetscReal dot_prod,normV;
Vec y[k];
PetscLogEvent evnt;

PetscInitialize(&argc,&args,NULL,help);

PetscCall( PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-k",&k,&flg) );
PetscCall( PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-n",&n,&flg) );

//creating random values for vector
PetscCall( PetscRandomCreate(PETSC_COMM_WORLD,&rann) );
PetscCall( PetscRandomSetFromOptions(rann)  );

PetscCall( VecCreate(PETSC_COMM_WORLD,&y[0]) );
PetscCall( VecSetSizes(y[0],PETSC_DETERMINE,n) );
PetscCall( VecSetFromOptions(y[0])  );

// create k number of vectors
for (i=1; i<k; ++i) {
PetscCall( VecDuplicate(y[0], &y[i])  );
}

for (i = 0; i < k; ++i) {
PetscCall( VecSetRandom(y[i], rann) );
}
PetscCall( PetscRandomDestroy(&rann) );

// ------------------log ---------------------
PetscCall( PetscLogEventRegister("Gram_Schmidt_orthogonalization",0,&evnt) ); // log evnt
PetscCall( PetscLogEventBegin(evnt,0,0,0,0) );
//--------------------- orthogonalize the vectors ----------------------
for (i=0; i<k; i++) {
    for (j=0; j<i; j++) {
        PetscCall( VecDot(y[i],y[j],&dot_prod) );
        PetscCall( VecAXPY(y[i],-dot_prod,y[j])  );
    }
    PetscCall( VecNorm(y[i],NORM_2,&normV) );
    PetscCall( VecScale(y[i],1.0/normV) );
}
PetscCall( PetscLogEventEnd(evnt,0,0,0,0) );

// -------print dot product of vect on terminal to verify orthogonality ----------------
for (i=0; i<k; i++) {
    for (j=0; j<k; j++) {
        PetscScalar dot;
        PetscCall( VecDot(y[i],y[j],&dot) );
        if(PetscAbsScalar(dot)< 0.00001) dot=0.0;
        PetscCall( PetscPrintf(PETSC_COMM_WORLD,"%.1g  ",dot) );
        }
    PetscCall( PetscPrintf(PETSC_COMM_WORLD, "\n") );
}
   
for (i=0; i<k; i++) {
PetscCall( VecDestroy(&y[i]) );
}
PetscCall( PetscFinalize() );
return 0;
}