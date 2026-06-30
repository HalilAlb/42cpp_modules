#include "Bureaucrat.hpp"
#include <iostream>

int main()
{

	std::cout << "=== Test 1: Valid Bureaucrat ===" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;
	}
	catch (std::exception& e) 
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Grade Too High ===" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 0); 
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Grade Too Low ===" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 151); 
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Increment Grade ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;
		alice.incrementGrade();  
		std::cout << "After increment: " << alice << std::endl;
		alice.incrementGrade();  
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Decrement Grade ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 149);
		std::cout << charlie << std::endl;
		charlie.decrementGrade(); 
		std::cout << "After decrement: " << charlie << std::endl;
		charlie.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
