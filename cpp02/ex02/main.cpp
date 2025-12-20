/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:19:14 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/20 19:00:59 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
	std::cout << "=== BASIC CONSTRUCTORS ===" << std::endl;
	Fixed a;
	Fixed b(10);
	Fixed c(42.42f);
	Fixed d(b);

	std::cout << "\na: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << std::endl;

	std::cout << "\n=== COMPARISON OPERATORS ===" << std::endl;
	Fixed x(12);
	Fixed y(34);
	Fixed z(5);

	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
	std::cout << "x > y: " << (x > y) << std::endl;
	std::cout << "x * y: " << (x * y) << std::endl;
	std::cout << "x < y: " << (x < y) << std::endl;
	std::cout << "x >= z: " << (x >= z) << std::endl;
	std::cout << "x <= z: " << (x <= z) << std::endl;
	std::cout << "x == z: " << (x == z) << std::endl;
	std::cout << "x != y: " << (x != y) << std::endl;

	std::cout << "\n=== ARITHMETIC OPERATORS ===" << std::endl;
	Fixed m(10.5f);
	Fixed n(2);

	std::cout << "m = " << m << ", n = " << n << std::endl;
	std::cout << "m + n = " << (m + n) << std::endl;
	std::cout << "m - n = " << (m - n) << std::endl;
	std::cout << "m * n = " << (m * n) << std::endl;
	std::cout << "m / n = " << (m / n) << std::endl;

	std::cout << "\n=== INCREMENT/DECREMENT OPERATORS ===" << std::endl;
	Fixed p(5);
	std::cout << "p = " << p << std::endl;
	std::cout << "++p = " << ++p << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "p++ = " << p++ << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "--p = " << --p << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "p-- = " << p-- << std::endl;
	std::cout << "p = " << p << std::endl;

	std::cout << "\n=== MIN/MAX FUNCTIONS ===" << std::endl;
	Fixed min1(3);
	Fixed min2(7);
	Fixed const minConst1(15);
	Fixed const minConst2(20);

	std::cout << "min1 = " << min1 << ", min2 = " << min2 << std::endl;
	std::cout << "min(min1, min2) = " << Fixed::min(min1, min2) << std::endl;
	std::cout << "max(min1, min2) = " << Fixed::max(min1, min2) << std::endl;

	std::cout << "\nminConst1 = " << minConst1 << ", minConst2 = " << minConst2 << std::endl;
	std::cout << "min(minConst1, minConst2) = " << Fixed::min(minConst1, minConst2) << std::endl;
	std::cout << "max(minConst1, minConst2) = " << Fixed::max(minConst1, minConst2) << std::endl;

	std::cout << "\n=== SUBJECT TEST ===" << std::endl;
	Fixed		subA;
	Fixed const	subB(Fixed(5.05f) * Fixed(2));

	std::cout << subA << std::endl;
	std::cout << ++subA << std::endl;
	std::cout << subA << std::endl;
	std::cout << subA++ << std::endl;
	std::cout << subA << std::endl;
	std::cout << subB << std::endl;
	std::cout << Fixed::max(subA, subB) << std::endl;

	return 0;
}
