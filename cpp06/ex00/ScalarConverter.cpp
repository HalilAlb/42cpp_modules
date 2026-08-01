#include "ScalarConverter.hpp"

#include <iostream>
#include <iomanip>   
#include <cstdlib>   
#include <cmath>     
#include <climits>   
#include <cfloat>    
#include <cctype>    



ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}


namespace
{
	
	enum LiteralType { L_CHAR, L_INT, L_FLOAT, L_DOUBLE, L_PSEUDO, L_INVALID };

	
	bool isPseudoLiteral(const std::string& s)
	{
		return s == "-inff" || s == "+inff" || s == "nanf"
			|| s == "-inf"  || s == "+inf"  || s == "nan";
	}

	
	
	bool isCharLiteral(const std::string& s)
	{
		return s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0]));
	}

	
	bool isIntLiteral(const std::string& s, long& outVal)
	{
		if (s.empty()) return false;
		char* end = NULL;
		long v = std::strtol(s.c_str(), &end, 10);
		if (*end != '\0') return false;          
		if (v < INT_MIN || v > INT_MAX) return false;
		outVal = v;
		return true;
	}

	
	bool isFloatLiteral(const std::string& s, double& outVal)
	{
		if (s.length() < 2 || s[s.length() - 1] != 'f') return false;
		std::string body = s.substr(0, s.length() - 1);
		if (body.empty()) return false;
		char* end = NULL;
		double v = std::strtod(body.c_str(), &end);
		if (*end != '\0') return false;
		outVal = v;
		return true;
	}

	
	
	bool isDoubleLiteral(const std::string& s, double& outVal)
	{
		if (s.empty() || s.find('.') == std::string::npos) return false;
		char* end = NULL;
		double v = std::strtod(s.c_str(), &end);
		if (*end != '\0') return false;
		outVal = v;
		return true;
	}


	LiteralType detectType(const std::string& s, double& dVal, long& iVal)
	{
		if (isPseudoLiteral(s))       return L_PSEUDO;
		if (isCharLiteral(s))         return L_CHAR;
		if (isIntLiteral(s, iVal))    return L_INT;
		if (isFloatLiteral(s, dVal))  return L_FLOAT;
		if (isDoubleLiteral(s, dVal)) return L_DOUBLE;
		return L_INVALID;
	}


	

	void printChar(double d, bool impossible)
	{
		std::cout << "char: ";
		
		if (impossible || std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		{
			std::cout << "impossible" << std::endl;
			return;
		}
		char c = static_cast<char>(d);
		if (!std::isprint(static_cast<unsigned char>(c)))
			std::cout << "Non displayable" << std::endl;
		else
			std::cout << "'" << c << "'" << std::endl;
	}

	void printInt(double d, bool impossible)
	{
		std::cout << "int: ";
		if (impossible || std::isnan(d) || std::isinf(d)
			|| d < static_cast<double>(INT_MIN)
			|| d > static_cast<double>(INT_MAX))
		{
			std::cout << "impossible" << std::endl;
			return;
		}
		std::cout << static_cast<int>(d) << std::endl;
	}

	
	
	void printFloat(double d, bool isNan, int infSign)
	{
		std::cout << "float: ";
		if (isNan)         { std::cout << "nanf"  << std::endl; return; }
		if (infSign != 0)  { std::cout << (infSign > 0 ? "+inff" : "-inff") << std::endl; return; }

		
		float f = static_cast<float>(d);
		if (std::isinf(f))
		{
			std::cout << (d > 0 ? "+inff" : "-inff") << std::endl;
			return;
		}
		std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}

	void printDouble(double d, bool isNan, int infSign)
	{
		std::cout << "double: ";
		if (isNan)         { std::cout << "nan"  << std::endl; return; }
		if (infSign != 0)  { std::cout << (infSign > 0 ? "+inf" : "-inf") << std::endl; return; }
		std::cout << std::fixed << std::setprecision(1) << d << std::endl;
	}


	
	
	
	void handlePseudo(const std::string& s)
	{
		bool isNan = (s == "nan" || s == "nanf");
		int  infSign = 0;
		if (s == "+inf" || s == "+inff") infSign = +1;
		if (s == "-inf" || s == "-inff") infSign = -1;

		
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		printFloat(0.0, isNan, infSign);
		printDouble(0.0, isNan, infSign);
	}
}


void ScalarConverter::convert(const std::string& literal)
{
	double dVal = 0.0;
	long   iVal = 0;
	LiteralType t = detectType(literal, dVal, iVal);

	if (t == L_INVALID)
	{
		std::cout << "char: impossible\n"
				  << "int: impossible\n"
				  << "float: impossible\n"
				  << "double: impossible" << std::endl;
		return;
	}

	if (t == L_PSEUDO)
	{
		handlePseudo(literal);
		return;
	}

	
	
	double commonValue = 0.0;
	switch (t)
	{
		case L_CHAR:   commonValue = static_cast<double>(literal[0]); break;
		case L_INT:    commonValue = static_cast<double>(iVal); break;
		case L_FLOAT:
		case L_DOUBLE: commonValue = dVal; break;
		default: break;
	}

	printChar(commonValue, false);
	printInt(commonValue, false);
	printFloat(commonValue, false, 0);
	printDouble(commonValue, false, 0);
}
