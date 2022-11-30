#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "MCvar.h"
#include "MCsim.h"
using namespace std;

int main(){
    // Exercise 2.4
    MCsim M_lattice_1(50, 2.26);
    ofstream myfile;
    myfile.open("M_list_226.txt");
    M_lattice_1.MCsweeps(100000);
    for(int i = 0; i < 500000; i++){
        M_lattice_1.MCsweeps(1);
        M_lattice_1.do_measurement();
        myfile << M_lattice_1.varAvg[3] << endl;
    }
    myfile.close();
    MCsim M_lattice_2(50, 2.45);
    myfile.open("M_list_245.txt");
    M_lattice_2.MCsweeps(100000);
    for(int i = 0; i < 500000; i++){
        M_lattice_2.MCsweeps(1);
        M_lattice_2.do_measurement();
        myfile << M_lattice_2.varAvg[3] << endl;
    }
    myfile.close();

    // Exercise 2.5
    myfile.open("EX2_5.txt");
    for(int i = 0; i < 11; i++){
        MCsim lattice(10, 2+0.05*i);
        myfile << "T=" << 2+0.05*i << endl;
        lattice.SQIsing(10000, 50000, 100);
        for(int i = 0; i < 6; i++){
            myfile << lattice.varAvg[i] << "," << lattice.varErr[i] << ",";
        }
        myfile << endl;
    }
    myfile.close();

    // Exercise 2.6
    myfile.open("EX2_6.txt");
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 3; j++){
            MCsim lattice(8+4*j,2+0.05*i);
            myfile << "L=" << 8+4*j << " T=" << 2+0.05*i << endl;
            lattice.SQIsing(10000, 100000, 10);
            for(int i = 0; i < 6; i++){
                myfile << lattice.varAvg[i] << "," << lattice.varErr[i] << ",";
            }
            myfile << endl;
        }
    }
    myfile.close();

    return 1;
}
