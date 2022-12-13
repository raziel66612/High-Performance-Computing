#include <petsc.h>

int main(int argc, char **argv)
{
  Vec         v, w;
  PetscRandom r;
  PetscReal   dot, nrm;
  PetscInt    N;

  PetscCall(PetscInitialize(&argc, &argv, NULL, NULL));
  PetscCall(VecCreate(PETSC_COMM_WORLD, &v));
  PetscCall(PetscObjectSetOptionsPrefix((PetscObject)v, "v_"));
  PetscCall(VecSetFromOptions(v));
  PetscCall(VecSetSizes(v, PETSC_DETERMINE, 10));
  PetscCall(VecGetSize(v, &N));
  PetscCall(PetscRandomCreate(PETSC_COMM_WORLD, &r));
  PetscCall(VecSetRandom(v, r));
  PetscCall(VecNorm(v, NORM_2, &nrm));
  PetscCall(VecScale(v, 1./nrm));
  PetscCall(VecViewFromOptions(v, NULL, "-vec_view"));
  PetscCall(VecDuplicate(v, &w));
  PetscCall(PetscObjectSetOptionsPrefix((PetscObject)w, "w_"));
  PetscCall(VecSetRandom(w, r));
  PetscCall(VecNorm(w, NORM_2, &nrm));
  PetscCall(VecScale(w, 1./nrm));
  PetscCall(VecViewFromOptions(w, NULL, "-vec_view"));

  PetscCall(VecDot(v, w, &dot));
  PetscCall(PetscPrintf(PETSC_COMM_WORLD, "v . w: %g\n", (double)dot));

  PetscCall(VecDestroy(&v));
  PetscCall(VecDestroy(&w));
  PetscCall(PetscRandomDestroy(&r));
  PetscCall(PetscFinalize());
  return 0;
}