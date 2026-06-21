#include<vector>
#include <cassert>
#include "LS.h"

namespace pp{
int binsearch(const std::vector<double>& x, double z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1]);
	int i=0; 
    int j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}


double linterp(const std::vector<double>& x, const std::vector<double>& y, double z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

double linterpInteg(const std::vector<double>& x, const std::vector<double>& y, double z){
    int i = binsearch(x,z);
    double sum = 0;

    // integrate full intervals
    for(int k=0; k<i; k++){
        double dx = x[k+1]-x[k];
        sum += (y[k] + y[k+1]) * dx / 2;
    }

    // integrate last partial interval
    double dx = x[i+1]-x[i];
    double dy = y[i+1]-y[i];
    double slope = dy/dx;

    double yz = y[i] + slope*(z - x[i]); // value at z
    sum += (y[i] + yz) * (z - x[i]) / 2;

    return sum;
}

double quar(const std::vector<double>& x, const std::vector<double>& y, double z){  
}
qspline::qspline(const std::vector<double>& xs,
                 const std::vector<double>& ys){
    x=xs;
    y=ys;

    int n=x.size();

    b.resize(n-1);
    c.resize(n-1);

    std::vector<double> dx(n-1),p(n-1);

    for(int i=0;i<n-1;i++){
        dx[i]=x[i+1]-x[i];
        p[i]=(y[i+1]-y[i])/dx[i];
    }

    c[0]=0;

    /* forward recursion */

    for(int i=0;i<n-2;i++){
        c[i+1]=(p[i+1]-p[i]-c[i]*dx[i])/dx[i+1];
    }

    /* last condition */

    c[n-2]/=2;

    /* backward recursion */

    for(int i=n-3;i>=0;i--){
        c[i]=(p[i+1]-p[i]-c[i+1]*dx[i+1])/dx[i];
    }

    for(int i=0;i<n-1;i++)
        b[i]=p[i]-c[i]*dx[i];
}

double qspline::eval(double z) const{
    int i=binsearch(x,z);
    double h=z-x[i];
    return y[i]+b[i]*h+c[i]*h*h;
}

double qspline::deriv(double z) const{
    int i=binsearch(x,z);
    double h=z-x[i];
    return b[i]+2*c[i]*h;
}

double qspline::integ(double z) const{
    int i=binsearch(x,z);

    double sum=0;

    for(int k=0;k<i;k++){
        double dx=x[k+1]-x[k];
        sum+=y[k]*dx
            +b[k]*dx*dx/2
            +c[k]*dx*dx*dx/3;
    }

    double h=z-x[i];

    sum+=y[i]*h
        +b[i]*h*h/2
        +c[i]*h*h*h/3;

    return sum;
}
}