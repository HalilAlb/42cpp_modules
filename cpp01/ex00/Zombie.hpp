/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:35:18 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/13 19:04:53 by malbayra         ###   ########.fr       */
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
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif