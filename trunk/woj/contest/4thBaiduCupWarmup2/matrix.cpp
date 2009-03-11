//matrix.h
//*******************************
# ifndef matrix_h
# define matrix_h

class matrix
{
private:
int m;
int n;
double arr[8][8];
public:
matrix();
matrix(double);
void set();// 对矩阵的赋值;
void show();//在屏幕上显示矩阵;
friend int homotype(matrix,matrix);//是否同型;
friend int multipliable(matrix,matrix);
//判断矩阵是否可相乘
friend matrix operator +(matrix,matrix);
//矩阵相加,对加号重载;
friend matrix operator -(matrix,matrix);
//矩阵机减,对减号重载;
friend matrix add(matrix,matrix);
//矩阵相加;
friend matrix minus(matrix,matrix);
//矩阵相减
friend matrix multiply(matrix,matrix);
//矩阵相乘
friend matrix operator *(matrix,matrix);
//矩阵相乘,对乘号重载;
friend double det(matrix);
//求方阵的行列式;
int issquare()
{
return m==n;
}
//判断是否为方阵;
matrix left(int x,int y);
//求元素arr[x][y](x,y从0开始)的余子式;
};

# endif
//*******************************
//matrix.cpp
//下面是对类中成员及友元函数的实现
//*******************************
# include <iostream.h>
# include "matrix.h"

matrix::matrix()
{
m = 8;
n = 8;
for(int i=0;i<m;i++)
{
for(int j=0;j<n;j++)
arr[i][j] = 0;
}
}
matrix::matrix(double x)
{
m = 1;
n = 1;
arr[0][0] = x;
}
void matrix::set()
{
cout<<"Set the type of the matrix(?*?)"<<endl;
cin>>m>>n;
cout<<"Now input the elements of the matrix:"<<endl;
for(int i=0;i<m;i++)
{
for(int j=0;j<n;j++)
cin>>arr[i][j];
}
}

void matrix::show()
{
cout<<"This is the matrix:"<<endl;
for(int i=0;i<m;i++)
{
for(int j=0;j<n;j++)
{
cout<<arr[i][j]<<ends;
}
cout<<endl;
}
}

int homotype(matrix x,matrix y)
{
if(x.m==y.m&&x.n==y.n)
return 1;
else
return 0;
}
int multipliable(matrix x,matrix y)
{
if(x.n==y.m)
return 1;
else
return 0;
}
matrix add(matrix x,matrix y)
{
matrix z;
if(homotype(x,y))
{
z.m = x.m;
z.n = x.n;
for(int i=0;i<z.m;i++)
for(int j=0;j<z.n;j++)
z.arr[i][j] = x.arr[i][j] + y.arr[i][j];
return z;
}
else
{
cout<<"cannot be added!"<<endl;
return z;
}
}
matrix operator +(matrix x,matrix y)
{
return add(x,y);
}
matrix minus(matrix x,matrix y)
{
matrix z;
if(homotype(x,y))
{
z.m = x.m;
z.n = x.n;
for(int i=0;i<z.m;i++)
for(int j=0;j<z.n;j++)
z.arr[i][j] = x.arr[i][j] - y.arr[i][j];
return z;
}
else
{
cout<<"cannot be added!"<<endl;
return z;
}
}
matrix operator -(matrix x,matrix y)
{
return minus(x,y);
}
matrix multiply(matrix x,matrix y)
{
matrix z;
if(x.n!=y.m)
{
cout<<"The two matrixes cannot be multiplied."<<endl;
return z;
}
for(int i=0;i<x.m;i++)
{
for(int j=0;j<y.n;j++)
{
for(int k=0;k<x.n;k++)
z.arr[i][j] += x.arr[i][k]*y.arr[k][j];
}
}
z.m = x.m;
z.n = y.n;
return z;
}
matrix operator *(matrix x,matrix y)
{
matrix z;
z = multiply(x,y);
return z;
}
matrix matrix::left(int x,int y)
{
matrix leftmatrix;
if((x>=m)||(y>=n))
{
cout<<"errer"<<endl;
return leftmatrix;
}
/* if(!issquare())
{
cout<<"不是方阵!"<<endl;
return *this;
}//*/

leftmatrix.m = m - 1;
leftmatrix.n = n - 1;
int testx = 0;
int testy = 0;
for(int i=0;i<leftmatrix.m;i++)
{
testy = 0;
for(int j=0;j<leftmatrix.n;j++)
{
if(i==x)
testx = 1;
if(j==y)
testy = 1;
if((!testx)&&(!testy))
leftmatrix.arr[i][j] = this->arr[i][j];
else if(testx&&(!testy))
leftmatrix.arr[i][j] = this->arr[i+1][j];
else if((!testx)&&testy)
leftmatrix.arr[i][j] = this->arr[i][j+1];
else
leftmatrix.arr[i][j] = this->arr[i+1][j+1];
}
}
return leftmatrix;
}

double det(matrix x)//递归算法
{
if(!x.issquare())
{
cout<<"不是方阵!"<<endl;
return 9.99;
}
if(x.m==0)
return 0;
else if(x.m==1)
return x.arr[0][0];
else if(x.m==2)
return (x.arr[0][0]*x.arr[1][1] - x.arr[0][1]*x.arr[1][0]);
else
{
double num = 0;
int a = 1;
for(int i=0;i<x.m;i++)
{
num = num + a*x.arr[0][i]*det(x.left(0,i));
//按第0行展开
a = -a;
}
return num;
}
}
//**************************************
