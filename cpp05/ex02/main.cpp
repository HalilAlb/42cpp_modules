#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <cstdlib>  
#include <ctime>    
#include <iostream>

int main()
{
	
	std::srand(static_cast<unsigned int>(std::time(NULL)));


	std::cout << "=== Test 1: ShrubberyCreationForm — successful execution ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);          
		ShrubberyCreationForm form("garden"); 
		boss.signForm(form);
		boss.executeForm(form);
		
	}


	std::cout << "\n=== Test 2: Attempt to execute an unsigned form ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm form("nogarden");
		boss.executeForm(form);  
	}


	std::cout << "\n=== Test 3: Attempt to execute with insufficient rank ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		Bureaucrat weak("Weak", 150);
		ShrubberyCreationForm form("tree");
		boss.signForm(form);            
		weak.executeForm(form);         
	}


	std::cout << "\n=== Test 4: RobotomyRequestForm — a few trials (random 50%) ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm form("Bender");
		boss.signForm(form);
		for (int i = 0; i < 4; ++i)
			boss.executeForm(form);
	}


	std::cout << "\n=== Test 5: PresidentialPardonForm —  successful execute ===" << std::endl;
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm form("Arthur Dent");
		president.signForm(form);
		president.executeForm(form);
	}


	std::cout << "\n=== Test 6:Insufficient rank to sign the Presidential Pardon Form ===" << std::endl;
	{
		Bureaucrat lowRank("LowRank", 100);
		PresidentialPardonForm form("Marvin");
		lowRank.signForm(form);          
		lowRank.executeForm(form);       
	}


	std::cout << "\n=== Test 7: Use of polymorphic AForm* ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		AForm* forms[3];
		forms[0] = new ShrubberyCreationForm("base_via_ptr");
		forms[1] = new RobotomyRequestForm("Zaphod");
		forms[2] = new PresidentialPardonForm("Trillian");
		for (int i = 0; i < 3; ++i)
		{
			std::cout << *forms[i] << std::endl;
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
		}
		
		for (int i = 0; i < 3; ++i)
			delete forms[i];
	}


	std::cout << "\n=== Test 8:AForm cannot be instantiated directly (compile-time check) ===" << std::endl;
	
	std::cout << "AForm abstract — If the instantiation line is commented out, it is prevented at compile time."
			  << std::endl;

	return 0;
}
