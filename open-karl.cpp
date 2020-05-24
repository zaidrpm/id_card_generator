 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <iostream>
 #include <math.h>
 #include <stdio.h>
//Coner
int urightx,urighty,uleftx,ulefty,brightx,brighty,bleftx,blefty;
 using namespace cv;
 Mat img;
 Vec3b intensity,inten2;
//Equation-> y=mx+c
struct linedata
{
int n;
long int xy; //sigma xy
long int x; // sigma x
long int y; // sigma y
long int x2; // sigma x^2
long int y2; // sigma y^2
float corcoff; // cofficient of corelation
float m; // 
float c; //
};
//Line data Variables
linedata top={0,0,0,0,0,0,0.0,0.0,0.0};
linedata bottom={0,0,0,0,0,0,0.0,0.0,0.0};
linedata left={0,0,0,0,0,0,0.0,0.0,0.0};
linedata right={0,0,0,0,0,0,0.0,0.0,0.0};
//Struct functions
int l=0,k=0,mm;float t;
void push(int x,int y,linedata& d)
{
d.n+=1;
d.x+=x;
d.y+=y;
d.xy+=(x*y);
d.x2+=(x*x);
d.y2+=(y*y);
t=float(y-k);
mm=(x-l);
if(mm==0)
t=0;
else
t=t/mm;
k=y;
l=x;
std::cout << t << "\n";
}

void top_border(int xres)
{
 int i=1,j=1,c=0;
int max,min,diff,x,y;
short int blue,green,red;
 for(j=0;j<xres;j=j+40)
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
if(diff<60 && max<120)
{
push(j,i,top);
for(y=i;y<(i+8);y++)
{
for(x=j;x<(j+8);x++)
{
//inten2=img.at<Vec3b>(y,x);
inten2.val[0]=0;
inten2.val[1]=250;
inten2.val[2]=0;
img.at<Vec3b>(y,x) = inten2;
}
}
break;
}
}
}
}

void bottom_border(int xres,int yres)
{
 int i=1,j=1,c=0;
int max,min,diff,x,y;
int temp=yres-300;
short int blue,green,red;
 for(j=1;j<xres;j=j+50)
{
  for(i=yres-1;i>=temp;i--)
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
if(diff<60 && max<120)
{
push(j,i,bottom);
for(y=i-10;y<i;y++)
{
for(x=j;x<(j+10);x++)
{
inten2.val[0]=0;
inten2.val[1]=0;
inten2.val[2]=250;
img.at<Vec3b>(y,x) = inten2;
}
}
break;
}
}
}
}

void left_border(int yres)
{
 int i=1,j=1,c=0;
int max,min,diff,x,y;
short int blue,green,red;
 for(j=0;j<yres;j=j+40)
{
  for(i=0;i<=400;i++)
{
intensity = img.at<Vec3b>(j, i);
blue =int(intensity.val[0]);
green = int(intensity.val[1]);
red = int(intensity.val[2]);
max=(blue>green?blue:green);
max=(max>red?max:red);
min=(blue<green?blue:green);
min=(min<red?min:red);
diff=max-min;
if(diff<60 && max<120)
{
push(i,j,left);
for(y=j;y<(j+8);y++)
{
for(x=i;x<(i+8);x++)
{
inten2.val[0]=0;
inten2.val[1]=250;
inten2.val[2]=0;
img.at<Vec3b>(y,x) = inten2;
}
}
break;
}
}
}
}

