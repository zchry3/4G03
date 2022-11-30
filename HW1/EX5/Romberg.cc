// Numerical Integration
#include <math.h>
#include "Romberg.h"

double Trapezoidal(double (*f)(double x), double xl,double xh,int n)
{ 
  double dx = (xh - xl)/n;
  double sum = 0;
  double f_prev = f(xl);
  double f_curr = f(xl + dx);
  for(int i = 1; i <= n; i++){
      sum += (f_curr + f_prev);
      f_prev = f_curr;
      f_curr = f(xl+(i+1)*dx);
  }
  sum *= dx/2;
  return sum;
}

double Romberg(double (*f)(double x), double xl,double xh,int N)
{ 
  double R_table [N+1][N+1];
  R_table[0][0] = (f(xl)+f(xh))/2;
  double h = 0.5;
  for(int n = 1; n <= N; n++){
      double sum = 0;
      for(double k = 1; k <= pow(2,n-1); k++){
          sum += f(xl + (2*k - 1)*h);
      }
      R_table[n][0] = R_table[n-1][0]/2 + h*sum;
      h = h/2;
      for(int m = 1; m <= n; m++){
          R_table[n][m] = R_table[n][m-1] + (R_table[n][m-1] - R_table[n-1][m-1])/(pow(4,m)-1);
      }
  }
  return R_table[N][N];
}
