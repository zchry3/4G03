#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "diag.h"
using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

// Kronecker delta
int delta(int n, int m){
    if (n==m){
        return 1;
    } else {
        return 0;
    }
}

// Computes Hnm
double H(int n, int m){
    return 4*pow(n+1,2)*delta(n,m)+4*fmin(n+1,m+1)*(0.05+5*pow((-1),fabs(n-m)));
}

int main(){
    Matrix Ham;
    vector<double> eig;
    for(int k = 1; k < 5; k++){
        for(int i = 0; i < 10*k; i++){
            Row row;
            for(int j = 0; j < 10*k; j++){
                row.push_back(H(i,j));
            }
            Ham.push_back(row);
        }
        jacuppdiag(Ham, eig);
        sort(eig.begin(), eig.end());
        for(int i = 0; i < 3; i++){
            cout << eig[i] << " ";
        }
        cout << endl;

        Ham.clear();
        eig.clear();
    }

    return 1;
}
