#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(LOWEST_GRADE)
{
}


Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	// Constructor'da grade kontrolü yapmamız gerekiyor
	validateGrade(grade);
}

// Copy constructor - deep copy yapıyoruz
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		// Önemli: _name const olduğu için yeniden atanamaz
		// Sadece _grade'i kopyalayabiliriz
		_grade = other._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat()
{
}


const std::string& Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

// Dikkat: Grade 1 = en yüksek, Grade 150 = en düşük

void Bureaucrat::incrementGrade()
{
	// Increment = grade değeri azalır (daha iyi pozisyona yükselir)
	validateGrade(_grade - 1);  // Önce kontrol et, sonra değiştir
	_grade--;
}

void Bureaucrat::decrementGrade()
{
	// Decrement = grade değeri artar (daha kötü pozisyona düşer)
	validateGrade(_grade + 1);  // Önce kontrol et, sonra değiştir
	_grade++;
}

// Private helper function - DRY prensibi (Don't Repeat Yourself)
// Grade kontrolünü tek bir yerde yap
void Bureaucrat::validateGrade(int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();  // Exception fırlatıyoruz
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();   // Exception fırlatıyoruz
}

// Exception classes - what() fonksiyonunu implement ediyoruz

// what() override - exception mesajı döndürür
// throw() = bu fonksiyon exception fırlatmaz garantisi (C++98)
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high! (minimum grade is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low! (maximum grade is 150)";
}


std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
	return out;
}
