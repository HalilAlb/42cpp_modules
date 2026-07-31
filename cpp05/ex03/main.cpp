#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Intern		intern;
	Bureaucrat	boss("Boss", 1);


	std::cout << "=== Test 1: PDF example — Bender for robotomy request ===" << std::endl;
	{
		AForm* rrf = intern.makeForm("robotomy request", "Bender");
		if (rrf)
		{
			boss.signForm(*rrf);
			boss.executeForm(*rrf);
			delete rrf;  
		}
	}


	std::cout << "\n=== Test 2: ShrubberyCreationForm via Intern ===" << std::endl;
	{
		AForm* form = intern.makeForm("shrubbery creation", "backyard");
		if (form)
		{
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}


	std::cout << "\n=== Test 3: PresidentialPardonForm via Intern ===" << std::endl;
	{
		AForm* form = intern.makeForm("presidential pardon", "Marvin");
		if (form)
		{
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}


	std::cout << "\n=== Test 4: unknown form name → NULL ===" << std::endl;
	{
		AForm* form = intern.makeForm("coffee request", "anyone");
		if (form == NULL)
			std::cout << "(makeForm returned NULL as expected)" << std::endl;
		else
		{
			delete form;
			std::cout << "[ERROR] expected: form is not NULL" << std::endl;
		}
	}


	std::cout << "\n=== Test 5: Empty string form name ===" << std::endl;
	{
		AForm* form = intern.makeForm("", "x");
		if (form == NULL)
			std::cout << "(An empty name is also considered unknown., NULL)" << std::endl;
		else
			delete form;
	}


	std::cout << "\n=== Test 6:Internal OCF basic check ===" << std::endl;
	{
		Intern a;
		Intern b(a);
		Intern c;
		c = a;
		AForm* f = b.makeForm("robotomy request", "copied_intern_target");
		if (f) { delete f; }
	}

	return 0;
}
