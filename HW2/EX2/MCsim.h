#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include "MCvar.h"
using namespace std;

class MCsim {
    // Variables
    public:
        double var [6]; // E E^2 E^4 M M^2 M^4
        double varAvg [6];
        double varErr [6];
    private:
        int L;
        vector<vector<int>> SpinConf;
        double hotness;
        double T;
        double kB;
        double prob [2];    // Although there are 5 possible values for e^(-dE/kBT) only 2 are less than 1
        vector<int> nLeft;
        vector<int> nRight;
        mt19937 rng;
        MCvar<int> Ebin;
        MCvar<int> E2bin;
        MCvar<double> E4bin;
        MCvar<int> Mbin;
        MCvar<int> M2bin;
        MCvar<double> M4bin;

   // Methods
   public:
        MCsim(int size, double cool);

        void print_lattice();

        void MCsweeps(int Nmcs);

        int Energy();

        int Magnetization();

        void do_measurement();

        void print_var(){
            cout << var[0] << endl;
            cout << var[1] << endl;
            cout << var[2] << endl;
            cout << var[3] << endl;
            cout << var[4] << endl;
            cout << var[5] << endl;
        }

        void printout();

        void SQIsing(int NWarmup, int Nmeas, int NStep);
};
