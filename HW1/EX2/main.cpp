#include <iostream>
#include "bessel.h"
using namespace std;

int main(){
    // Calculate J_20(0.5) using ascending recurrence and print value
    double J_20 = bessel_ascending(20);
    cout << "J_20(0.5) = " << J_20 << endl << endl;

    // Calculate J_3(0.5) through J_20(0.5) using ascending recurrence to compare with real
    // values
    for(int i = 2; i <= 20; i++){
        cout << "J_" << i << "(0.5) = " << bessel_ascending(i) << endl;
    }

    // Calculate J_0(0.5) and J_1(0.5) using descending recurrence and
    // print values
    cout.precision(20);
    cout << endl << "J_0(0.5) = " << bessel_descending(0, 0.5) << endl;
    cout << "J_1(0.5) = " << bessel_descending(1, 0.5) << endl;
    return 0;
}
