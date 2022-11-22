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

MPI::COMM_WORLD.Bcast(&dx,1,MPI::INT,0);
MPI::COMM_WORLD.Bcast(&dy,1,MPI::INT,0);

//defining variable count for calculating area
int count1 = 0;      // variable for rank==1
int count2 = 0;      // variable for rank==2
int count3 = 0;      // variable for rank==3
int count4 = 0;      // variable for rank==4
int value1[Nx][Ny];
int value2[Nx][Ny];
int value3[Nx][Ny];
int value4[Nx][Ny];
int dim=Nx*Ny;
int r;
int g;
int b;

if(rank==1){
double start1=MPI::Wtime();    // timing this processor
ofstream fout1("mandelbrot_set_grid_1000x800_rank_rank_1.ppm");    //using ppm for plotting, 
fout1 << "P3" << endl;   // "magic number" for defining ppm.
fout1 << Nx << " " << Ny/4 << endl;  
fout1 << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cy > 0.5 && cy<=1.0 ){
		 value1[i][j] = mandelbrot(cx,cy);
        	if (value1[i][j]>9999){
		++count1;}
        r=(((value1[i][j])*1)%256);
        g=(((value1[i][j])*2)%256);
        b=(((value1[i][j])*3)%256);
        fout1<< r << " " << g << " " << b << " ";
		}
}
fout1 << endl;
}
fout1.close();
cout << "From Rank : " << rank << "      count1 : "<< count1 << endl;
double end1=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end1-start1) <<" seconds" << endl  << endl;
int tag1=1;
MPI_Send(&count1,1,MPI_INT,0,tag1,MPI_COMM_WORLD);

int tag5=5;
MPI_Send(&value1,dim,MPI_INT,0,tag5,MPI_COMM_WORLD);
}


else if(rank==2){
double start2=MPI::Wtime();    // timing this processor
ofstream fout2("mandelbrot_set_grid_1000x800_rank_rank_2.ppm");    //using ppm for plotting, 
fout2 << "P3" << endl;   // "magic number" for defining ppm.
fout2 << Nx << " " << Ny/4 << endl;  
fout2 << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cy > 0 && cy<=0.5){
		 value2[i][j] = mandelbrot(cx,cy);
        	if (value2[i][j]>9999){
		++count2;}
        r=(((value2[i][j])*1)%256);
        g=(((value2[i][j])*2)%256);
        b=(((value2[i][j])*3)%256);
        fout2<< r << " " << g << " " << b << " ";
		}
}
fout2 << endl ;
}
fout2.close();
cout << "From Rank : " << rank << "      count2 : " << count2 << endl;
double end2=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end2-start2) <<" seconds" << endl  << endl;


int tag2=2;
MPI_Send(&count2,1,MPI_INT,0,tag2,MPI_COMM_WORLD);

int tag6=6;
MPI_Send(&value2,dim,MPI_INT,0,tag6,MPI_COMM_WORLD);
}

else if(rank==3){
double start3=MPI::Wtime();    // timing this processor
ofstream fout3("mandelbrot_set_grid_1000x800_rank_rank_3.ppm");    //using ppm for plotting, 
fout3 << "P3" << endl;   // "magic number" for defining ppm.
fout3 << Nx << " " << Ny/4 << endl;  
fout3 << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cy > -0.5 && cy<=0){
		 value3[i][j] = mandelbrot(cx,cy);
        	if (value3[i][j]>9999){
		++count3;}
        r=(((value3[i][j])*1)%256);
        g=(((value3[i][j])*2)%256);
        b=(((value3[i][j])*3)%256);
        fout3<< r << " " << g << " " << b << " ";
		}
}
fout3 << endl ;
}
fout3.close();
cout << "From Rank : " << rank << "      count2 : " << count3 << endl;
double end3=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end3-start3) <<" seconds" << endl  << endl;
int tag3=3;
MPI_Send(&count3,1,MPI_INT,0,tag3,MPI_COMM_WORLD);

int tag7=7;
MPI_Send(&value3,dim,MPI_INT,0,tag7,MPI_COMM_WORLD);
}

else if(rank==4){
double start4=MPI::Wtime();    // timing this processor
ofstream fout4("mandelbrot_set_grid_1000x800_rank_rank_4.ppm");    //using ppm for plotting, 
fout4 << "P3" << endl;   // "magic number" for defining ppm.
fout4 << Nx << " " << Ny/4 << endl;  
fout4 << "256" << endl; //pixel's max RGB value
for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;
	if(cy >= -1.0 && cy<=-0.5){
		 value4[i][j] = mandelbrot(cx,cy);
        	if (value4[i][j]>9999){
		++count4;}
        r=(((value4[i][j])*1)%256);
        g=(((value4[i][j])*2)%256);
        b=(((value4[i][j])*3)%256);
        fout4<< r << " " << g << " " << b << " ";
		}
}
fout4 << endl ;
}
fout4.close();
cout << "From Rank : " << rank << "      count2 : " << count4 << endl;
double end4=MPI::Wtime();
cout << "From Rank : " << rank << "      Time Taken for calculation : "<< (end4-start4) <<" seconds" << endl  << endl;

