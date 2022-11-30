#include "bisection.h"
#include "../EX2/bessel.h"
#include <iostream>
using namespace std;

int main(){
    for(int i=1; i<4; i++){
        cout << "J_(0," << i << ") = " << bisection(i, 0.0001) << endl;
    }
    return 0;
}
