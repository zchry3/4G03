#include <random>
#include "monte_carlo.h"
using namespace std;

double monte_carlo(double (*f)(double x), double (*generator)(double x), double (*weight)(double x), mt19937& rng, int maxiter){
    float npoints = 0.0;
    double running_sum = 0;
    uniform_real_distribution<double> dist(0, 1);
    for(int i = 0; i < maxiter; i++){
        double xrand = dist(rng);
        double weightx = generator(xrand);
        npoints += 1;
        running_sum += f(weightx)/weight(weightx);
    }
    return running_sum/npoints;
}
