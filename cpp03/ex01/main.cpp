/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 01:00:00 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/27 01:22:14 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int main()
{
    std::cout << "=== Test 1: Construction/Destruction Chaining ===" << std::endl;
    {
        std::cout << "\n--- Creating ScavTrap ---" << std::endl;
        ScavTrap scav("Guardian");
        std::cout << "\n--- Destroying ScavTrap ---" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Test 2: ScavTrap Attack (Different Message) ===" << std::endl;
    {
        ScavTrap scav("Warrior");
        scav.attack("Enemy");
        scav.attack("Another Enemy");
    }
    std::cout << std::endl;

    std::cout << "=== Test 3: GuardGate Function ===" << std::endl;
    {
        ScavTrap scav("Gatekeeper");
        scav.guardGate();
        scav.attack("Intruder");
        scav.guardGate();
    }
    std::cout << std::endl;

    std::cout << "=== Test 4: ScavTrap Taking Damage ===" << std::endl;
    {
        ScavTrap scav("Tank");
        scav.takeDamage(30);
        scav.takeDamage(50);
        scav.takeDamage(20);
        scav.takeDamage(10);
    }
    std::cout << std::endl;

    std::cout << "=== Test 5: ScavTrap Repair ===" << std::endl;
    {
        ScavTrap scav("Healer");
        scav.takeDamage(60);
        scav.beRepaired(30);
        scav.beRepaired(20);
        scav.attack("Enemy");
    }
    std::cout << std::endl;

    std::cout << "=== Test 6: Energy Depletion Test ===" << std::endl;
    {
        ScavTrap scav("Exhausted");
        std::cout << "\n--- Attacking 50 times to deplete energy ---" << std::endl;
        for (int i = 0; i < 51; i++)
        {
            scav.attack("Target");
        }
        std::cout << "\n--- Trying to repair with no energy ---" << std::endl;
        scav.beRepaired(10);
        std::cout << "\n--- Trying guardGate (should still work) ---" << std::endl;
        scav.guardGate();
    }
    std::cout << std::endl;

    std::cout << "=== Test 7: Copy Constructor ===" << std::endl;
    {
        ScavTrap original("Original");
        original.takeDamage(30);
        original.attack("Test");
        
        std::cout << "\n--- Creating copy ---" << std::endl;
        ScavTrap copy(original);
        copy.attack("Copy Target");
        copy.guardGate();
    }
    std::cout << std::endl;

    std::cout << "=== Test 8: Assignment Operator ===" << std::endl;
    {
        ScavTrap scav1("Alpha");
        ScavTrap scav2("Beta");
        
        scav1.takeDamage(40);
        std::cout << "\n--- Assigning scav1 to scav2 ---" << std::endl;
        scav2 = scav1;
        scav2.attack("Target");
        scav2.guardGate();
    }
    std::cout << std::endl;

    std::cout << "=== Test 9: Dead ScavTrap Cannot Act ===" << std::endl;
    {
        ScavTrap scav("Deceased");
        scav.takeDamage(100);
        scav.attack("Ghost");
        scav.beRepaired(50);
        scav.guardGate();
    }
    std::cout << std::endl;

    std::cout << "=== Test 10: Mixed ClapTrap and ScavTrap ===" << std::endl;
    {
        std::cout << "\n--- Creating ClapTrap ---" << std::endl;
        ClapTrap clap("BasicBot");
        
        std::cout << "\n--- Creating ScavTrap ---" << std::endl;
        ScavTrap scav("AdvancedBot");
        
        std::cout << "\n--- ClapTrap actions ---" << std::endl;
        clap.attack("Target");
        
        std::cout << "\n--- ScavTrap actions ---" << std::endl;
        scav.attack("Target");
        scav.guardGate();
        
        std::cout << "\n--- Destruction order ---" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Test 11: High Damage ScavTrap ===" << std::endl;
    {
        ScavTrap scav("PowerHouse");
        for (int i = 0; i < 5; i++)
        {
            scav.attack("Monster");
        }
        scav.guardGate();
    }
    std::cout << std::endl;

    return 0;
}
