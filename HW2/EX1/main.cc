#include <iostream>
#include <cmath>
#include <random>
#include "monte_carlo.h"
using namespace std;

double function(double x){
    return exp(-pow(x,2));
}

double generator(double x, double xmax){
    return -log(1-x*(exp(xmax)-1)/exp(xmax));
}

double weight(double x, double xmax){
    return exp(-x)*exp(xmax)/(exp(xmax)-1);
}

int main(){
    random_device r; // Seed with a real random device
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 engine(seed);

    double real_value = 0.7468241328124270253994674361318530053544996868126063290276544989;
    double integral = monte_carlo(function, [](double x)->double{return x;}, [](double x)->double{return 1;}, engine, 5000);
    cout << "Regular MC: Iterations: 5000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,1);}, [](double x)->double{return weight(x,1);}, engine, 5000);
    cout << "Importance Sampling: Iterations: 5000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return x;}, [](double x)->double{return 1;}, engine, 500000);
    cout << "Regular MC: Iterations: 500000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,1);}, [](double x)->double{return weight(x,1);}, engine, 500000);
    cout << "Importance Sampling: Iterations: 500000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return x;}, [](double x)->double{return 1;}, engine, 5000000);
    cout << "Regular MC: Iterations: 5000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,1);}, [](double x)->double{return weight(x,1);}, engine, 5000000);
    cout << "Importance Sampling: Iterations: 5000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return x;}, [](double x)->double{return 1;}, engine, 10000000);
    cout << "Regular MC: Iterations: 10000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,1);}, [](double x)->double{return weight(x,1);}, engine, 10000000);
    cout << "Importance Sampling: Iterations: 10000000 Value: " << integral << " Error: " << real_value-integral << endl << endl;

    real_value = 0.8862269254527580136490837416705725913987747262103196339027644347;
    integral = monte_carlo(function, [](double x)->double{return 10*x;}, [](double x)->double{return 1.0/10.0;}, engine, 5000);
    cout << "Regular MC: Iterations: 5000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,10);}, [](double x)->double{return weight(x,10);}, engine, 5000);
    cout << "Importance Sampling: Iterations: 5000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return 10*x;}, [](double x)->double{return 1.0/10.0;}, engine, 500000);
    cout << "Regular MC: Iterations: 500000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,10);}, [](double x)->double{return weight(x,10);}, engine, 500000);
    cout << "Importance Sampling: Iterations: 500000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return 10*x;}, [](double x)->double{return 1.0/10.0;}, engine, 5000000);
    cout << "Regular MC: Iterations: 5000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,10);}, [](double x)->double{return weight(x,10);}, engine, 5000000);
    cout << "Importance Sampling: Iterations: 5000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return 10*x;}, [](double x)->double{return 1.0/10.0;}, engine, 10000000);
    cout << "Regular MC: Iterations: 10000000 Value: " << integral << " Error: " << real_value-integral << endl;
    integral = monte_carlo(function, [](double x)->double{return generator(x,10);}, [](double x)->double{return weight(x,10);}, engine, 10000000);
    cout << "Importance Sampling: Iterations: 10000000 Value: " << integral << " Error: " << real_value-integral << endl << endl;

    return 1;
}
