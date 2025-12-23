/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:19:07 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/22 20:08:17 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed() : _rawBits(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(other.getRawBits())
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		_rawBits = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const int value) : _rawBits(value << _fractionalBits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value) : _rawBits(roundf(value * (1 << _fractionalBits)))
{
	std::cout << "Float constructor called" << std::endl;
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _rawBits >> _fractionalBits;
}

int Fixed::getRawBits(void) const
{
	return _rawBits;
}

void Fixed::setRawBits(int const raw)
{
	_rawBits = raw;
}

bool Fixed::operator>(const Fixed &other) const
{
	return _rawBits > other.getRawBits();
}

bool Fixed::operator<(const Fixed &other) const
{
	return _rawBits < other.getRawBits();
}

bool Fixed::operator>=(const Fixed &other) const
{
	return _rawBits >= other.getRawBits();
}

bool Fixed::operator<=(const Fixed &other) const
{
	return _rawBits <= other.getRawBits();
}

bool Fixed::operator==(const Fixed &other) const
{
	return _rawBits == other.getRawBits();
}

bool Fixed::operator!=(const Fixed &other) const
{
	return _rawBits != other.getRawBits();
}

Fixed Fixed::operator+(const Fixed &other) const
{
	Fixed result;
	result.setRawBits(_rawBits + other.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed &other) const
{
	Fixed result;
	result.setRawBits(_rawBits - other.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed &other) const
{
	Fixed result;
	result.setRawBits((_rawBits * other.getRawBits()) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
	Fixed result;
	result.setRawBits((_rawBits << _fractionalBits) / other.getRawBits());
	return result;
}

Fixed &Fixed::operator++(void)
{
	_rawBits++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	_rawBits++;
	return temp;
}

Fixed &Fixed::operator--(void)
{
	_rawBits--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	_rawBits--;
	return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}
