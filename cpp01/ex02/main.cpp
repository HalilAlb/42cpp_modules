/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:36:53 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/13 23:41:39 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main( void )
{
	std::string a =  "HI THIS IS BRAIN";
	std::string* stringPTR = &a;
	std::string& stringREF = a;
	
	std::cout << "Adresse of a (value): " << &a << std::endl;
	std::cout << "Adresse of a (pointer): " << stringPTR << std::endl;
	std::cout << "Adresse of a (REF): " << &stringREF << std::endl;

	std::cout << std::endl << "Value of a (pointer): " << *stringPTR << std::endl;
	std::cout << "Value of a (ref): " << stringREF << std::endl;
	
	return (0);
}