#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include "MCvar.h"
#include "MCsim.h"
using namespace std;

MCsim::MCsim(int size, double hot){
    L = size;
    SpinConf.resize(L);
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    rng.seed(seed);
    uniform_int_distribution<int> spins(0,1);
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
                SpinConf[i].push_back(2*spins(rng)-1);
            }
        }
    kB = 1.380649e-23;
    hotness = hot;
    T = hotness/(kB);
    for(int i = 0; i < 2; i++){
        prob[i] = exp(-2*(2*(i+1))/hotness); // Only need to consider cases where sum of spins is positive (spin initially aligned with most of its neighbours)
    }
    nLeft.push_back(L-1);
    for(int i = 0; i < L-1; i++){
        nLeft.push_back(i);
        nRight.push_back(i+1);
    }
    nRight.push_back(0);
}

void MCsim::print_lattice(){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            cout << SpinConf[i][j] << " ";
        }
        cout << endl;
    }
}

void MCsim::MCsweeps(int Nmcs){
    int nFlips = L*L*Nmcs;
    uniform_int_distribution<int> coord(0,L-1);
    uniform_real_distribution<double> flip(0.0,1.0);
    int x;
    int y;
    int sumSpins;
    double flipProb;
    for(int i = 0; i < nFlips; i++){
        x = coord(rng);
        y = coord(rng);
        sumSpins = SpinConf[x][y]*(SpinConf[nLeft[x]][y]+SpinConf[nRight[x]][y]+SpinConf[x][nLeft[y]]+SpinConf[x][nRight[y]]);
        if(sumSpins <= 0){
            SpinConf[x][y] = -1*SpinConf[x][y];
        } else {
            flipProb = flip(rng);
            if(flipProb < prob[(sumSpins/2)-1]){
                SpinConf[x][y] = -1*SpinConf[x][y];
            }
        }
    }
}

int MCsim::Energy(){
    int sumSpins = 0;
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            sumSpins -= SpinConf[i][j]*SpinConf[nRight[i]][j];
            sumSpins -= SpinConf[i][j]*SpinConf[i][nRight[j]];
        }
    }
    return sumSpins;
}

int MCsim::Magnetization(){
    int sumSpins = 0;
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            sumSpins += SpinConf[i][j];
        }
    }
    return sumSpins;
}

void MCsim::do_measurement(){
    int eng = Energy();
    int mag = Magnetization();
    var[0] = eng;
    var[1] = pow(eng,2);
    var[2] = pow(eng,4);
    var[3] = mag;
    var[4] = pow(mag,2);
    var[5] = pow(mag,4);
    Ebin.push(var[0]);
    E2bin.push(var[1]);
    E4bin.push(var[2]);
    Mbin.push(var[3]);
    M2bin.push(var[4]);
    M4bin.push(var[5]);
}

void MCsim::printout(){
    varAvg[0] = Ebin.Avrg();
    varErr[0] = Ebin.Err_Avrg();
    varAvg[1] = E2bin.Avrg();
    varErr[1] = E2bin.Err_Avrg();
    varAvg[2] = E4bin.Avrg();
    varErr[2] = E4bin.Err_Avrg();
    varAvg[3] = Mbin.Avrg();
    varErr[3] = Mbin.Err_Avrg();
    varAvg[4] = M2bin.Avrg();
    varErr[4] = M2bin.Err_Avrg();
    varAvg[5] = M4bin.Avrg();
    varErr[5] = M4bin.Err_Avrg();

    cout << "<E> = " << varAvg[0] << " +- " << varErr[0] << endl;
    cout << "<E^2> = " << varAvg[1] << " +- " << varErr[1] << endl;
    cout << "<E^4> = " << varAvg[2] << " +- " << varErr[2] << endl;
    cout << "<M> = " << varAvg[3] << " +- " << varErr[3] << endl;
    cout << "<M^2> = " << varAvg[4] << " +- " << varErr[4] << endl;
    cout << "<M^4> = " << varAvg[5] << " +- " << varErr[5] << endl;
}

void MCsim::SQIsing(int NWarmup, int Nmeas, int NStep){
    MCsweeps(NWarmup);
    for(int i = 0; i < Nmeas; i++){
        MCsweeps(NStep);
        do_measurement();
    }
    printout();
}
