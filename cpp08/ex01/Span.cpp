#include "Span.hpp"

#include <algorithm>   
#include <numeric>     

Span::Span() : _capacity(0), _numbers()
{
}

Span::Span(unsigned int n) : _capacity(n), _numbers()
{
	
	_numbers.reserve(n);
}

Span::Span(const Span& other) : _capacity(other._capacity), _numbers(other._numbers)
{
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_capacity = other._capacity;
		_numbers  = other._numbers;
	}
	return *this;
}

Span::~Span()
{
}


void Span::addNumber(int n)
{
	if (_numbers.size() >= _capacity)
		throw SpanFullException();
	_numbers.push_back(n);
}








int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughElementsException();

	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	std::vector<int> diffs(sorted.size());
	std::adjacent_difference(sorted.begin(), sorted.end(), diffs.begin());
	
	

	return *std::min_element(diffs.begin() + 1, diffs.end());
}




int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughElementsException();

	int minV = *std::min_element(_numbers.begin(), _numbers.end());
	int maxV = *std::max_element(_numbers.begin(), _numbers.end());
	return maxV - minV;
}


std::size_t Span::size() const
{
	return _numbers.size();
}


const char* Span::SpanFullException::what() const throw()
{
	return "Span: container is full";
}

const char* Span::NotEnoughElementsException::what() const throw()
{
	return "Span: need at least 2 elements to compute a span";
}
