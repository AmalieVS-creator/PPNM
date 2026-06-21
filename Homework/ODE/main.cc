#include <iostream>
#include <cmath>
#include "RKE.h"
#include "matrix.h"
#include <fstream>

using namespace pp;

// harmonic oscillator: u'' = -u
int main() {
    // u'' = -u
    // something like u = cos(x)
    // let y[0] = u and y[1] = u'
    std::function<vector(double,vector)> f = [](double x, vector y){
        vector dydx(2);
        dydx[0] = y[1];   // u' = dy[0]/dx = y[1]
        dydx[1] = -y[0];  // u'' = dy[1]/dx = -y[0]
        return dydx;
    };

    double a = 0;   //start point
    double b = 3.14;  //end point

    vector y0(2);
    //start conditions
    y0[0] = 1;
    y0[1] = 0;

    auto [xlist, ylist] = driver(f, a, b, y0);

    // Print results
    /*for(size_t i = 0; i < xlist.size(); i++){
        std::cout<< xlist[i] <<" "<< ylist[i][0] <<" "<< ylist[i][1]<<"\n";
    }*/
    std::cout<<"Computing ODE: u'' = -u \n";
    std::cout<<"cos(π) = "<<std::cos(b)<<", rkstep12 at π: "<<ylist[xlist.size()-1][0]<<"\n";


	// ny funcyion

	double damping = 0.25;   //start point
    double stiff = 5.0;  //end point

	std::function<vector(double,vector)> f2 = [damping, stiff](double x, vector y){
        vector dydx(2);
        dydx[0] = y[1];   // u' = dy[0]/dx = y[1]
        dydx[1] = -damping*y[1]-stiff*std::sin(y[0]);  // u'' = dy[1]/dx = -y[0]
        return dydx;
    };

	double t0 = 0.0;
	double t_end = 10.0;

    vector y0_2(2);
    //start conditions
    y0_2[0] = 3.141-0.1;
    y0_2[1] = 0;

    auto [xlist2, ylist2] = driver(f2, t0, t_end, y0_2);

	std::ofstream file("pendulum.dat");

	for(size_t i = 0; i < xlist2.size(); i++){
		file << xlist2[i] << " "
			<< ylist2[i][0] << " "   // theta
			<< ylist2[i][1] << "\n"; // omega
	}

	file.close();

	std::cout << "Data written to pendulum.dat\n";



    // Opgave B 1

    double ep1 = 0;  //end point
    double h=0.125, acc=0.01, eps=0.01, hmin=0.01;

	std::function<vector(double,vector)> f3 = [ep1](double x, vector y){
        vector dydx(2);
        dydx[0] = y[1];   // u' = dy[0]/dx = y[1]
        dydx[1] = 1-y[0]+ep1*y[0]*y[0];  // u'' = dy[1]/dx = -y[0]
        return dydx;
    };

	double t0_1 = 0.0;
	double t_end1 = 50.0;

    vector y0_3(2);
    //start conditions
    y0_3[0] = 1;
    y0_3[1] = 0;

    auto [xlist3, ylist3] = driver(f3, t0_1, t_end1, y0_3, h, acc, eps, hmin);

    std::ofstream file1("planet1.dat");

	for(size_t i = 0; i < xlist3.size(); i++){
		file1 << xlist3[i] << " "
			<< ylist3[i][0] << " "   // theta
			<< ylist3[i][1] << "\n"; // omega
	}

	file1.close();



    // Opgave B 2

    double ep2 = 0;  //end point

	std::function<vector(double,vector)> f4 = [ep2](double x, vector y){
        vector dydx(2);
        dydx[0] = y[1];   // u' = dy[0]/dx = y[1]
        dydx[1] = 1-y[0]+ep2*y[0]*y[0];  // u'' = dy[1]/dx = -y[0]
        return dydx;
    };

	double t0_2 = 0.0;
	double t_end2 = 50.0;

    vector y0_4(2);
    //start conditions
    y0_4[0] = 1;
    y0_4[1] = -0.5;

    auto [xlist4, ylist4] = driver(f4, t0_2, t_end2, y0_4);

    std::ofstream file2("planet2.dat");

	for(size_t i = 0; i < xlist4.size(); i++){
		file2 << xlist4[i] << " "
			<< ylist4[i][0] << " "   // theta
			<< ylist4[i][1] << "\n"; // omega
	}

	file2.close();

    
    
    // Opgave B 3

    double ep3 = 0.01;  //end point

	std::function<vector(double,vector)> f5 = [ep3](double x, vector y){
        vector dydx(2);
        dydx[0] = y[1];   // u' = dy[0]/dx = y[1]
        dydx[1] = 1-y[0]+ep3*y[0]*y[0];  // u'' = dy[1]/dx = -y[0]
        return dydx;
    };

	double t0_3 = 0.0;
	double t_end3 = 50.0;

    vector y0_5(2);
    //start conditions
    y0_5[0] = 1;
    y0_5[1] = -0.5;

    auto [xlist5, ylist5] = driver(f5, t0_3, t_end3, y0_5);

    std::ofstream file3("planet3.dat");

	for(size_t i = 0; i < xlist5.size(); i++){
		file3 << xlist5[i] << " "
			<< ylist5[i][0] << " "   // theta
			<< ylist5[i][1] << "\n"; // omega
	}

	file3.close();


    // std::ofstream file1("planet.dat");

    // for(size_t i = 0; i < xlist3.size(); i++){
    //     file1 << xlist3[i] << " "
    //         << ylist3[i][0] << " "
    //         << ylist4[i][0] << " "
    //         << ylist5[i][0] << "\n";
    // }

    // file1.close();

}