/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:35:18 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/11 17:09:00 by malbayra         ###   ########.fr       */
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
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif
