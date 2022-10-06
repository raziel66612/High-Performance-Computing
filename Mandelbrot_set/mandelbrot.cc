#include<fstream>
#include<iostream>
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

int main()
{
double xmin,xmax,ymin,ymax,Nx,Ny,dx,dy;

Nx=1000;  //total number of y nodes
Ny=800;  //total number of x nodes
xmin=-2.0; //limit on negative x axis(real axis)
xmax=2.0;  //limit on positive x axis(real axis)
ymin=-1.0;  //limit on negative y axis(img axis)
ymax=+1.0;  //limit on positive y axis(img axis)

/*creating .ppm output for visualization*/
ofstream fout("mandelbrot_set_grid_1000x800.ppm");    //using ppm for plotting, 
fout << "P3" << endl;   // "magic number" for defining ppm.
fout << Nx << " " << Ny << endl;  
fout << "256" << endl; //pixel's max RGB value

dx=((xmax-xmin)/(Nx));   //step size in x direction 
dy=((ymax-ymin)/(Ny));   //step size in x direction

int count = 0;     //defining variable count for calculating area

for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;

        int value = mandelbrot(cx,cy);

        if (value>9999){
            ++count;
        }
        
//        cout << value;   //for testing purpose

        int r=((value*1)%256);
        int g=((value*2)%256);
        int b=((value*3)%256);

        fout<< r << " " << g << " " << b << " ";
        }
//        cout << endl;
fout << endl ;
}
fout.close();

double fraction =  (count)/(Nx*Ny);
double area = (fraction*(xmax-xmin))*(ymax-ymin);
cout<< "fraction of mandelbrot Set is " << fraction <<endl;
cout<< "Area of Mandelbrot is " << area;

/* creating output files with required output*/
ofstream myfile("result_grid_1000x800.txt");
myfile << "Range in x-axis : xmin = " << xmin << " ; xmax = "<< xmax <<endl;
myfile << "Range in y-axis (img axis) : ymin = " << ymin << " ; ymax = "<< ymax <<endl;
myfile << "Length in x-axis : " << xmax-xmin <<endl;
myfile << "Length in y-axis (img axis) : " << ymax-ymin <<endl;
myfile << "Number of grid points in x:" << Nx <<endl;
myfile << "Number of grid points in y:" << Ny <<endl ;
myfile << "Area of mandlebrot is: " << area <<endl; 

myfile.close();
return 0;
}