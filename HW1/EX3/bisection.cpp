#include "../EX2/bessel.h"
#include "bisection.h"

// Find sign of a number (modified from the lecture notes)
int sgn(double val){
    return int((val>0)-(val<0));
}

// Use bisection to locate root 1, 2, or 3 of J_0(x)
double bisection(int root, double width){
    double a; // Left hand bound
    double b; // Right hand bound
    // Because of the scope of the problem we can hard code the
    // initial interval boundaries for the first 3 roots
    if (root == 1){
        a = 2;
        b = 3;
    } else if (root == 2){
        a = 5;
        b = 6;
    } else if (root == 3){
        a = 8;
        b = 9;
    }
    // Iteratively halve the length of the interval, choosing the
    // bounds contain a sign change (and thus a root), until diff <
    // width
    double diff = b-a;
    while(diff > width){
        double mid_point = (a+b)/2;
        // Since we know for sure our interval contains one and only
        // one root, and that the function is monotonic between the bounds, we only
        // need to check the end points of the leftmost interval. If it's not in the
        // leftmost interval then we know by default it must be in the
        // other interval.
        if (sgn(bessel_descending(0,a)) != sgn(bessel_descending(0,mid_point))){
            b = mid_point;
        } else {
            a = mid_point;
        }
        diff = b-a;
    }
    return (a+b)/2;
}
