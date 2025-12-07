/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:34:20 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/07 20:27:43 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main( void ) {
   std::string name;

    std::cout << "Creating zombie on the stack." << std::endl;
    std::cout << "Zombie name:" << std::flush;
    std::cin >> name;
    randomChump(name);

    std::cout << "\nCreating zombie on the heap." << std::endl;
    std::cout << "Zombie name: " << std::flush;
    std::cin >> name;

    Zombie *zombie2 = newZombie(name);
    zombie2->announce();
    delete zombie2;

    return 0;
}
