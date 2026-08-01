#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <exception>



Base* generate(void)
{
	int r = std::rand() % 3;
	switch (r)
	{
		case 0:  return new A();
		case 1:  return new B();
		default: return new C();
	}
}



void identify(Base* p)
{
	if (dynamic_cast<A*>(p)) { std::cout << "A" << std::endl; return; }
	if (dynamic_cast<B*>(p)) { std::cout << "B" << std::endl; return; }
	if (dynamic_cast<C*>(p)) { std::cout << "C" << std::endl; return; }
	std::cout << "Unknown" << std::endl;  
}




void identify(Base& p)
{
	try
	{
		
		
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::exception&) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::exception&) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::exception&) {}

	std::cout << "Unknown" << std::endl;
}


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== 6 rastgele instance — pointer & reference ile identify ===" << std::endl;
	for (int i = 0; i < 6; ++i)
	{
		Base* b = generate();
		std::cout << "Instance " << i << ": ";
		std::cout << "ptr→";
		identify(b);
		std::cout << "          ref→";
		identify(*b);
		delete b;
	}


	std::cout << "\n=== Edge case: identify(NULL ptr) ===" << std::endl;
	identify(static_cast<Base*>(NULL));
	
	

	return 0;
}
