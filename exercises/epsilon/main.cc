#include<iostream>
#include"machine.h"
#include"addition.h"
#include"doubles.h"
#include<iomanip>

int main(){
	machine();
	addition();
	
	double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
	double d2 = 8*0.1;
	
	std::cout << "d1==d2?" << (d1==d2 ? "true":"false") << "\n";

	std::cout << "approx(d1==d2)?" << (approx(d1,d2) ? "true":"false") << "\n";

	std::cout << std::fixed << std::setprecision(17);
	std::cout << "d1=" << d1 << "\n";
	std::cout << "d2=" << d2 << "\n";
	return 0;

}

