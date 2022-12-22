> Code is written in c
> 
> Firstly, run the make file using `make gsa` which would then generate one executable and one object file(.o)
> 
> run the executable using command `./gsa` on terminal, this would produce the result for assigned values of k(no. of vectors) and n(size of each vector) in the code.

> If you run using `./gsa -help`, this would print out help text written by author of teh code followed by default petsc help dialogue written by petsc developers.
> 
> Code contains `PetscOptionsGetInt` for both 'k' and 'n' variables, and this routine can be invoked on terminal to change the value of k and n directly from terminal using command `./gsa -k 20 -n 1000`.
> 
> To run the code on multiple processors(for eg. 8), use command `mpiexec -n 8 ./gsa` or `mpirun -np 8 ./gsa` 

> similarly, using this command we can change values of k and n to solve for Q2 and Q3, individually or 

> For Q2 use command `for i in {1000,5000,10000,50000,100000};do ./gsa -k 20 -n $i -log_view >> n_$i.txt; done`  on terminal.
> 
> This would generate 5 .txt files (which are in Q2 directory)for 5 test cases and then observe the time.
> 
> Along with this, you will also find one excel file which sumarizes the result.

> Similary for Q3 `for i in {2,4,8,16,32,64};do ./gsa -k $i -n 50000 -log_view >> k_$i.txt; done`  on terminal.
>>
>>  this would again generate 5 .txt (which are in Q3 directory) files for 5 test cases and then observe the time.
> 
> Along with this, you will also find one excel file which sumarizes the result.
