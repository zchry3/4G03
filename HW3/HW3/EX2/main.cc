#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "hv.h"
#include "Lan.h"
#include "../EX1/diag.h"
using namespace std;
using namespace chrono;

typedef vector<double> Row; // One row of the matrix 
typedef vector<Row> Matrix; // Matrix: a vector of rows

int main(){      
    int L,m;
    L = 10;
    int N = pow(2,L);
    Matrix Lan;
    vector<double> eig;
    
    cout << "EX2.1 Part 1" << endl << "---------------" << endl;
    ofstream file1("EX2_1_10.txt");
    file1 << "L,m,E0,E1,E2" << endl; 

    for (int i = 1; i <= 10; i++){
        m = 5*i;
        file1 << L << "," << m << ",";
        makelan(Lan, m, N, L);

        jacuppdiag(Lan, eig);
        sort(eig.begin(), eig.end());
        for(int j = 0; j < 3; j++){
            cout << eig[j] << " ";
            file1 << eig[j] << ",";
        }
        cout << endl;
        file1 << endl;
    }

    file1.close();
    cout << "---------------" << endl << "EX2.1 Part 2" << endl << "---------------" << endl;
    ofstream file2("EX2_1_14.txt");
    file2 << "L,m,E0,E1,E2" << endl;
    L = 14;
    N = pow(2,L);
    for (int i = 1; i <= 10; i++){
        m = 5*i;
        file2 << L << "," << m << ",";
        makelan(Lan, m, N, L);

        jacuppdiag(Lan, eig);
        sort(eig.begin(), eig.end());
        for(int j = 0; j < 3; j++){
            cout << eig[j] << " ";
            file2 << eig[j] << ",";
        }
        cout << endl;
        file2 << endl;
    }

    file2.close();
    cout << "---------------" << endl << "EX2.2" << endl << "---------------" << endl;
    ofstream file3("EX2_2.txt");
    file3 << "L,m,E0,E1,E2" << endl;
    L = 2;
    N = pow(2,L);
    m = 4;
    file3 << L << "," << m << ",";
    makelan(Lan, m, N, L);

    jacuppdiag(Lan, eig);
    sort(eig.begin(), eig.end());
    for (int i = 0; i < 3; i++){
        cout << eig[i] << " ";
        file3 << eig[i] << ",";
    }
    cout << endl;
    file3 << endl;

    for(int i = 2; i < 12; i++){
        L = 2*i;
        N = pow(2,L);
        m = 4*L;
        file3 << L << "," << m << ",";
        makelan(Lan, m, N, L);

        jacuppdiag(Lan, eig);
        sort(eig.begin(), eig.end());
        for (int j = 0; j < 3; j++){
            cout << eig[j] << " ";
            file3 << eig[j] << ",";
        }
        cout << endl;
        file3 << endl;
    }

    file3.close();

    return 0;
}
