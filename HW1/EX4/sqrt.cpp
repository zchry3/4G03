#include "math.h"
#include "sqrt.h"

double Sq_Tlr(double x){
    // Taylor series of sqrt(x-1) around x=0 is given by
    // 1 + x/2 - x^2/8 + x^3/16 - 5*x^4/128 + O(x^5). Given x between (0,2) we can shift
    // left by 1 unit, and evaluate in the Taylor series.
    return 1+(x-1)*(1./2+(x-1)*(-1./8+(x-1)*(1./16-5.*(x-1)/128)));
}

double Sq_Nwt(double c){
    // Use Newton's algorithm to calculate sqrt(c) by finding the
    // positive root of x^2-c=0
    double x_prev = c;
    double x_curr = c/2; // Use c/2 as a very rough intial approximation of sqrt(c)
    while(fabs(x_curr-x_prev) > 0.0001){
        double x_next = x_curr - (pow(x_curr,2)-c)/(2*x_curr);
        x_prev = x_curr;
        x_curr = x_next;
    }
    return x_curr;
}

double Sq_Frc(double x){
    // Using the relation sqrt(x) = a+(x-a^2)/(a+sqrt(x)) and setting
    // a=1 we get the relation 1+(x-1)/(2+(x-1)/2+(x-1)/2+... which we
    // will then evaluate using the recurrence method learnt in class
    double A_prev = 1;
    double A_curr = 1;
    double B_prev = 0;
    double B_curr = 1;
    for(int i = 0; i < 5; i++){
        double A_next = 2*A_curr + (x-1)*A_prev;
        double B_next = 2*B_curr + (x-1)*B_prev;
        A_prev = A_curr;
        A_curr = A_next;
        B_prev = B_curr;
        B_curr = B_next;
    }
    return A_curr/B_curr;
}
