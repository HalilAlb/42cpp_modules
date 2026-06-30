#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return *this; }
Intern::~Intern() {}





static AForm* makeShrubbery(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

static AForm* makeRobotomy(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

static AForm* makePresidential(const std::string& target)
{
	return new PresidentialPardonForm(target);
}




struct FormEntry
{
	const char*	name;
	AForm*		(*create)(const std::string& target);
};


AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	static const FormEntry forms[] = {
		{ "shrubbery creation", &makeShrubbery },
		{ "robotomy request",   &makeRobotomy },
		{ "presidential pardon",&makePresidential }
	};
	static const std::size_t count = sizeof(forms) / sizeof(forms[0]);

	for (std::size_t i = 0; i < count; ++i)
	{
		if (formName == forms[i].name)
		{
			AForm* created = forms[i].create(target);
			std::cout << "Intern creates " << created->getName() << std::endl;
			return created;
		}
	}

	std::cerr << "Intern: form '" << formName << "' is unknown." << std::endl;
	return NULL;
}