void right_border(int xres,int yres)
{
 int i=1,j=1,c=0;
int max,min,diff,x,y;
short int blue,green,red;
int temp=xres-400;
 for(j=0;j<yres;j=j+40)
{
  for(i=xres-1;i>temp;i--)
{
intensity = img.at<Vec3b>(j, i);
blue =int(intensity.val[0]);
green = int(intensity.val[1]);
red = int(intensity.val[2]);
max=(blue>green?blue:green);
max=(max>red?max:red);
min=(blue<green?blue:green);
min=(min<red?min:red);
diff=max-min;
if(diff<60 && max<120)
{
push(i,j,right);
for(y=j;y<(j+8);y++)
{
for(x=i-8;x<i;x++)
{
inten2.val[0]=0;
inten2.val[1]=250;
inten2.val[2]=0;
img.at<Vec3b>(y,x) = inten2;
}
}
break;
}
}
}
}
void equation_gen(linedata& l)
{
int tmp=l.n*l.x2-l.x*l.x;
if(tmp==0)
l.m=0;
else
l.m=l.corcoff * sqrt(float(l.n*l.y2-l.y*l.y)/tmp);
if(l.n==0)
l.c=0;
else
l.c=float(l.y-l.m*l.x)/l.n;
}
void corner_points_printer(int x,int y)
{
int j,k;
for(j=y-4;j<(y+4);j++)
{
for(k=x-4;k<(x+4);k++)
{
inten2.val[0]=250;
inten2.val[1]=0;
inten2.val[2]=0;
img.at<Vec3b>(j,k) = inten2;
}
}
}
int main()
{
long int tmp;
img=imread("/home/zaid/Projects/c++/form-2-1-1.png");
int rows=img.rows;
int cols=img.cols;
std::cout << "----------------------------Top Line-----------------------------------------\n";
top_border(cols);
std::cout << "\n\n\n-------------------------------------------------------------------------\n";
bottom_border(cols,rows);
left_border(rows);
right_border(cols,rows);

//Cov calculation
tmp=(top.n * top.x2 - top.x * top.x)*(top.n * top.y2 - top.y * top.y);
if(tmp==0)
top.corcoff=0;
else
top.corcoff=float(top.n * top.xy - top.x * top.y)/sqrt(tmp);

tmp=(bottom.n * bottom.x2 - bottom.x * bottom.x)*(bottom.n * bottom.y2 - bottom.y * bottom.y);
if(tmp==0)
bottom.corcoff=0;
else
bottom.corcoff=float((bottom.n * bottom.xy - bottom.x * bottom.y))/sqrt(tmp);

tmp=(left.n * left.x2 - left.x * left.x)*(left.n * left.y2 - left.y * left.y);
if(tmp==0)
left.corcoff=0;
else
left.corcoff=float((left.n * left.xy - left.x * left.y))/sqrt(temp);

tmp=(right.n * right.x2 - right.x * right.x)*(right.n * right.y2 - right.y * right.y);
if(tmp==0)
right.corcoff=0;
else
right.corcoff=float((right.n * right.xy - right.x * right.y))/sqrt(tmp);
//Eqation of line-
equation_gen(top);
equation_gen(bottom);
equation_gen(right);
equation_gen(left);
//Intersection point of top right corner
//int urightx,urighty,uleftx,ulefty,brightx,brighty,bleftx,blefty;
urightx=(right.c-top.c)/(top.m-right.m);
urighty=(right.m*top.c-right.c*top.m)/(right.m-top.m);
corner_points_printer(urightx,urighty);

uleftx=(left.c-top.c)/(top.m-left.m);
ulefty=(left.m*top.c-left.c*top.m)/(left.m-top.m);
corner_points_printer(uleftx,ulefty);

brightx=(right.c-bottom.c)/(bottom.m-right.m);
brighty=(right.m*bottom.c-right.c*bottom.m)/(right.m-bottom.m);
corner_points_printer(brightx,brighty);

bleftx=(left.c-bottom.c)/(bottom.m-left.m);
blefty=(left.m*bottom.c-left.c*bottom.m)/(left.m-bottom.m);
corner_points_printer(bleftx,blefty);

//namedWindow("image", CV_WINDOW_AUTOSIZE);
//imshow("image", img);
//waitKey();
//std::cout << "Yossddsdoo" << std::endl;
imwrite("/home/zaid/Projects/c++/dited.png", img);
return 0;
}
