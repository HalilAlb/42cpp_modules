#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;
	static const int	HIGHEST_GRADE = 1;
	static const int	LOWEST_GRADE = 150;

	void				validateGrade(int grade) const;

public:

	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();


	const std::string&	getName() const;
	int					getGrade() const;

	// Dikkat: increment = grade azalır (1'e doğru), decrement = grade artar (150'ye doğru)
	void				incrementGrade();
	void				decrementGrade();

	// Nested exception classes - std::exception'dan türetilmeli
	// Orthodox Canonical Form'a gerek yok (PDF'de belirtilmiş)
	class GradeTooHighException : public std::exception
	{
	public:
		// what() fonksiyonu override edilmeli, throw() = exception güvenliği
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

// << operatörünü overload ediyoruz (class dışında tanımlanmalı)
// Format: <name>, bureaucrat grade <grade>.
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif
