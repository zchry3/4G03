#include "bessel.h"

// Calculate J_n(0.5) for n>=2 using the recursive formula J_(n+1)(x) =
// (2n/x)*J_n(x) - J_(n-1)(x) for x = 0.5
double bessel_ascending(int n_max){
    double prev_term = 0.938469807240813; // J_0(0.5)
    double current_term = 0.2422684577; // J_1(0.5)
    // We start with values of J_0 and J_1, so we just return those if
    // asked for
    if(n_max==0){
        return prev_term;
    } else if(n_max==1){
        return current_term;
    } else {
        // Compute recurrence relationship up to J_n(0.5)
        for(int n=1;n<n_max;n++){
            // J_(n+1)(0.5) = 4*n*J_n(0.5) - J_(n-1)(0.5)
            double next_term = 4*n*current_term - prev_term;
            prev_term = current_term;
            current_term = next_term;
        }
        return current_term;
    }
}

// Calculate J_n(x) using the recursive formula J_(n-1)(x) =
// (2n/x)*J_n(x) - J_(n+1)(x) with initial conditions J_N(x) = 1 for N
// >> n and J_m(x) = 0 for m>N. After computing the recurrence
// relation values they are then normalized using the relation J_0(x)
// + 2*(sum from n=1 to infinity of J_2n(x)) = 1.
double bessel_descending(int n, double x){
    // Pick a sufficiently large N and generate an array of length N+2
    // (this holds J_0(x) to J_(N+1)(x), hence N+2 values)
    int n_max = 2*(n+x) + 10;
    double bessel_values [n_max+2];
    //Initial conditions on J_N and J_(N+1)
    bessel_values[n_max+1] = 0;
    bessel_values[n_max] = 1;
    // Use recurrence relationship to compute down to J_0(x)
    for(int i=n_max-1;i>=0;i--){
        bessel_values[i] = (2*(i+1)/x)*bessel_values[i+1] - bessel_values[i+2];
    }
    // Calculate norm given by J_0 + 2*(sum n=1 to inf J_2n) = 1
    double norm = bessel_values[0];
    for(int i=1;i<=(n_max/2);i++){
        norm += 2*bessel_values[2*i];
    }
    // Return normalized value
    return bessel_values[n]/norm;
}
