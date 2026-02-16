#include<iostream>
#include<cmath>
#include<iomanip>
#include"addition.h"

int addition(){
	double epsilon=std::pow(2,-52);	
	double tiny=epsilon/2;

	double a=1+tiny+tiny; // should be 1+epsilon, that is, larger than 1, no?
	double b=tiny+tiny+1; // should be the same mathematically, no?
	
	std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
	std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
	std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
	std::cout << std::fixed << std::setprecision(17);
		std::cout << "       tiny=" << tiny << "\n";
	std::cout << "1+tiny+tiny=" << a << "\n";
	std::cout << "tiny+tiny+1=" << b << "\n";
	
	return 0;
}
