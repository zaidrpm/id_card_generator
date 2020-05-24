#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>
#define threshold 200.0f
#define inten 120
#define depth 800
#define sepration 150
#define sepration2 1
 /*
 Dimensions of Block-2051x2850
 
 */
//Global variables 
//Coner
int urightx,urighty,uleftx,ulefty,brightx,brighty,bleftx,blefty;
int rows,cols;
// int rkp,ckp;
 using namespace cv;
 Mat img;
 Vec3b intensity,intensity2;
struct linedata
{
float data[3][100];
//data[1]-> m; data[1]-> c ; data[2]-> vote
int p;
int xlast;
int ylast;
float m;
float c;
int pos;
}top,bottom,left,right; 


void printer(int x, int y, int b, int g, int r)
{
	int j,k;
	for(j=x;j<(x+8) && j<cols;j++)
				{
				for(k=y;k<(y+8) && k<rows;k++)
					{
					intensity2.val[0]=b;
					intensity2.val[1]=g;
					intensity2.val[2]=r;
					img.at<Vec3b>(k,j) = intensity2;
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
	if((d.data[0][i]==m) && (abs(d.data[1][i]-c)<threshold))
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
}

//j for x for columns
//i for y for rows
void top_border(int xres)
{
 int i=1,j=1,flag=0;
int max,min,diff,x,y;
short int blue,green,red;
for(j=0;j<xres && flag==0;j=j+sepration)
	{
  	for(i=0;i<=depth;i=i+sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
			{
			top.xlast=j;
			top.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+sepration)
	{
	for(i=0;i<=depth;i=i+sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
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
for(j=0;j<xres && flag==0;j=j+sepration)
	{
  	for(i=yres-1;i>=(yres-depth);i=i-sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
			{
			bottom.xlast=j;
			bottom.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+sepration)
	{
	for(i=yres-1;i>=(yres-depth);i=i-sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
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
for(i=0;i<yres && flag==0;i=i+sepration)
	{
  	for(j=0;j<depth;j=j+sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
			{
			left.xlast=j;
			left.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i=i+sepration)
	{
	for(j=0;j<depth;j=j+sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
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
for(i=0;i<yres && flag==0;i=i+sepration)
	{
  	for(j=(xres-1);j>(xres-depth);j-=sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
			{
			right.xlast=j;
			right.ylast=i;
			printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i=i+sepration)
	{
	for(j=xres-1;j>(xres-depth);j-=sepration2)
		{
		intensity = img.at<Vec3b>(i, j);
		blue =int(intensity.val[0]);
		green = int(intensity.val[1]);
		red = int(intensity.val[2]);
		if((blue<inten) && (green < inten) && (red < inten))
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
d.pos=pos;
}

void line_printer(linedata& d)
{
int i,j,temp;
for(i=0;i<rows;i++)
{
for(j=0;j<cols;j++)
{
temp=i-d.m*j-d.c;
if(temp==0)
printer(j,i,250,0,0);
}
}
}

int main(int argc,char *argv[])
{
top.p=0;
bottom.p=0;
left.p=0;
right.p=0;
long int tmp;
img=imread(argv[1]);
//int rows,cols;
rows=img.rows;
cols=img.cols;
//rkp=rows;
//ckp=cols;
top_border(cols);
bottom_border(cols,rows);
left_border(rows);
right_border(cols,rows);

// Equation calculation
calculate(top);
calculate(bottom);
calculate(left);
calculate(right);

//Printing Line
line_printer(top);
line_printer(bottom);
line_printer(right);
line_printer(left);

//Calculating corners
//Top-Right 
urightx=(right.c-top.c)/(top.m-right.m);
urighty=top.m*urightx+top.c;
//Top-left
uleftx=(left.c-top.c)/(top.m-left.m);
ulefty=top.m*uleftx+top.c;
//Bottom-Right
brightx=(right.c-bottom.c)/(bottom.m-right.m);
brighty=bottom.m*brightx+bottom.c;
//Bottom-Left
bleftx=(left.c-bottom.c)/(bottom.m-left.m);
blefty=bottom.m*bleftx+bottom.c;

//Printing Corners
printer(urightx,urighty,0,0,250);
printer(uleftx,ulefty,0,0,250);
printer(brightx,brighty,0,0,250);
printer(bleftx,blefty,0,0,250);

imwrite("/home/zaid/Projects/c++/dited.png", img);
return 0;
}
