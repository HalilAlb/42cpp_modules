#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Test 1: Creating a valid form ===" << std::endl;
	try
	{
		Form taxReport("TaxReport", 50, 25);
		std::cout << taxReport << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 2: Invalid form grade (too high, 0 < 1) ===" << std::endl;
	try
	{
		Form invalid("Invalid", 0, 50);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 3:Invalid form grade (too low, 151 > 150) ===" << std::endl;
	try
	{
		Form invalid("Invalid", 50, 151);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 4:A bureaucrat of sufficient rank signs the form. ===" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 10);
		Form contract("Contract", 50, 25);  
		std::cout << "Before: " << contract << std::endl;
		boss.signForm(contract);
		std::cout << "After:  " << contract << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 5:An insufficiently ranked bureaucrat cannot sign. ===" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 100);  
		Form contract("ImportantContract", 50, 25);
		intern.signForm(contract);  
		std::cout << "After:  " << contract << std::endl;  
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 6:Boundary case — rank on the verge of full signature ===" << std::endl;
	try
	{
		Bureaucrat exact("Exact", 50);  
		Form form("EdgeCase", 50, 25);
		exact.signForm(form);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	std::cout << "\n=== Test 7:beSigned direct call (signForm bypass) ===" << std::endl;
	
	try
	{
		Bureaucrat weak("Weak", 100);
		Form strong("StrongForm", 10, 5);
		strong.beSigned(weak);  
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception (direct beSigned): " << e.what() << std::endl;
	}

	return 0;
}
