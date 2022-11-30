#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <random>
#include <chrono>
#include "Vec2D.h"
#include "params.h"
#include "MDvar.h"

using namespace std;
using namespace chrono;

struct Atom {
   Vec<double> r,vel,acc;
};

typedef high_resolution_clock myclock;

class MDsim: MDvar<double> {
// Data
private:
	vector<Atom> Particles;
	double deltaT;
 	double density;
	int initUcellx;
	int initUcelly;
	int stepAvg;
	int stepEquil;
	int stepLimit;
 	Vec<int> initUcell;
	double temperature;
	double rCut;
 	Vec<double> region;
	int nAtoms;
	double velMag;
	long int stepCount;
        int countRdf;
        MDvar<double> Etot;
        MDvar<double> Ekin;
        MDvar<double> Pressure;
        Vec<double> vSum;
        double timeNow;
        double uSum;
        double virSum;
        double vvSum;
        double sizeHistRdf;
        double rangeRdf;
        valarray<double> HistRdf;

//Methods
public:
	// constructor
        MDsim(Params & myparams):
          deltaT(myparams.deltaT),
 	  density    (myparams.density),
	  initUcellx (myparams.initUcellx),
	  initUcelly (myparams.initUcelly),
	  stepAvg    (myparams.stepAvg),
	  stepEquil  (myparams.stepEquil),
	  stepLimit  (myparams.stepLimit),
 	  initUcell  (myparams.initUcell),
	  temperature(myparams.temperature),
	  rCut       (myparams.rCut),
 	  region     (myparams.region),
	  nAtoms     (myparams.nAtoms),
	  velMag     (myparams.velMag),      
	  sizeHistRdf(myparams.sizeHistRdf),      
	  rangeRdf   (myparams.rangeRdf),      
          Particles(myparams.nAtoms),
          HistRdf(myparams.nAtoms)   {
	  //deltaT      = myparams.deltaT;
 	  //density     = myparams.density;    
	  //initUcellx  = myparams.initUcellx;
	  //initUcelly  = myparams.initUcelly;
	  //stepAvg     = myparams.stepAvg;
	  //stepEquil   = myparams.stepEquil;
	  //stepLimit   = myparams.stepLimit;
 	  //initUcell   = myparams.initUcell;
	  //temperature = myparams.temperature;
	  //rCut        = myparams.rCut;
 	  //region      = myparams.region;
	  //nAtoms      = myparams.nAtoms;
	  //velMag      = myparams.velMag;      
	  //Particles.resize(nAtoms);
        }
 
	void Initialize()
	{
	  stepCount = 0;
          countRdf = 0;
          initcoords();
          InitVels();
          initaccells();
 	}

	void SingleStep()
	{
	  stepCount += 1;
          timeNow = stepCount*deltaT;
          LeapFrogStep(1);
          ApplyBC();
          ComputeForces();
          LeapFrogStep(2);
          EvalVars();
          if (stepCount%stepAvg == 0) {
            PrintSummary();
            Etot.zero();
            Ekin.zero();
            Pressure.zero();
            HistRdf = 0.0;
            countRdf = 0;
          }
 	}

	
private:
	void PrintSummary()
	{ static bool firstcall=true;
          if (firstcall) {
            cout << "  step  timeNow  Sum Vel       E +-Std_Err(E)           Ekin +- Std_Err(Ekin)     P +- Std_Err(P)"<< endl;
            firstcall=false;
          }
          cout << fixed << setw(6) << stepCount << "  " << 
                  setw(6) << setprecision(5)  << timeNow   << "  " <<
                  setw(6) << setprecision(5) << fabs(vSum.VCsum()/nAtoms) << "       " << 
                  setw(6) << setprecision(5) << Etot.Avrg() << " +- " << 
                  setw(6) << setprecision(5) << Etot.Err_Avrg() << "       " << 
                  setw(6) << setprecision(5) << Ekin.Avrg() << " +- " << 
                  setw(6) << setprecision(5) << Ekin.Err_Avrg() << "        " << 
                  setw(6) << setprecision(5) << Pressure.Avrg() << " +- " << 
                  setw(6) << setprecision(5) << Pressure.Err_Avrg() << endl;                 
 	}


