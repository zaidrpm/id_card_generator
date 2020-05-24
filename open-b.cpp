 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <iostream>
 #define threshold 100.0
 #define intensitydiff 50
 #define intensitymax 100
 //#include <math.h>
//Coner
int urightx,urighty,uleftx,ulefty,brightx,brighty,bleftx,blefty;
 using namespace cv;
// using namespace std;
 Mat img;
 Vec3b intensity,inten2;
struct linedata
{
float data[3][100];
//data[1]-> m; data[1]-> c ; data[2]-> vote
int p;
int xlast;
int ylast;
float m;
float c;
}top,bottom,left,right; 

//Initializing variables


void printer(int x, int y, int b, int g, int r)
{
	int j,k;
	for(j=x;j<(x+8);j++)
				{
				for(k=y;k<(y+8);k++)
					{
					inten2.val[0]=b;
					inten2.val[1]=g;
					inten2.val[2]=r;
					img.at<Vec3b>(k,j) = inten2;
					}
				}
}

void push(int x,int y,linedata& d)
{
float m,c;
int i,flag=1;
m=float(y-d.ylast)/(x-d.xlast);
c=float(y-m*x);
d.xlast=x;
d.ylast=y;
for(i=0;i<d.p;i++)
	{
	if(d.data[0][i]==m && ((d.data[1][i]-threshold) < c) &&	((d.data[1][i]+threshold) > c))
		{
		d.data[2][i]+=1.0;
		flag=0;
		break;
		}
	}
if(flag)
	{
	d.data[0][d.p]=m;
	d.data[1][d.p]=c;
	d.data[2][d.p]=1;
	d.p+=1;
	}
//std::cout << m << "	      " << c << "\n";
}

//j for x for columns
//i for y for rows
void top_border(int xres)
{
 int i=1,j=1,flag=0;
int max,min,diff,x,y;
short int blue,green,red;
for(j=0;j<xres && flag==0;j+=80)
	{
  	for(i=0;i<=300;i++)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			top.xlast=j;
			top.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+80)
	{
	for(i=0;i<=300;i++)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		std::cout << diff << "	" << max << "\n";
		if(diff<intensitydiff && max<intensitymax)
			{
			push(j,i,top);	
			printer(j,i,0,250,0);
			break;
			}
		}
	}
}

void bottom_border(int xres,int yres)
{
 int i=1,j=1;
int max,min,diff,x,y,flag=0;
short int blue,green,red;
for(j=0;j<xres && flag==0;j=j+80)
	{
  	for(i=yres-1;i>=(yres-300);i--)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			bottom.xlast=j;
			bottom.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+80)
	{
	for(i=yres-1;i>=(yres-300);i--)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			push(j,i,bottom);	
			printer(j,i,0,250,0);
			break;
			}
		}
	}
}

void left_border(int yres)
{
 int i=1,j=1,flag=0;
int max,min,diff,x,y;
short int blue,green,red;
for(i=0;i<yres && flag==0;i+=80)
	{
  	for(j=0;j<300;j++)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			left.xlast=j;
			left.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i+=80)
	{
	for(j=0;j<300;j++)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			push(j,i,left);	
			printer(j,i,0,250,0);
			break;
			}
		}
	}
}


void right_border(int xres,int yres)
{
 int i=1,j=1,flag=0;
int max,min,diff,x,y;
short int blue,green,red;
for(i=0;i<yres && flag==0;i+=80)
	{
  	for(j=(xres-1);j>(xres-300);j--)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			right.xlast=j;
			right.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i+=80)
	{
	for(j=xres-1;j>(xres-300);j--)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		max=(blue>green?blue:green);
		max=(max>red?max:red);
		min=(blue<green?blue:green);
		min=(min<red?min:red);
		diff=max-min;
		if(diff<intensitydiff && max<intensitymax)
			{
			push(j,i,right);	
			printer(j,i,0,250,0);
			break;
			}
		}
	}
}

void calculate(linedata& d)
{
int i,pos;
if(d.p>0)
pos=0;
for(i=1;i<d.p;i++)
	{
	if(d.data[2][i] > d.data[2][pos])
	pos=i;
	}
d.m=d.data[0][pos];
d.c=d.data[1][pos];
}
int main()
{
top.p=0;
bottom.p=0;
left.p=0;
right.p=0;
long int tmp;
img=imread("/home/zaid/Projects/c++/3.png");
int rows=img.rows;
int cols=img.cols;
std::cout << "\n---------------------------Top--------------------------\n";
top_border(cols);
std::cout << "\n---------------------------Bottom--------------------------\n";
bottom_border(cols,rows);
std::cout << "\n---------------------------Left--------------------------\n";
left_border(rows);
std::cout << "\n---------------------------Right--------------------------\n";
right_border(cols,rows);

// Equation calculation
calculate(top);
calculate(bottom);
calculate(left);
calculate(right);

int i,j;
float temp;
for(i=0;i<rows;i++)
{
for(j=0;j<cols;j++)
{
temp=i-top.m*j-top.c;
if(int(temp)==0)
printer(j,i,250,0,0);
}
}

for(i=0;i<rows;i++)
{
for(j=0;j<cols;j++)
{
temp=i-bottom.m*j-bottom.c;
if(int(temp)==0)
printer(j,i,250,0,0);
}
}

for(i=0;i<rows;i++)
{
for(j=0;j<cols;j++)
{
temp=i-left.m*j-left.c;
if(int(temp)==0)
printer(j,i,250,0,0);
}
}

for(i=0;i<rows;i++)
{
for(j=0;j<cols;j++)
{
temp=i-right.m*j-right.c;
if(int(temp)==0)
printer(j,i,250,0,0);
}
}
/*int i=0;
for(i=0;i<top.p;i++)
std::cout << top.data[0][i] << "	" << top.data[1][i] << "	" << top.data[2][i] << "\n";*/
imwrite("/home/zaid/Projects/c++/dited.png", img);
return 0;
}
