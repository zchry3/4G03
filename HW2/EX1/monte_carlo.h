#include <random>
using namespace std;

double monte_carlo(double (*f)(double x), double (*generator)(double x), double (*weight)(double x), mt19937& rng, int maxiter);
