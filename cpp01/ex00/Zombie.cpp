/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:35:27 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/13 19:05:15 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie( void ) : _name("foo"){	
}

Zombie::Zombie( std::string name ) : _name(name){
}

void Zombie::announce( void ){
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie( void){
	std::cout << _name << " has been destroyed." << std::endl;
}