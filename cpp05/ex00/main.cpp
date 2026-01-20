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
	catch (std::exception& e)  // std::exception base class'ı yakalıyor
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test 2: Grade çok yüksek (0 < 1) - GradeTooHighException fırlatmalı
	std::cout << "\n=== Test 2: Grade Too High ===" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 0);  // Constructor'da exception fırlatılır
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test 3: Grade çok düşük (151 > 150) - GradeTooLowException fırlatmalı
	std::cout << "\n=== Test 3: Grade Too Low ===" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 151);  // Constructor'da exception fırlatılır
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test 4: Grade increment (grade sayısı azalır, rütbe yükselir)
	// 2 -> 1 (ok), 1 -> 0 (exception)
	std::cout << "\n=== Test 4: Increment Grade ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;
		alice.incrementGrade();  // 2 -> 1
		std::cout << "After increment: " << alice << std::endl;
		alice.incrementGrade();  // 1 -> 0 = Exception!
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test 5: Grade decrement (grade sayısı artar, rütbe düşer)
	// 149 -> 150 (ok), 150 -> 151 (exception)
	std::cout << "\n=== Test 5: Decrement Grade ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 149);
		std::cout << charlie << std::endl;
		charlie.decrementGrade();  // 149 -> 150
		std::cout << "After decrement: " << charlie << std::endl;
		charlie.decrementGrade();  // 150 -> 151 = Exception!
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
