/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:00:00 by malbayra          #+#    #+#             */
/*   Updated: 2026/01/01 18:27:11 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    std::cout << "=== Test 1: Construction/Destruction Chaining ===" << std::endl;
    {
        std::cout << "\n--- Creating FragTrap ---" << std::endl;
        FragTrap frag("Demolisher");
        std::cout << "\n--- Destroying FragTrap ---" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Test 2: FragTrap High Fives ===" << std::endl;
    {
        FragTrap frag("Friendly");
        frag.highFivesGuys();
        frag.attack("Target");
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 3: FragTrap Attack and Damage ===" << std::endl;
    {
        FragTrap frag("Warrior");
        std::cout << "\n--- Attacking multiple targets ---" << std::endl;
        frag.attack("Enemy1");
        frag.attack("Enemy2");
        frag.attack("Enemy3");
        
        std::cout << "\n--- Taking damage ---" << std::endl;
        frag.takeDamage(40);
        frag.takeDamage(30);
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 4: FragTrap Repair ===" << std::endl;
    {
        FragTrap frag("Healer");
        frag.takeDamage(70);
        frag.beRepaired(30);
        frag.beRepaired(25);
        frag.attack("Enemy");
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 5: Energy Depletion Test ===" << std::endl;
    {
        FragTrap frag("Exhausted");
        std::cout << "\n--- Performing 100 actions to deplete energy ---" << std::endl;
        for (int i = 0; i < 101; i++)
        {
            frag.attack("Target");
        }
        std::cout << "\n--- Trying to repair with no energy ---" << std::endl;
        frag.beRepaired(10);
        std::cout << "\n--- HighFives (should still work) ---" << std::endl;
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 6: Copy Constructor ===" << std::endl;
    {
        FragTrap original("Original");
        original.takeDamage(50);
        original.attack("Test");
        
        std::cout << "\n--- Creating copy ---" << std::endl;
        FragTrap copy(original);
        copy.attack("Copy Target");
        copy.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 7: Assignment Operator ===" << std::endl;
    {
        FragTrap frag1("Alpha");
        FragTrap frag2("Beta");
        
        frag1.takeDamage(60);
        std::cout << "\n--- Assigning frag1 to frag2 ---" << std::endl;
        frag2 = frag1;
        frag2.attack("Target");
        frag2.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 8: Dead FragTrap Cannot Act ===" << std::endl;
    {
        FragTrap frag("Deceased");
        frag.takeDamage(100);
        frag.attack("Ghost");
        frag.beRepaired(50);
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 9: Mixed ClapTrap, ScavTrap and FragTrap ===" << std::endl;
    {
        std::cout << "\n--- Creating ClapTrap ---" << std::endl;
        ClapTrap clap("BasicBot");
        
        std::cout << "\n--- Creating ScavTrap ---" << std::endl;
        ScavTrap scav("GuardBot");
        
        std::cout << "\n--- Creating FragTrap ---" << std::endl;
        FragTrap frag("DemolitionBot");
        
        std::cout << "\n--- ClapTrap actions ---" << std::endl;
        clap.attack("Target");
        
        std::cout << "\n--- ScavTrap actions ---" << std::endl;
        scav.attack("Target");
        scav.guardGate();
        
        std::cout << "\n--- FragTrap actions ---" << std::endl;
        frag.attack("Target");
        frag.highFivesGuys();
        
        std::cout << "\n--- Destruction order ---" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Test 10: High Damage FragTrap ===" << std::endl;
    {
        FragTrap frag("PowerHouse");
        std::cout << "\n--- FragTrap deals 30 damage per attack ---" << std::endl;
        for (int i = 0; i < 5; i++)
        {
            frag.attack("Monster");
        }
        frag.highFivesGuys();
    }
    std::cout << std::endl;

    std::cout << "=== Test 11: FragTrap vs ScavTrap Comparison ===" << std::endl;
    {
        std::cout << "\n--- Creating both types ---" << std::endl;
        ScavTrap scav("Guardian");
        FragTrap frag("Destroyer");
        
        std::cout << "\n--- ScavTrap special ability ---" << std::endl;
        scav.guardGate();
        
        std::cout << "\n--- FragTrap special ability ---" << std::endl;
        frag.highFivesGuys();
        
        std::cout << "\n--- Both attacking ---" << std::endl;
        scav.attack("Enemy");  // 20 damage
        frag.attack("Enemy");  // 30 damage
    }
    std::cout << std::endl;

    std::cout << "=== Test 12: Stress Test - Multiple High Fives ===" << std::endl;
    {
        FragTrap frag("Enthusiastic");
        for (int i = 0; i < 3; i++)
        {
            frag.highFivesGuys();
            frag.attack("Target");
        }
    }
    std::cout << std::endl;

    // std::cout << "=== Test 13: Polymorphism with dynamic_cast ===" << std::endl;
    // {
    //     std::cout << "\n--- Creating array of base class pointers ---" << std::endl;
    //     ClapTrap* robots[3];
    //     robots[0] = new ClapTrap("BasicBot");
    //     robots[1] = new ScavTrap("GuardBot");
    //     robots[2] = new FragTrap("DemoBot");

    //     std::cout << "\n--- Using dynamic_cast for type-safe downcasting ---" << std::endl;
    //     for (int i = 0; i < 3; i++)
    //     {
    //         std::cout << "\nRobot " << i << ": " << std::endl;
    //         robots[i]->attack("Target");
            
    //         // Try casting to ScavTrap
    //         ScavTrap* scav = dynamic_cast<ScavTrap*>(robots[i]);
    //         if (scav)
    //         {
    //             std::cout << "-> It's a ScavTrap!" << std::endl;
    //             scav->guardGate();
    //         }
            
    //         // Try casting to FragTrap
    //         FragTrap* frag = dynamic_cast<FragTrap*>(robots[i]);
    //         if (frag)
    //         {
    //             std::cout << "-> It's a FragTrap!" << std::endl;
    //             frag->highFivesGuys();
    //         }
    //     }

    //     std::cout << "\n--- Cleaning up ---" << std::endl;
    //     for (int i = 0; i < 3; i++)
    //         delete robots[i];
    // }
    // std::cout << std::endl;

    return 0;
}
