#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mpi.h>
#include<time.h>

using namespace std;

double fx(double x)  //defining arctan function
{
    double ans=4.0/(1.0+x*x);    
    return ans;
}

int main(int argc,char* argv[])
{
clock_t stime = clock();

// Declaring and initializing variables:
double xmin=0 ;  // min coordinate in abscisa
double xmax=1 ; //max coordindate in abscisa
long long int Nx=1000000;  //number of grid points in x
double dx = (xmax-xmin)/Nx ;     //step-size i.e. grid length i.e. distance between two nodes on abscisa,
double x[Nx], y[Nx];       // Creating empty arrays
int rank,size;  // variables for MPI
double sum,integral,final_pi,timeP;

MPI::Init(argc,argv); //initialising MPI Lib
size = MPI::COMM_WORLD.Get_size();
rank = MPI::COMM_WORLD.Get_rank();

double start=MPI::Wtime();
MPI::COMM_WORLD.Bcast(&Nx,1,MPI::INT,0);
MPI::COMM_WORLD.Bcast(&dx,1,MPI::DOUBLE,0);

if(Nx==0){
cout<<"Enter a valid internal Nx"<< endl;
}
else{
sum=0.0;


for(int i=rank+1 ; i<=Nx ; i+=size){
x[i]=xmin + ((double)i)*dx ;   // marching in x grid points from x=0 to x=1
sum+=fx(x[i]);
}
integral=dx*sum;
MPI::COMM_WORLD.Reduce(&integral,&final_pi,1,MPI::DOUBLE,MPI::SUM,0);
double end=MPI::Wtime();

timeP= end-start;
if(rank==0){
cout<< "--------------------------------------------------------"<<endl;
cout<< "Number of processors : " << size << "            Nx : "<< Nx <<endl;
cout<<"STD_Pi : "<< M_PI <<endl;
cout<< "Num_Pi : "<< final_pi << endl;
//cout<< "TIME_PARALLEL : " << timeP << " secs " <<  endl;
cout << "Error : " << (M_PI - final_pi)*100 << " %"<< endl;
}
}
MPI::Finalize();
clock_t time_lapsed = clock() - stime;
if(rank==0){
cout.precision(9);
//cout<< "Total time : " <<((double)time_lapsed)/CLOCKS_PER_SEC << " seconds"<<endl; 
printf("Total Time : %f seconds. \n",((double)time_lapsed)/CLOCKS_PER_SEC);
cout<< "Parallel Time : " << timeP <<endl;
cout<< "Serial time :  "  << (((double)time_lapsed)/CLOCKS_PER_SEC) - timeP <<endl;
cout<< "--------------------------------------------------------" <<endl;
}
return 0;
}

