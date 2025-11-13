/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:20:31 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/13 23:28:23 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int j, std::string name ){
	Zombie* zombies = new Zombie[j];
	for (int i = 0; i < j; i++)
		zombies[i].setName(name);
	
	return (zombies);
}
