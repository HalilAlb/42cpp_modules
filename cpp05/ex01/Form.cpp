#include "Form.hpp"
#include "Bureaucrat.hpp"  

Form::Form() : _name("Default"), _isSigned(false),
	_gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE)
{
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false),
	  _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	
	validateGrade(gradeToSign);
	validateGrade(gradeToExecute);
}

Form::Form(const Form& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}




Form& Form::operator=(const Form& other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return *this;
}

Form::~Form()
{
}


const std::string& Form::getName() const          { return _name; }
bool               Form::getIsSigned() const      { return _isSigned; }
int                Form::getGradeToSign() const   { return _gradeToSign; }
int                Form::getGradeToExecute() const{ return _gradeToExecute; }


void Form::beSigned(const Bureaucrat& bureaucrat)
{
	
	
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}


void Form::validateGrade(int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();
}




const char* Form::GradeTooHighException::what() const throw()
{
	return "Form: grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form: grade is too low!";
}


std::ostream& operator<<(std::ostream& out, const Form& form)
{
	out << "Form \"" << form.getName()
		<< "\", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute()
		<< ", signed: " << (form.getIsSigned() ? "yes" : "no");
	return out;
}
