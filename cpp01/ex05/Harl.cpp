/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:51:43 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/11 17:12:58 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}
Harl::~Harl()
{
}

void Harl::debug(void)
{
	std::cout << "[ DEBUG ]\n"
				<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!\n";
}

void Harl::info(void)
{
	std::cout << "[ INFO ]\n"
              << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!\n";
}

void Harl::warning(void)
{
	std::cout << "[ WARNING ]\n"
				<< "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.\n";
}

void Harl::error(void)
{
	std::cout << "[ ERROR ]\n"
				<< "This is unacceptable! I want to speak to the manager now.\n";
}

void Harl::complain(std::string level)
{
	typedef void (Harl::*HarlMemFn)(void);

	const char *levell[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	HarlMemFn funcs[] = {&Harl::debug, &Harl::info, &Harl::warning,
		&Harl::error};

	for (int i = 0; i < 4; ++i)
	{
		if (level == levell[i])
		{
			(this->*funcs[i])();
			return ;
		}
	}
	std::cout << "[ Probably complaining about insignificant problems ]\n";
}
