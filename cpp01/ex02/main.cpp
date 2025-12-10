/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:36:53 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/10 17:01:59 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(void)
{
	std::string a = "HI THIS IS BRAIN";
	std::string *stringPTR = &a;
	std::string &stringREF = a;

	std::cout << "Adress of a (value): " << &a << std::endl;
	std::cout << "Adress of a (pointer): " << stringPTR << std::endl;
	std::cout << "Adress of a (REF): " << &stringREF << std::endl;
	
	std::cout << std::endl << "Value of a (value): " << a << std::endl;
	std::cout << "Value of a (pointer): " << *stringPTR << std::endl;
	std::cout << "Value of a (ref): " << stringREF << std::endl;

	return (0);
}