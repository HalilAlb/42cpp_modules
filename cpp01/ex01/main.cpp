/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:19:40 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/08 17:35:10 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main( void ) {
   
	int numzombie;
	std::string name;
	Zombie* zombies;
    std::cout << "Creating horde of zombie" << std::endl;
    std::cout << "Number of Zombie: ";
    std::cin >> numzombie;    
	std::cout << "Name of each Zombie: ";
    std::cin >> name;

	zombies = zombieHorde(numzombie, name);

	for (int i = 0; i < numzombie; i++)
		zombies[i].announce();

	delete [] zombies;
    return 0;
}
