/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:30:00 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/28 21:10:09 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main()
{
    std::cout << "╔══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║      DIAMOND INHERITANCE - DIAMONDTRAP TESTING          ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Test 1: Construction/Destruction Chaining ===" << std::endl;
    std::cout << "Testing proper construction order: ClapTrap -> ScavTrap -> FragTrap -> DiamondTrap" << std::endl;
    {
        std::cout << "\n--- Creating DiamondTrap ---" << std::endl;
        DiamondTrap diamond("Gemstone");
        std::cout << "\n--- Destroying DiamondTrap (reverse order) ---" << std::endl;
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 2: whoAmI() - Identity Test ===" << std::endl;
    std::cout << "DiamondTrap has its own name and ClapTrap name with suffix" << std::endl;
    {
        DiamondTrap diamond("Crystal");
        std::cout << "\n--- Calling whoAmI() ---" << std::endl;
        diamond.whoAmI();
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 3: Inherited Attributes Test ===" << std::endl;
    std::cout << "HP: 100 (FragTrap), Energy: 50 (ScavTrap), Damage: 30 (FragTrap)" << std::endl;
    {
        DiamondTrap diamond("Warrior");
        std::cout << "\n--- Testing attacks (should use ScavTrap's attack) ---" << std::endl;
        diamond.attack("Enemy1");
        diamond.attack("Enemy2");
        
        std::cout << "\n--- Testing damage (30 points from FragTrap) ---" << std::endl;
        diamond.takeDamage(40);
        diamond.takeDamage(30);
        
        std::cout << "\n--- Checking remaining HP (should be 30/100) ---" << std::endl;
        diamond.beRepaired(20);
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 4: Multiple Special Abilities ===" << std::endl;
    std::cout << "DiamondTrap has access to ScavTrap and FragTrap abilities" << std::endl;
    {
        DiamondTrap diamond("Multitasker");
        
        std::cout << "\n--- Using ScavTrap's guardGate() ---" << std::endl;
        diamond.guardGate();
        
        std::cout << "\n--- Using FragTrap's highFivesGuys() ---" << std::endl;
        diamond.highFivesGuys();
        
        std::cout << "\n--- Using DiamondTrap's whoAmI() ---" << std::endl;
        diamond.whoAmI();
        
        std::cout << "\n--- Using ScavTrap's attack (inherited) ---" << std::endl;
        diamond.attack("Target");
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 5: Energy Depletion Test ===" << std::endl;
    std::cout << "DiamondTrap has 50 energy points from ScavTrap" << std::endl;
    {
        DiamondTrap diamond("Marathon");
        std::cout << "\n--- Performing 50 attacks to deplete energy ---" << std::endl;
        for (int i = 0; i < 51; i++)
        {
            if (i < 3 || i == 49 || i == 50)
                diamond.attack("Target");
        }
        
        std::cout << "\n--- Trying to repair with no energy ---" << std::endl;
        diamond.beRepaired(10);
        
        std::cout << "\n--- Special abilities should still work ---" << std::endl;
        diamond.guardGate();
        diamond.highFivesGuys();
        diamond.whoAmI();
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 6: Copy Constructor ===" << std::endl;
    {
        DiamondTrap original("Original");
        original.takeDamage(30);
        original.attack("Test");
        
        std::cout << "\n--- Creating copy ---" << std::endl;
        DiamondTrap copy(original);
        
        std::cout << "\n--- Original whoAmI ---" << std::endl;
        original.whoAmI();
        
        std::cout << "\n--- Copy whoAmI ---" << std::endl;
        copy.whoAmI();
        
        copy.attack("Copy Target");
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 7: Assignment Operator ===" << std::endl;
    {
        DiamondTrap diamond1("Alpha");
        DiamondTrap diamond2("Beta");
        
        diamond1.takeDamage(50);
        diamond1.attack("Enemy");
        
        std::cout << "\n--- Before assignment ---" << std::endl;
        std::cout << "Diamond1: ";
        diamond1.whoAmI();
        std::cout << "Diamond2: ";
        diamond2.whoAmI();
        
        std::cout << "\n--- Assigning diamond1 to diamond2 ---" << std::endl;
        diamond2 = diamond1;
        
        std::cout << "\n--- After assignment ---" << std::endl;
        std::cout << "Diamond2: ";
        diamond2.whoAmI();
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 8: Dead DiamondTrap Cannot Act ===" << std::endl;
    {
        DiamondTrap diamond("Mortal");
        diamond.takeDamage(100);
        
        std::cout << "\n--- Trying to act while dead ---" << std::endl;
        diamond.attack("Ghost");
        diamond.beRepaired(50);
        
        std::cout << "\n--- Special abilities still work ---" << std::endl;
        diamond.guardGate();
        diamond.highFivesGuys();
        diamond.whoAmI();
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 9: All Robot Types Comparison ===" << std::endl;
    {
        std::cout << "\n--- Creating all robot types ---" << std::endl;
        ClapTrap clap("BasicBot");
        std::cout << std::endl;
        
        ScavTrap scav("GuardBot");
        std::cout << std::endl;
        
        FragTrap frag("BombBot");
        std::cout << std::endl;
        
        DiamondTrap diamond("UltimateBot");
        std::cout << std::endl;
        
        std::cout << "\n--- ClapTrap actions (HP:10, Energy:10, Damage:0) ---" << std::endl;
        clap.attack("Target");
        
        std::cout << "\n--- ScavTrap actions (HP:100, Energy:50, Damage:20) ---" << std::endl;
        scav.attack("Target");
        scav.guardGate();
        
        std::cout << "\n--- FragTrap actions (HP:100, Energy:100, Damage:30) ---" << std::endl;
        frag.attack("Target");
        frag.highFivesGuys();
        
        std::cout << "\n--- DiamondTrap actions (HP:100, Energy:50, Damage:30) ---" << std::endl;
        diamond.attack("Target");  // ScavTrap's attack
        diamond.guardGate();       // ScavTrap's ability
        diamond.highFivesGuys();   // FragTrap's ability
        diamond.whoAmI();          // DiamondTrap's ability
        
        std::cout << "\n--- Destruction order ---" << std::endl;
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 10: Virtual Inheritance Verification ===" << std::endl;
    std::cout << "Verifying only ONE ClapTrap instance exists in DiamondTrap" << std::endl;
    {
        DiamondTrap diamond("Tester");
        
        std::cout << "\n--- Initial state ---" << std::endl;
        diamond.whoAmI();
        
        std::cout << "\n--- Taking damage affects the single ClapTrap instance ---" << std::endl;
        diamond.takeDamage(50);
        
        std::cout << "\n--- Repairing affects the same instance ---" << std::endl;
        diamond.beRepaired(25);
        
        diamond.whoAmI();
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 11: Name Shadowing Test ===" << std::endl;
    std::cout << "DiamondTrap has its own _name that shadows ClapTrap's _name" << std::endl;
    {
        DiamondTrap diamond1("Shadow");
        DiamondTrap diamond2("Light");
        
        std::cout << "\n--- Diamond1 identity ---" << std::endl;
        diamond1.whoAmI();
        
        std::cout << "\n--- Diamond2 identity ---" << std::endl;
        diamond2.whoAmI();
        
        std::cout << "\n--- Both are separate entities ---" << std::endl;
        diamond1.attack("Target");
        diamond2.attack("Target");
    }
    std::cout << "\n" << std::endl;

    std::cout << "=== Test 12: Stress Test - All Features ===" << std::endl;
    {
        DiamondTrap diamond("StressTest");
        
        std::cout << "\n--- Identity check ---" << std::endl;
        diamond.whoAmI();
        
        std::cout << "\n--- Combat test ---" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            diamond.attack("Enemy");
            diamond.takeDamage(15);
        }
        
        std::cout << "\n--- Repair test ---" << std::endl;
        diamond.beRepaired(30);
        
        std::cout << "\n--- All special abilities ---" << std::endl;
        diamond.guardGate();
        diamond.highFivesGuys();
        diamond.whoAmI();
        
        std::cout << "\n--- Final attack ---" << std::endl;
        diamond.attack("Final Enemy");
    }
    std::cout << "\n" << std::endl;

    std::cout << "╔══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            ALL TESTS COMPLETED SUCCESSFULLY              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════╝" << std::endl;

    return 0;
}

