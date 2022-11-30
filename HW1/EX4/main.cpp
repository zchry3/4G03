#include <ctime>
#include <iostream>
#include "sqrt.h"
using namespace std;

int main(){
    cout.precision(10);
    cout << "Sq_Tlr(0.5) = " << Sq_Tlr(0.5) << endl;
    cout << "Sq_Nwt(0.5) = " << Sq_Nwt(0.5) << endl;
    cout << "Sq_Frc(0.5) = " << Sq_Frc(0.5) << endl;

    clock_t begin_time = clock();
    for(int i = 0; i < 10000000; i++){
        double calc = Sq_Tlr(0.5);
    }
    clock_t end_time = clock();
    double elapsed_secs = double(end_time-begin_time)/CLOCKS_PER_SEC;
    cout << "Sq_Tlr Time Elapsed " << elapsed_secs << endl;

    begin_time = clock();
    for(int i = 0; i < 10000000; i++){
        double calc = Sq_Nwt(0.5);
    }
    end_time = clock();
    elapsed_secs = double(end_time-begin_time)/CLOCKS_PER_SEC;
    cout << "Sq_Nwt Time Elapsed " << elapsed_secs << endl;
    
    begin_time = clock();
    for(int i = 0; i < 10000000; i++){
        double calc = Sq_Frc(0.5);
    }
    end_time = clock();
    elapsed_secs = double(end_time-begin_time)/CLOCKS_PER_SEC;
    cout << "Sq_Frc Time Elapsed " << elapsed_secs << endl;
  
    return 0;
}
