#include<iostream>
#include"calc.h"
#include"sfuns.h"

int main(){
	calc();
	for (int i = 1; i <= 10; ++i) {
        std::cout << "fgamma(" << i << ") = "
                  << sfuns::fgamma(i) << std::endl;
	}
	for (int i = 1; i <= 10; ++i) {
    	std::cout << "lngamma(" << i << ") = "
		<< sfuns::lngamma(i) << std::endl;
	}
	return 0;
}