int tag4=4;
MPI_Send(&count4,1,MPI_INT,0,tag4,MPI_COMM_WORLD);

int tag8=8;
MPI_Send(&value4,dim,MPI_INT,0,tag8,MPI_COMM_WORLD);
}

else if(rank==0)
{
int tag1=1;
int source=1;
MPI_Recv(&count1,1,MPI_INT,source,tag1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
cout<<"From rank : " <<  rank <<" ::   Count1 received from rank : " << source <<endl; 
int tag2=2;
source=2;
MPI_Recv(&count2,1,MPI_INT,source,tag2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
cout<<"From rank : " <<  rank <<" ::   Count2 received from rank : " << source <<endl; 
int tag3=3;
source=3;
MPI_Recv(&count3,1,MPI_INT,source,tag3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
cout<<"From rank : " <<  rank <<" ::  Count3 received from rank : " << source <<endl; 
int tag4=4;
source=4;
MPI_Recv(&count4,1,MPI_INT,source,tag4,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
cout<<"From rank : " <<  rank <<" ::   Count4 received from rank : " << source <<endl; 

/* Receiving rgb values from individual processors to stitch together a final plot */

int dim=Nx*Ny;
int tag5=5;
MPI_Recv(&value1,dim,MPI_INT,1,tag5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

dim=Nx*Ny;
int tag6=6;
MPI_Recv(&value2,dim,MPI_INT,2,tag6,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

dim=Nx*Ny;
int tag7=7;
MPI_Recv(&value3,dim,MPI_INT,3,tag7,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

dim=Nx*Ny;
int tag8=8;
MPI_Recv(&value4,dim,MPI_INT,4,tag8,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

/* plotting final Plot by splitting value1, value1,value1 ,value1 into rgb */

ofstream fout5("mandelbrot_set_grid_1000x800_rank_rank_0.ppm");    //using ppm for plotting, 
fout5 << "P3" << endl;   // "magic number" for defining ppm.
fout5 << Nx << " " << Ny << endl;  
fout5 << "256" << endl; //pixel's max RGB value

for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        if(i<=Ny/4){
        r=(((value1[i][j])*1)%256);
        g=(((value1[i][j])*2)%256);
        b=(((value1[i][j])*3)%256);
        fout5<< r << " " << g << " " << b << " ";
		}
        else if(Ny/2 > i >= Ny/4 ){
        r=(((value2[i][j])*1)%256);
        g=(((value2[i][j])*2)%256);
        b=(((value2[i][j])*3)%256);
        fout5<< r << " " << g << " " << b << " ";
        }
        else if(3*Ny/4 > i >= Ny/2){
        r=(((value3[i][j])*1)%256);
        g=(((value3[i][j])*2)%256);
        b=(((value3[i][j])*3)%256);
        fout5<< r << " " << g << " " << b << " ";
        }
        else if(i>=3*Ny/4){
        r=(((value4[i][j])*1)%256);
        g=(((value4[i][j])*2)%256);
        b=(((value4[i][j])*3)%256);
        fout5<< r << " " << g << " " << b << " ";
        }
    }
fout5<<endl;
}
fout5.close();

// accumulating and displaying all the final result collected at rank==0
double fraction = (double) (count1+count2+count3+count4)/(Nx*Ny);
double area = (fraction)*((xmax-xmin)*(ymax-ymin));
cout<<endl;
cout<<"From rank : " <<  rank <<endl;
cout<< "Total Number of process : "<< size <<endl;
cout<< "fraction of mandelbrot Set is " << fraction <<endl;
cout<< "Area of Mandelbrot is " << area<<endl;

cout << "Range in x-axis (Real axis): xmin = " << xmin << " ; xmax = "<< xmax <<endl;
cout << "Range in y-axis (img axis) : ymin = " << ymin << " ; ymax = "<< ymax <<endl;
cout << "Length in x-axis : " << xmax-xmin <<endl;
cout << "Length in y-axis (img axis) : " << ymax-ymin <<endl;
cout << "Number of grid points in x:" << Nx <<endl;
cout << "Number of grid points in y:" << Ny <<endl ;
cout << "Area of mandlebrot is: " << area <<endl; 
}

MPI::Finalize();
return 0;
}
