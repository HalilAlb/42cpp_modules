/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:47:14 by malbayra          #+#    #+#             */
/*   Updated: 2025/09/23 04:08:16 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main() {
    PhoneBook phoneBook;
    std::string command;

    std::cout << "Welcome to the PhoneBook!\n";
    std::cout << "Available commands: ADD, SEARCH, EXIT\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command))
            break; // EOF (Ctrl+D)

        if (command == "ADD")
            phoneBook.add_contact();
        else if (command == "SEARCH")
            phoneBook.search_contact();
        else if (command == "EXIT")
            break;
        else if (!command.empty())
            std::cout << "Unknown command. Try: ADD, SEARCH, EXIT\n";
    }

    std::cout << "Goodbye!\n";
    return 0;
}