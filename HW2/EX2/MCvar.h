#pragma once
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

template <class Type> class MCvar {
// Data
public:

private:
	int bin_size;
        int count;
        int no_of_bins;
	Type av;
	vector<double> Bins;  
//Methods
public:
        MCvar() : bin_size(1000),count(0),no_of_bins(0) {}
        MCvar(int bsz) : bin_size(bsz),count(0),no_of_bins(0) {}
        void push(const Type v)
	{ 
                if (count == 0) {
                        av = v;
                        count += 1;
                }else if (count < bin_size-1) {
                        av += v;
                        count += 1;
                }else {
                        av += v;
                        Bins.push_back(((double) av)/bin_size);
                        count = 0;
                        no_of_bins += 1;
                }
        }
        double Avrg()
	{ 
                double res = 0.0;
                for (auto r : Bins) res += r;
                return (res/no_of_bins);
        }
        double Err_Avrg()
	{ 
                double res = 0.0,res2=0.0;
                for (auto r : Bins) {
                    res += r;
                    res2 += pow(r, 2);
                }
                double avg = res/no_of_bins;
                double sq_avg = res2/no_of_bins;
                return sqrt((sq_avg-pow(avg,2))/(no_of_bins-1));
        }
};
