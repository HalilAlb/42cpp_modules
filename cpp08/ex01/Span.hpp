#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <cstddef>
#include <iterator>   








class Span
{
private:
	unsigned int		_capacity;
	std::vector<int>	_numbers;

public:

	Span();                                   
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	
	void	addNumber(int n);

	
	
	
	template <typename InputIt>
	void	addRange(InputIt first, InputIt last);

	
	
	int		shortestSpan() const;

	
	int		longestSpan() const;

	std::size_t	size() const;


	class SpanFullException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class NotEnoughElementsException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};



template <typename InputIt>
void Span::addRange(InputIt first, InputIt last)
{
	
	std::size_t addCount = static_cast<std::size_t>(std::distance(first, last));
	if (_numbers.size() + addCount > _capacity)
		throw SpanFullException();
	_numbers.insert(_numbers.end(), first, last);
}

#endif
