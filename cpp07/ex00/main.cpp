#include "whatever.hpp"

#include <iostream>
#include <string>


int main(void)
{
	int a = 2;
	int b = 3;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;


	
	std::cout << "\n--- Eşitlik testi ---" << std::endl;
	int x = 5;
	int y = 5;
	const int& m = ::min(x, y);
	const int& M = ::max(x, y);
	std::cout << "min(x, y) == &y ? " << (&m == &y ? "yes" : "no") << std::endl;
	std::cout << "max(x, y) == &y ? " << (&M == &y ? "yes" : "no") << std::endl;

	return 0;
}
