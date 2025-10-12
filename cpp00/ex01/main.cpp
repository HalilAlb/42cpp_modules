/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:47:14 by malbayra          #+#    #+#             */
/*   Updated: 2025/10/12 20:49:49 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static void showMenu() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║       PHONEBOOK MENU           ║\n";
    std::cout << "╠════════════════════════════════╣\n";
    std::cout << "║  ADD    - Add new contact      ║\n";
    std::cout << "║  SEARCH - Search contacts      ║\n";
    std::cout << "║  EXIT   - Quit program         ║\n";
    std::cout << "╚════════════════════════════════╝\n";
    std::cout << "> ";
}

int main() {
    PhoneBook phoneBook;
    std::string command;

    std::cout << "Welcome to the PhoneBook!\n";

    while (true) {
        showMenu();
        
        if (!std::getline(std::cin, command))
            break;
        
        if (command == "ADD")
            phoneBook.add_contact();
        else if (command == "SEARCH")
            phoneBook.search_contact();
        else if (command == "EXIT")
            break;
        else if (!command.empty())
            std::cout << "Unknown command!\n";
    }
    
    std::cout << "\nGoodbye!\n";
    return 0;
}