	void EvalVars()
	{ 
          vSum.set_values(0.0,0.0);
          vvSum = 0.0;
	  for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
            vSum = vSum+it->vel;
            vvSum += it->vel.VLenSQ();
	  }
          double Erg_Kin = 0.5*vvSum/nAtoms;
          Ekin.push(Erg_Kin);
          Etot.push(Erg_Kin+uSum/nAtoms);
          double P = density*(vvSum+virSum)/((double)nAtoms*NDIM);
          Pressure.push(density*(vvSum+virSum)/((double)nAtoms*NDIM));
          EvalRdf();
 	}

	void ComputeForces()
	{
          Vec<double> dr;
          double fcVal,rr,rrCut,rri,rri3;

          rrCut = rCut*rCut;
	  for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
            it->acc.set_values(0.0,0.0);
	  }
          uSum = 0.0;
          virSum = 0.0;
          for (int j1=0; j1 <= nAtoms-2; j1++) {
             for (int j2=j1+1; j2 <= nAtoms-1; j2++ ){
               dr=Particles[j1].r-Particles[j2].r;
               dr.VWrap(region);
               rr =dr.VLenSQ();
               if (rr < rrCut) {
                 rri = 1.0/rr;
                 rri3 = rri*rri*rri;
                 fcVal = 48.0*rri3*(rri3-0.5)*rri;
                 Particles[j1].acc = Particles[j1].acc+fcVal*dr;
                 Particles[j2].acc = Particles[j2].acc-fcVal*dr;
                 uSum += 4.0*rri3*(rri3-1.0)+1.0;
                 virSum += fcVal*rr;
               }
             }
          }
 	}

	void ApplyBC()
	{
	  for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
            it->r.VWrap(region); 
	  }
 	}

	void LeapFrogStep(int part)
	{
          if (part == 1) {
	    for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
               it->vel = it->vel+...
               it->r = it->r+...
	    }
          } else {
	    for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
               it->vel = it->vel+...
	    }
          }
 	}

	void randomize_vel()
	{
           myclock::time_point beginning = myclock::now();
      	   myclock::duration dur = myclock::now() - beginning;
           unsigned seed = dur.count();
	   double s;

      	   mt19937 generator(seed);
      	   uniform_real_distribution<double> distribution(0,1.0);
	   for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
	     s = distribution(generator);
	     s *= 2.0*M_PI;
	     it->vel.randomize(s);
             it->vel = (it->vel)*velMag;
	   }
	}

	void initcoords()
	{
	   Vec<double> c,gap;
	   
	   gap.VDiv(region,initUcellx,initUcell.y);
	    
	   int n=0;
	   for (int nx=0; nx <=initUcell.x-1; nx++) {
	     for (int ny=0; ny <=initUcell.y-1; ny++) {
	        c.set_values(nx+0.5,ny+0.5);
                c.scale_with(gap);
                c = c-0.5*region;
	        Particles[n].r=c;
	        n=n+1;
	     }
	   }
	}

	void InitVels()
	{
	   vSum.set_values(0.0,0.0);
	   
           randomize_vel();
	   for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
	     vSum = vSum + it->vel;
	   }
	   for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
	     it->vel = it->vel - (1.0/nAtoms)*vSum;
	   }
	}

	void initaccells()
	{
	   for (vector<Atom>::iterator it = Particles.begin() ; it != Particles.end(); ++it) {
	     it->acc.set_values(0.0,0.0);
	   }
	   
	}


    void EvalRdf(){
        Vec<double> dr;
        double deltaR, rr;
        int j1, j2, n;

        deltaR = rangeRdf / sizeHistRdf;
        for (j1 = 0; j1 < nAtoms - 1; j1 ++) {
          for (j2 = j1 + 1; j2 < nAtoms; j2 ++) {
            dr=Particles[j1].r-Particles[j2].r;
            dr.VWrap(region);
            rr =dr.VLenSQ();
            if (rr < (rangeRdf*rangeRdf)) {
               n = sqrt (rr) / deltaR;
               ++ HistRdf[n];
            }
          }
        }
        ++ countRdf;
        }

    void printRdf(){
        double rb,normFac;
        double deltaR;
        int n;

        deltaR = rangeRdf / sizeHistRdf;
        normFac = region.VProd() / (M_PI * deltaR * deltaR * 
                                   nAtoms * nAtoms * countRdf);
        for (n = 0; n < sizeHistRdf; n ++)
          HistRdf[n] *= normFac / (n - 0.5);
        cout << "  r      Radial Df" << endl;
        for (n = 0; n < sizeHistRdf; n ++) {
          rb = (n + 0.5) * rangeRdf / sizeHistRdf;
          cout << fixed << setw(6) << rb << "  " << setw(6) << setprecision(5)  << HistRdf[n]   << endl;
        }
        }



};
