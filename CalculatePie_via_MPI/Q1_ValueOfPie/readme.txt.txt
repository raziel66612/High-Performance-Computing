-- each of my code is written in C++
-- directory "serial_code" has the code ran in serial of verify the calculations of pie. 
-- to run the serial code use command "g++ pie.cpp -o pie"  to generate object file and then run th eobject "./pie"

-- Each folder in directory have their respective scaling cases.
-- Directory: 'strong_scaling' contains 4 test cases for calculting value of pie, calculated for no. of core: 1,8,16,32.
-- Directory:'weak_scaling_caseA' contains 3 test cases for calculting value of pie, calculated for no. of core: 8,16,32.
-- Directory: 'weak_scaling_caseB' contains 4 test cases for calculting value of pie, calculated for no. of core: 1,8,16,32. 1core case is a base case to find speedup.

-- to run the result, after writing code in ".cc" extension, we first load 2 module to run mpi using commands "module load intel/17.0" and "module load intel-mpi/2017.0.1" then generate the object file with command "mpiicpc mandelbrot.cc -o mandelbrot.mpi"
-- this would generate an object file with name pie.mpi, which is then loaded in slurm script "qpie.sh".
-- to run the slurm script use command " sbatch ./qpie.sh"
-- on succesfull job completion we will get one output file with extension ".out" (which contains the result) and another output error file with extension".err"(whihc is an error log file, if you get any error)

-- each of the directory have their own slurm script
-- each one of the ran cases have their output files with name "JOB_PI_######.out" you can view the results with command "cat ./JOB_PI_######.out" which should dispay the value of calculated pie and also we took value of pie from standard library and compared the error percentage
