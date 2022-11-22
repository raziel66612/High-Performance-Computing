#include<fstream>
#include<iostream>
#include <mpi.h>
using namespace std;

int mandelbrot(double cr,double ci)
{
    int limit=10000;
    double zr=0.0 ,zi=0.0;
    for (int i=0; i<limit; ++i){
        if (zr*zr + zi*zi > 4.0)return i;
        double temp_zr = cr + zr*zr - zi*zi;
        zi = ci + 2.0*zr*zi;
        zr = temp_zr;
     
/*above equations comes from: 
(a+bi)^2 = a^2 + (b*i)^2 + 2*a*b*i 
where,
real part = a^2 - b^2;
imaginary part = 2*a*b*i;
*/
    }
    return limit;
}


int main(int argc,char *argv[])
{
double xmin,xmax,ymin,ymax,dx,dy;
int Nx,Ny;
//Nx=1000;  //total number of y nodes
//Ny=800;  //total number of x nodes
xmin=-2.0; //limit on negative x axis(real axis)
xmax=2.0;  //limit on positive x axis(real axis)
ymin=-1.0;  //limit on negative y axis(img axis)
ymax=+1.0;  //limit on positive y axis(img axis)

//MPI_STATUS status;
int rank,size;


MPI::Init(argc,argv);
rank=MPI::COMM_WORLD.Get_rank();
size=MPI::COMM_WORLD.Get_size();

Nx=1000;
Ny=800;
//cout<< Nx << "  " << Ny <<endl << "--------------------"<<endl;   //testing
dx=((xmax-xmin)/(Nx));   //step size in x direction 
dy=((ymax-ymin)/(Ny));   //step size in x direction

MPI::COMM_WORLD.Bcast(&Nx,1,MPI::INT,0);
MPI::COMM_WORLD.Bcast(&Ny,1,MPI::INT,0);

int count1 = 0;     //count for rank==1
int count2 = 0;     //count for rank==2
int value1[Nx][Ny];
int value2[Nx][Ny];
int dim=(Nx)*Ny;
int r;
int g;
int b;

if(rank==1){
double start1=MPI::Wtime();    // timing this processor
ofstream fout("mandelbrot_set_grid_1000x800_rank_rank_1.ppm");    //using ppm for plotting, 
fout << "P3" << endl;   // "magic number" for defining ppm.
fout << Nx/2 << " " << Ny << endl;  
fout << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cx < 0){
		 value1[i][j] = mandelbrot(cx,cy);
        	if (value1[i][j]>9999){
		++count1;}

        r=(((value1[i][j])*1)%256);
        g=(((value1[i][j])*2)%256);
        b=(((value1[i][j])*3)%256);
        fout<< r << " " << g << " " << b << " ";
        }
}
fout << endl ;
}
fout.close();
cout << "From Rank : " << rank << "      count1 : "<< count1 << endl;
double end1=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end1-start1) <<" seconds" << endl  << endl;
int tag=1;
MPI_Send(&count1,1,MPI_INT,0,tag,MPI_COMM_WORLD);
tag=3;
MPI_Send(&value1,dim,MPI_INT,0,tag,MPI_COMM_WORLD);
}

else if(rank==2){
double start2=MPI::Wtime();    // timing this processor
ofstream fout2("mandelbrot_set_grid_1000x800_rank_rank_2.ppm");    //using ppm for plotting, 
fout2 << "P3" << endl;   // "magic number" for defining ppm.
fout2 << Nx/2 << " " << Ny << endl;  
fout2 << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cx >= 0){
		 value2[i][j] = mandelbrot(cx,cy);
        	if (value2[i][j]>9999){
		++count2;}
        r=(((value2[i][j])*1)%256);
        g=(((value2[i][j])*2)%256);
        b=(((value2[i][j])*3)%256);
        fout2<< r << " " << g << " " << b << " ";
		}
}
fout2 << endl;
}
fout2.close();
cout << "From Rank : " << rank << "      count1 : "<< count2 << endl;
double end2=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end2-start2) <<" seconds"  << endl  << endl;


int tag=2;
MPI_Send(&count2,1,MPI_INT,0,tag,MPI_COMM_WORLD);
tag=4;
MPI_Send(&value2,dim,MPI_INT,0,tag,MPI_COMM_WORLD);
}

else if(rank==0){
int tag=1;
MPI_Recv(&count1,1,MPI_INT,1,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
tag=2;
MPI_Recv(&count2,1,MPI_INT,2,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

dim=Nx*Ny;
tag=3;
MPI_Recv(&value1,dim,MPI_INT,1,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

dim=Nx*Ny;
tag=4;
MPI_Recv(&value2,dim,MPI_INT,2,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
ofstream fout3("mandelbrot_set_grid_1000x800_rank_rank_0.ppm");    //using ppm for plotting, 
fout3 << "P3" << endl;   // "magic number" for defining ppm.
fout3 << Nx << " " << Ny << endl;  
fout3 << "256" << endl; //pixel's max RGB value

for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        if(j<Nx/2){
        r=(((value1[i][j])*1)%256);
        g=(((value1[i][j])*2)%256);
        b=(((value1[i][j])*3)%256);
        fout3<< r << " " << g << " " << b << " ";
		}
        else{
        r=(((value2[i][j])*1)%256);
        g=(((value2[i][j])*2)%256);
        b=(((value2[i][j])*3)%256);
        fout3<< r << " " << g << " " << b << " ";
        }
    }
fout3<<endl;
}
fout3.close();


cout<< endl <<"From Rank : " << rank <<endl;
double fraction = (double) (count1+count2)/(Nx*Ny);
double area = (fraction*(xmax-xmin))*(ymax-ymin);
cout<< "Num of process : "<< size <<endl <<endl;
cout<< "fraction of mandelbrot Set is " << fraction <<endl;
cout<< "Area of Mandelbrot is " << area<<endl;

/* creating output files with required output*/
//ofstream myfile("result_grid_1000x800.txt");
cout << "Range in x-axis (Real axis): xmin = " << xmin << " ; xmax = "<< xmax <<endl;
cout << "Range in y-axis (img axis) : ymin = " << ymin << " ; ymax = "<< ymax <<endl;
cout << "Length in x-axis : " << xmax-xmin <<endl;
cout << "Length in y-axis (img axis) : " << ymax-ymin <<endl;
cout << "Number of grid points in x:" << Nx <<endl;
cout << "Number of grid points in y:" << Ny <<endl ;
cout << "Area of mandlebrot is: " << area <<endl; 
}
//myfile.close();

MPI::Finalize();
return 0;
}
