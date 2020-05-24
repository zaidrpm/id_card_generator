#include<iostream>
#include<string>
struct bpset
{
char base;
int pow;
struct bpset *next;
};
struct exp
{
float coff;
struct bpset bp; 
struct exp *next;
};

class num
{
int ival;
float fval;
int isfloat;
void retint();
void retfloat();
public:
num
{
isfloat=0;
}
void add(char z);
void get();
}

void num::add(char z)
{
if(z>=0 && z<=9)
{

class poly
{
int isopr(char a);
void add(float coff, int pow);
void parse(char &z);
struct exp head;
public:
void set(char &z);
poly
{
exp=NULL;
}
poly(const poly &obj);
poly operator+(poly a);
poly operator-(poly a);
poly operator/(poly a);
poly operator*(poly b);
};

int poly::isopr(char a);
{
switch(a)
case '+':
case '-':
case '*':
case '/': return 1;
default: return 0;
}

void poly::set(char &z)
{
//tokeinize
}

