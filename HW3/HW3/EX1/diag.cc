#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Row; // One row of the matrix
typedef vector<Row> Matrix; // Matrix: a vector of rows. Notice that since each element of A is a row, Anm = Matrix[n][m]

// Find sign of a number (modified from the lecture notes)
int sgn(double val){
    return int((val>0)-(val<0));
}

void jacdiag(Matrix & A, vector<double> & d){
    d.clear();
    int size = A.size();
    for(int i = 0; i < 10; i++){
        for(int p = 0; p < size-1; p++){
            for(int q = p+1; q < size; q++){
                if(fabs(A[p][q]) > 0.00000000000000022){
                    // Compute variabes for calculation
                    double alpha = (A[q][q]-A[p][p])/(2*A[p][q]);
                    double t = sgn(alpha)/(fabs(alpha)+sqrt(pow(alpha,2)+1));
                    double c = 1/sqrt(pow(t,2)+1);
                    double s = t*c;
                    // Save these values so we don't use the new value
                    // in a later calculation
                    double Apq = A[p][q];
                    double App = A[p][p];
                    double Aqq = A[q][q];
                    // Essentially we march along the p and q columns
                    // and row, with special calculations for (p,p),
                    // (q,q) and (p,q)
                    for(int k = 0; k < size; k++){
                        if(k == p){
                            A[p][p] = pow(c,2)*App+pow(s,2)*Aqq-2*s*c*Apq;
                            A[p][q] = 0;
                            A[q][p] = 0;
                        } else if (k == q){
                            A[q][q] = pow(s,2)*App+pow(c,2)*Aqq+2*s*c*Apq;
                        } else {
                            // Save old values so new values don't
                            // change calculation
                            double Akp = A[k][p];
                            double Akq = A[k][q];
                            double Apk = A[p][k];
                            double Aqk = A[q][k];
                            A[p][k] = c*Apk-s*Aqk;
                            A[q][k] = s*Apk+c*Aqk;
                            A[k][p] = c*Akp-s*Akq;
                            A[k][q] = s*Akp+c*Akq;
                        }
                    }
                }
            }
        }
        // Sum of squares of upper diagonal
        double sumsq = 0;
        for(int p = 0; p < size-1; p++){
            for(int q = p+1; q < size; q++){
                sumsq += pow(A[p][q],2);
            }
        }
        cout << "Sum of Squares: " << sumsq << endl;
    }
    for(int i = 0; i < size; i++){
        d.push_back(A[i][i]);
    }
}

void jacuppdiag(Matrix & A, vector<double> & d){
    d.clear();
    int size = A.size();
    for(int i = 0; i < 10; i++){
        for(int p = 0; p < size-1; p++){
            for(int q = p+1; q < size; q++){
                if(fabs(A[p][q]) > 0.00000000000000022){
                    // Compute variables for the calculations
                    double alpha = (A[q][q]-A[p][p])/(2*A[p][q]);
                    double t = sgn(alpha)/(fabs(alpha)+sqrt(pow(alpha,2)+1));
                    double c = 1/sqrt(pow(t,2)+1);
                    double s = t*c;
                    double tau = s/(1+c);
                    // Create a copy of A so that the newly calculated
                    // values don't affect calculaitons down the line
                    Matrix copy (A);
                    // Note that all these calculation stop at the
                    // main diagonal and their values are reflected
                    // over the diagonal. March down p and q columns
                    for(int k = 0; k < q; k++){
                        if(k < p){
                            A[k][p] = copy[k][p]-s*(copy[k][q]+tau*copy[k][p]);
                            A[k][q] = copy[k][q]+s*(copy[k][p]-tau*copy[k][q]);
                            A[p][k] = A[k][p];
                            A[q][k] = A[k][q];
                        } else {    // When k > p only q column is above diagonal
                            A[k][q] = copy[k][q]+s*(copy[k][p]-tau*copy[k][q]);
                            A[q][k] = A[k][q];
                        }
                    }
                    // March along p and q rows
                    for(int k = size-1; k > p; k--){
                        if(k > q){
                            A[p][k] = copy[p][k]-s*(copy[q][k]+tau*copy[p][k]);
                            A[q][k] = copy[q][k]+s*(copy[p][k]-tau*copy[q][k]);
                            A[k][p] = A[p][k];
                            A[k][q] = A[q][k];
                        } else {    // When k < q only p row is above diagonal
                            A[p][k] = copy[p][k]-s*(copy[q][k]+tau*copy[p][k]);
                            A[k][p] = A[p][k];
                        }
                    A[p][p] = copy[p][p]-t*copy[p][q];
                    A[q][q] = copy[q][q]+t*copy[p][q];
                    A[p][q] = 0;
                    A[q][p] = 0;
                    }
                }
            }
        }
        // Calculate sum of squares of upper diagonal
        double sumsq = 0;
        for(int p = 0; p < size-1; p++){
            for(int q = p+1; q < size; q++){
                sumsq += pow(A[p][q],2);
            }
        }
        cout << "Sum of Squares: " << sumsq << endl;
    }
    for(int i = 0; i < size; i++){
        d.push_back(A[i][i]);
    }
}
