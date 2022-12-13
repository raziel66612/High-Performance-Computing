> This is a basic HELLO WORLD code writte in c using petsc library, in parallel, also with a written help flag which could be invokde using `-help` on terminal

> To run petsc code first create `makefile` as provided

> then use command `export PATH=$PATH:/petsc/arch-linux-cxx-debug/bin` to load the directory for petsc library.

> to create object file use command `make hello` on **terminal** and then it should generate two files 
>> 1. `hello` which is your executable file
>> 2. `hello.o` which is your object file

> To run the executable in parallel use command `mpiexec -n 4 ./hello` on terminal, which should display multiple text on terminal

> Alternatively, you can also run using command `mpiexec -n 4 ./hello -help` ,where, `-help` flag would invoke help text from the code, which would give a complete description of the code written by the author of code and followed by 'default developer text'.
