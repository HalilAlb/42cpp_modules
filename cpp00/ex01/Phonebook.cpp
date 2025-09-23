/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:41:45 by malbayra          #+#    #+#             */
/*   Updated: 2025/09/23 04:07:50 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _currentSize(0) {}
PhoneBook::~PhoneBook() {}

namespace {
    // Satır boşsa tekrar isteyen ortak girdi fonksiyonu
    static bool promptLine(const std::string &msg, std::string &out) {
        do {
            std::cout << msg;
            if (!std::getline(std::cin, out))
                return false; // EOF
        } while (out.empty());
        return true;
    }

    // Yalnızca rakamlardan oluşup oluşmadığını kontrol eder
    static bool isDigitsOnly(const std::string &str) {
        for (std::string::size_type i = 0; i < str.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }
        return true;
    }
}

void PhoneBook::add_contact() {
    std::string name, lname, nname, phone, secret;

    if (!promptLine("Enter your first name: ", name))  return;
    if (!promptLine("Enter your last name: ",  lname)) return;
    if (!promptLine("Enter your nickname: ",   nname)) return;

    // Telefon numarası için rakam kontrolü gerek var mı ?
    do {
        std::cout << "Enter your phone number (digits only): ";
        if (!std::getline(std::cin, phone))
            return;
        if (phone.empty() || !isDigitsOnly(phone))
            std::cout << RED << "Invalid number! Digits only.\n" << RESET;
    } while (phone.empty() || !isDigitsOnly(phone));

    if (!promptLine("Enter your darkest secret: ", secret)) return;

    Contact newContact(name, lname, nname, phone, secret);

    if (_currentSize == 8) { // FIFO(A101): en eskiyi sil
        for (int i = 1; i < 8; ++i)
            _contacts[i - 1] = _contacts[i];
        _currentSize--;
    }
    _contacts[_currentSize++] = newContact;
}

void PhoneBook::displayColumn(const std::string &text) const {
    std::string result = (text.length() > 10) ? text.substr(0, 9) + '.' : text;
    std::cout << std::setw(10) << std::right << result << '|';
}

void PhoneBook::displayContact(int index) const {
    std::string idx(1, static_cast<char>('1' + index));
    displayColumn(idx);
    displayColumn(_contacts[index].getFirstName());
    displayColumn(_contacts[index].getLastName());
    displayColumn(_contacts[index].getNickname());
}

void PhoneBook::displayAllContact() const {
    const int width = 44;
    std::cout << std::setfill('_') << std::setw(width) << "" << std::setfill(' ') << '\n';
    displayColumn("Index");
    displayColumn("First Name");
    displayColumn("Last Name");
    displayColumn("Nickname");
    std::cout << '\n' << std::setfill('_') << std::setw(width) << "" << std::setfill(' ') << '\n';

    for (int j = 0; j < _currentSize; ++j) {
        displayContact(j);
        std::cout << '\n';
    }
}

void PhoneBook::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void PhoneBook::search_contact() {
    if (_currentSize == 0) {
        std::cout << RED << "No entry for the moment..." << RESET << '\n';
        return;
    }
    clearScreen();
    displayAllContact();

    int index;
    while (true) {
        std::cout << "\nEnter the index of your Search: ";
        std::cin >> index;
        if (std::cin.eof()) return;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << RED << "Please enter a valid integer index." << RESET << '\n';
            continue;
        }
        if (index <= 0 || index > _currentSize) {
            std::cout << RED << "Please, enter a correct index!" << RESET << '\n';
            continue;
        }
        break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    clearScreen();
    std::cout << YELLOW << "Perfect! Here is the information of this person" << RESET << '\n';
    std::cout << std::setfill('_') << std::setw(30) << "" << std::setfill(' ') << '\n';

    const Contact &c = _contacts[index - 1];
    std::cout << MAGENTA << "First name: "   << RESET << c.getFirstName()  << '\n'
              << MAGENTA << "Last name: "    << RESET << c.getLastName()   << '\n'
              << MAGENTA << "Nickname: "     << RESET << c.getNickname()   << '\n'
              << MAGENTA << "Phone number: " << RESET << c.getPhoneNumber()<< '\n'
              << MAGENTA << "Secret: "       << RESET << c.getSecret()     << '\n';
}

std::string PhoneBook::getName() const {
    return _currentSize > 0 ? _contacts[0].getFirstName() : "";
}
