#include "ShrubberyCreationForm.hpp"
#include <fstream>


ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
}


ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
		AForm::operator=(other);
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

const std::string& ShrubberyCreationForm::getTarget() const
{
	return _target;
}




void ShrubberyCreationForm::executeAction() const
{
	const std::string filename = _target + "_shrubbery";
	std::ofstream out(filename.c_str());
	if (!out.is_open())
	{
		
		
		std::cerr << "ShrubberyCreationForm: could not open file '"
				  << filename << "'" << std::endl;
		return;
	}
	out << "       _-_\n"
		   "    /~~   ~~\\\n"
		   " /~~         ~~\\\n"
		   "{               }\n"
		   " \\  _-     -_  /\n"
		   "   ~  \\\\ 		   "
		   "_- -   | | _- _\n"
		   "  _ -  | |   -_\n"
		   "      			 "
		   "\n"
		   "        ___\n"
		   "    .-9 9 `\\\n"
		   "  =(:(::)=  ;\n"
		   "    ||||     \\\n"
		   "    ||||      `-.\n"
		   "   ,\\|\\|         `,\n"
		   "  /                \\\n"
		   " ;                  `-.\n"
		   "|                     \\\n"
		   ";                  |   |\n";
}
