#include"vec.h"
#include<iostream>

int main(){
	pp::vec a {1, 2, 3};
	a.x = 5;
	pp::vec b {100, 0, 10};
	std::cout << "Dot product of " << a << " and " << b << " is: " << pp::dot(a, b) << "\n";
	
	std::cout << "Cross product of " << a << " and " << b << " is " << pp::cross(a,b) << "\n";
	std::cout << "Norm of " << a << " is " << pp::norm(a) << "\n";

	std::cout << (a*3.14) << "\n";

	std::cout << (a+=b) << "\n";

	pp::vec c(b);
	std::cout << c << " == " << b << " ? \n";

	return 0;
}
		
