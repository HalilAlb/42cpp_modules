/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:20:06 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/11 17:09:52 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ZOMBIE_
#define _ZOMBIE_

#include <string>
#include <iostream>

class Zombie{
private:
	std::string _name;

public:
	Zombie();
	~Zombie();
	Zombie( std::string name );
	void announce( void );
	
	void setName( std::string name );
};

Zombie* zombieHorde( int N, std::string name );

#endif
