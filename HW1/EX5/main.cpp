#include <iostream>
#include <ctime>
#include "Romberg.h"
using namespace std;

double myfunc (double x){
    double r;
    r=4./(1+x*x);
    return r;
}

int main(){
    int level;
    cout.precision(24);
    cout << "The Trapezoidal result is      " << Trapezoidal(&myfunc,0.0,1.0,64) << endl;
    cout << "The Romberg result is          " << Romberg(&myfunc,0.0,1.0,6) << endl << endl;

    cout << "R(6,6)   =      " << Romberg(&myfunc,0.0,1.0,6) << endl;
    cout << "R(8,8)   =      " << Romberg(&myfunc,0.0,1.0,8) << endl;
    cout << "R(10,10) =      " << Romberg(&myfunc,0.0,1.0,10) << endl << endl;
    
    for(int i=1; i <= 15; i++){
        double val;
        clock_t begin_time = clock();
        for(int j=1; j < 1000000; j++){
            val = Trapezoidal(&myfunc,0.0,1.0,i*i);
        }
        clock_t end_time = clock();
        double elapsed_sec = double(end_time-begin_time)/CLOCKS_PER_SEC;
        cout << "Intervals: " << i*i << " Value: " << val << " Time: " << elapsed_sec << endl;
    }
    cout << endl;
    for(int i=1; i<=10; i++){
        double val;
        clock_t begin_time = clock();
        for(int j=1; j < 1000000; j++){
            val = Romberg(&myfunc,0.0,1.0,i);
        }
        clock_t end_time = clock();
        double elapsed_sec = double(end_time-begin_time)/CLOCKS_PER_SEC;
        cout << "Approximants: " << i << " Value: " << val << " Time: " << elapsed_sec << endl;
    }
    return 0;
}
