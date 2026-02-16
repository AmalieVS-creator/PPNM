#include<cmath>
#include<iostream>
#include"calc.h"

int calc(){
	double sqrt2=std::sqrt(2.0);
	std::cout << "sqrt(2) = " << sqrt2 << std::endl;

	double power2=std::pow(2,1.5);
	std::cout << "power(2) = " << power2 << std::endl;

	const double EulerConstant = std::exp(1.0);
	const double Pi = 3.14159265358979323846;
	double epi=pow(EulerConstant,Pi);
	std::cout << "e(pi) = " << epi << std::endl;

	double pie=pow(Pi, EulerConstant);
	std::cout << "pi(e) = " << pie << std::endl;
	
	return 0;
} 
