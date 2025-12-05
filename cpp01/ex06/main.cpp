/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:23:36 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/05 18:51:38 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	getLevelIndex(std::string level)
{
	const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; ++i)
	{
		if (level == levels[i])
			return (i);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./harlFilter <level>" << std::endl;
		return (1);
	}

	Harl harl;
	int levelIndex = getLevelIndex(argv[1]);

	switch (levelIndex)
	{
		case 0:
			harl.complain("DEBUG");
			std::cout << std::endl;
		case 1:
			harl.complain("INFO");
			std::cout << std::endl;
		case 2:
			harl.complain("WARNING");
			std::cout << std::endl;
		case 3:
			harl.complain("ERROR");
			std::cout << std::endl;
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
	return (0);
}
