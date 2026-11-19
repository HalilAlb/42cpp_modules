#include "RPN.hpp"

#include <stack>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}
RPN::RPN(const RPN&) {}
RPN& RPN::operator=(const RPN&) { return *this; }
RPN::~RPN() {}


namespace
{
	
	
	void applyOp(std::stack<int>& s, char op)
	{
		if (s.size() < 2)
			throw std::runtime_error("Error");

		int b = s.top(); s.pop();
		int a = s.top(); s.pop();
		int result;

		switch (op)
		{
			case '+': result = a + b; break;
			case '-': result = a - b; break;
			case '*': result = a * b; break;
			case '/':
				if (b == 0)
					throw std::runtime_error("Error");
				result = a / b;
				break;
			default:
				throw std::runtime_error("Error");
		}
		s.push(result);
	}
}


int RPN::evaluate(const std::string& expression)
{
	std::stack<int> s;

	for (std::size_t i = 0; i < expression.size(); ++i)
	{
		char c = expression[i];

		if (c == ' ') continue;

		
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			s.push(c - '0');
			continue;
		}

		
		if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			applyOp(s, c);
			continue;
		}

		
		throw std::runtime_error("Error");
	}

	if (s.size() != 1)
		throw std::runtime_error("Error");  

	return s.top();
}
