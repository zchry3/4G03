#include <cmath>
#include <vector>
#include <random>
#include "hv.h"
#include "Lan.h"
using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

inline double dotprod(const vector<double>& y, const vector<double>& x){
    double sum = 0.0;
    for (int i=0;i<y.size();i++)
        sum += x[i]*y[i];
    return (sum);
}

void makelan(Matrix& Lan, int m, int N, int L){
    // define the geneator without seeding
    mt19937 generator;
    uniform_real_distribution<double> distribution(0,1.0);

    Lan.clear();
    for (int i = 0; i < m; i++){
        Row row(m,0);
        Lan.push_back(row);
    }
    vector<double> v1(N),v2(N),omega(N);
    vector<double> alpha, beta;  

    for (int i=0;i<N;i++){
        v1[i] = 1.0-2.0*distribution(generator);
        v2[i] = 0.0;
    }
    double mag = sqrt(dotprod(v1, v1));
    for (int i = 0; i < N; i++){
        v1[i] = v1[i]/mag;
    }
    hv(omega, v1, L);
    alpha.push_back(dotprod(v1, omega));
    beta.push_back(sqrt(dotprod(omega, omega)-pow(alpha[0],2)));
    for(int i = 0; i < N; i++){
        v2[i] = (omega[i]-alpha[0]*v1[i])/beta[0];
    }
    for (int i = 1; i < m-1; i++){
        hv(omega, v2, L);
        for (int j = 0; j < N; j++){
            omega[j] = omega[j] - beta[i-1]*v1[j];
        }
        alpha.push_back(dotprod(v2, omega));
        beta.push_back(sqrt(dotprod(omega,omega)-pow(alpha[i],2)));
        for (int j = 0; j < N; j++){
            v1[j] = v2[j];
            v2[j] = (omega[j] - alpha[i]*v1[j])/beta[i];
        }
    }
    for (int i = 0; i < m; i++){
        if ((i>0)&&(i<m-1)){
            Lan[i][i-1] = beta[i-1];
            Lan[i][i] = alpha[i];
            Lan[i][i+1] = beta[i];
        } else if (i == 0){
            Lan[i][i] = alpha[i];
            Lan[i][i+1] = beta[i];
        } else {
            Lan[i][i-1] = beta[i-1];
            Lan[i][i] = alpha[i];
        }
    }
}
