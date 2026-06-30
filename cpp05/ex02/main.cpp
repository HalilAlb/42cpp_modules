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


	std::cout << "=== Test 1: ShrubberyCreationForm — başarılı execute ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);          
		ShrubberyCreationForm form("garden"); 
		boss.signForm(form);
		boss.executeForm(form);
		
	}


	std::cout << "\n=== Test 2: İmzasız form execute denemesi ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm form("nogarden");
		boss.executeForm(form);  
	}


	std::cout << "\n=== Test 3: Yetersiz rütbe ile execute denemesi ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		Bureaucrat weak("Weak", 150);
		ShrubberyCreationForm form("tree");
		boss.signForm(form);            
		weak.executeForm(form);         
	}


	std::cout << "\n=== Test 4: RobotomyRequestForm — birkaç deneme (random %50) ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm form("Bender");
		boss.signForm(form);
		for (int i = 0; i < 4; ++i)
			boss.executeForm(form);
	}


	std::cout << "\n=== Test 5: PresidentialPardonForm — başarılı execute ===" << std::endl;
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm form("Arthur Dent");
		president.signForm(form);
		president.executeForm(form);
	}


	std::cout << "\n=== Test 6: PresidentialPardonForm sign için yetersiz rütbe ===" << std::endl;
	{
		Bureaucrat lowRank("LowRank", 100);
		PresidentialPardonForm form("Marvin");
		lowRank.signForm(form);          
		lowRank.executeForm(form);       
	}


	std::cout << "\n=== Test 7: Polymorphic AForm* kullanımı ===" << std::endl;
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


	std::cout << "\n=== Test 8: AForm direkt instantiate edilemez (compile-time check) ===" << std::endl;
	
	std::cout << "AForm abstract — instantiate satırı yorumda, derleme zamanı engellenir."
			  << std::endl;

	return 0;
}
