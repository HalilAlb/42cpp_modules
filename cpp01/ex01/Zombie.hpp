/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:20:06 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/13 23:30:23 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ZOMBIE__
#define __ZOMBIE__

#include <string>
#include <iostream>

class Zombie{
private:
	std::string _name;

public:
	Zombie();
	Zombie( std::string name );
	~Zombie();
	void announce( void );
	
	void setName( std::string name );
};

Zombie* zombieHorde( int j, std::string name );

#endif