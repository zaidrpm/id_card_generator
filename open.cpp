#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>
#define threshold 200.0d
#define inten 120
#define difference 25
#define depth 800
#define sepration 100
#define sepration2 1
#define endl '\n'
 /*
 Dimensions of Block-2051x2850
 
 */
//Global variables 
//Coner
int urightx,urighty,uleftx,ulefty,brightx,brighty,bleftx,blefty;
int rows,cols;
 using namespace cv;
 Mat img;
 Vec3b intensity,intensity2;
struct linedata
{
//data[1]-> m; data[1]-> c ; data[2]-> vote
float mdata[100];
double cdata[100];
short int vote[100];
double ctotal[100];
int p;
int xlast;
int ylast;
float m;
double c;
int pos;
}top,bottom,left,right; 

int isblack(int x,int y)
{
intensity = img.at<Vec3b>(y,x);
int blue =intensity.val[0];
int green = intensity.val[1];
int red = intensity.val[2];
int diff=(blue>green?(blue>red?blue:red):(green>red?green:red))-(blue<green?(blue<red?blue:red):(green<red?green:red));
if(diff<difference && blue<inten)
return 1;
else
return 0;
}

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
float m;
double c;
int i,flag=1;
if(x==d.xlast)
{
m=1000.0f; // 1000 for infinity
c=double(x);
}
else
{
m=float(y-d.ylast)/(x-d.xlast);
c=double(y-m*x);
}
d.xlast=x;
d.ylast=y;
for(i=0;i<d.p;i++)
	{
	if(( d.mdata[i]==m && abs(d.cdata[i]-c)<3.0) || (d.mdata[i]==m && abs(d.cdata[i]-c)<threshold && d.mdata[i]!=1000.0f))
		{
		d.vote[i]+=1;
		d.ctotal[i]+=c;
		flag=0;
		break;
		}
	}
if(flag)
	{
	d.mdata[d.p]=m;
	d.cdata[d.p]=c;
	d.ctotal[d.p]=c;
	d.vote[d.p]=1;
	d.p+=1;
	}
//printer(x,y,0,250,0);
}

//j for x for columns
//i for y for rows
void top_border(int xres)
{
 int i=1,j=1,flag=0,flag2=1;
int max,min,diff,x,y;
for(j=0;j<xres && flag==0;j=j+sepration)
	{
  	 for(i=0,flag2=1;i<=depth;i=i+sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			top.xlast=j;
			top.ylast=i;
			//printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+sepration)
	{
	for(i=0,flag2=1;i<=depth;i=i+sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			push(j,i,top);	
			//printer(j,i,0,250,0);
			break;
			}
		}
	}
}

void bottom_border(int xres,int yres)
{
 int i=1,j=1;
int max,min,diff,x,y,flag=0,flag2;
for(j=0;j<xres && flag==0;j=j+sepration)
	{
  	for(i=yres-1,flag2=1;i>=(yres-depth);i=i-sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			bottom.xlast=j;
			bottom.ylast=i;
			//printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;j<xres;j=j+sepration)
	{
	for(i=yres-1,flag2=1;i>=(yres-depth);i=i-sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			push(j,i,bottom);	
			//printer(j,i,0,250,0);
			break;
			}
		}
	}
}

void left_border(int yres)
{
 int i=1,j=1,flag=0,flag2;
int max,min,diff,x,y;
for(i=0;i<yres && flag==0;i=i+sepration)
	{
  	for(j=0,flag2=1;j<depth;j=j+sepration2)
		{
			if(isblack(j,i) && flag2==1)
			continue;
			flag2=0;
			if(isblack(j,i))
			{
			left.xlast=j;
			left.ylast=i;
			//printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i=i+sepration)
	{
	for(j=0,flag2=1;j<depth;j=j+sepration2)
		{
			if(isblack(j,i) && flag2==1)
			continue;
			flag2=0;
			if(isblack(j,i))
			{
			push(j,i,left);	
			//printer(j,i,0,250,0);
			break;
			}
		}
	}
}


void right_border(int xres,int yres)
{
 int i=1,j=1,flag=0,flag2;
int max,min,diff,x,y;
for(i=0;i<yres && flag==0;i=i+sepration)
	{
  	for(j=xres-1,flag2=1;j>(xres-depth);j-=sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			right.xlast=j;
			right.ylast=i;
			//printer(j,i,0,250,0);
			flag=1;
			break;
			}
		}
	}

for(;i<yres;i=i+sepration)
	{
	for(j=xres-1,flag2=1;j>(xres-depth);j-=sepration2)
		{
		if(isblack(j,i) && flag2)
		continue;
		flag2=0;
		if(isblack(j,i))
			{
			push(j,i,right);	
			//printer(j,i,0,250,0);
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
	if(d.vote[i] > d.vote[pos])
	pos=i;
	}
d.m=d.mdata[pos];
d.c=d.ctotal[pos]/d.vote[pos];
d.pos=pos;
}

void corner(int *x, int *y,linedata& d1, linedata& d2)
{
if(d1.m==1000.0f)
{
*x=int(d1.c);
*y=int(d2.m*(*x)+d2.c);
}
else if(d2.m==1000.0f)
{
*x=int(d2.c);
*y=int(d1.m*(*x)+d1.c);
}
else
{
*x=(d1.c-d2.c)/(d2.m-d1.m);
*y=d2.m*(*x)+d2.c;
}
printer(*x,*y,0,0,250);
}


void line_printer(linedata& d)
{
int i,j,temp;
if(d.m==1000.0f)
{
for(i=0;i<rows;i++)
printer(int(d.c),i,250,0,0);
}
else
{
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

corner(&urightx,&urighty,right,top);
corner(&uleftx,&ulefty,left,top);
corner(&brightx,&brighty,right,bottom);
corner(&bleftx,&blefty,left,bottom);

// Correcting





imwrite("/home/zaid/Projects/c++/dited.png", img);
return 0;
}
