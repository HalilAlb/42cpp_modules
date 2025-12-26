/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:34:45 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/27 00:41:08 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    std::cout << "=== Test 1: Basic Construction and Destruction ===" << std::endl;
    {
        ClapTrap clap1("Warrior");
    }
    std::cout << std::endl;

    std::cout << "=== Test 2: Attack Function ===" << std::endl;
    {
        ClapTrap clap2("Attacker");
        clap2.attack("Target Dummy");
        clap2.attack("Another Target");
    }
    std::cout << std::endl;

    std::cout << "=== Test 3: Take Damage ===" << std::endl;
    {
        ClapTrap clap3("Defender");
        clap3.takeDamage(3);
        clap3.takeDamage(5);
        clap3.takeDamage(10); 
        clap3.takeDamage(5);
    }
    std::cout << std::endl;

    std::cout << "=== Test 4: Repair Function ===" << std::endl;
    {
        ClapTrap clap4("Healer");
        clap4.takeDamage(7);
        clap4.beRepaired(5);
        clap4.beRepaired(3);
    }
    std::cout << std::endl;

    std::cout << "=== Test 5: Energy Depletion ===" << std::endl;
    {
        ClapTrap clap5("Exhausted");
        for (int i = 0; i < 11; i++)
        {
            clap5.attack("Enemy");
        }
        clap5.beRepaired(5);
    }
    std::cout << std::endl;

    std::cout << "=== Test 6: Copy Constructor ===" << std::endl;
    {
        ClapTrap original("Original");
        original.takeDamage(3);
        ClapTrap copy(original);
        copy.attack("Test Target");
    }
    std::cout << std::endl;

    std::cout << "=== Test 7: Assignment Operator ===" << std::endl;
    {
        ClapTrap clap7a("Alpha");
        ClapTrap clap7b("Beta");
        clap7a.takeDamage(5);
        clap7b = clap7a;
        clap7b.beRepaired(2);
    }
    std::cout << std::endl;

    std::cout << "=== Test 8: Dead ClapTrap Cannot Act ===" << std::endl;
    {
        ClapTrap dead("Deceased");
        dead.takeDamage(10);
        dead.attack("Ghost");
        dead.beRepaired(5);
    }
    std::cout << std::endl;

    std::cout << "=== Test 9: Mixed Actions ===" << std::endl;
    {
        ClapTrap fighter("Fighter");
        fighter.attack("Monster");
        fighter.takeDamage(4);
        fighter.beRepaired(2);
        fighter.attack("Monster");
        fighter.takeDamage(6);
        fighter.beRepaired(3);
    }
    std::cout << std::endl;

    return 0;
}

