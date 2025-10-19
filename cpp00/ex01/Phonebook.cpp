/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:41:45 by malbayra          #+#    #+#             */
/*   Updated: 2025/10/13 19:58:05 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

// Constructor
PhoneBook::PhoneBook() : _currentSize(0), _head(0)
{
}
PhoneBook::~PhoneBook()
{
}

static bool	promptLine(const std::string &msg, std::string &out)
{
	do
	{
		std::cout << msg;
		if (!std::getline(std::cin, out))
			return (false); // EOF durumunda çık
	} while (out.empty());
	return (true);
}

static bool	isDigitsOnly(const std::string &str)
{
	if (str.empty())
		return (false);
	// İlk karakter + olabilir
	std::string::size_type start = 0;
	if (str[0] == '+')
	{
		if (str.length() == 1) // Sadece + varsa geçersiz
			return (false);
		start = 1;
	}
	// Geri kalan karakterler rakam olmalı
	for (std::string::size_type i = start; i < str.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return (false);
	}
	return (true);
}

void PhoneBook::add_contact()
{
	std::string name, lname, nname, phone, secret;
	if (!promptLine("Enter your first name: ", name))
		return ;
	if (!promptLine("Enter your last name: ", lname))
		return ;
	if (!promptLine("Enter your nickname: ", nname))
		return ;
	do
	{
		std::cout << "Enter your phone number (digits only): ";
		if (!std::getline(std::cin, phone))
			return ;
		if (phone.empty() || !isDigitsOnly(phone))
			std::cout << "Invalid number! Digits only.\n";
	} while (phone.empty() || !isDigitsOnly(phone));
	if (!promptLine("Enter your darkest secret: ", secret))
		return ;
	Contact newContact(name, lname, nname, phone, secret);
	if (_currentSize < 8)
	{
		// Henüz 8 elemana ulaşmadıysak, normal şekilde ekle
		_contacts[_currentSize] = newContact;
		_currentSize++;
	}
	else
	{
		// 8 eleman varsa, sadece ilk elemanı sil (index 0'ı üzerine yaz)
		// Diğer elemanlar yerlerinde kalır
		_contacts[0] = newContact;
	}
	clearScreen();
}

void PhoneBook::displayColumn(const std::string &text) const
{
	std::string result = (text.length() > 10) ? text.substr(0, 9) + '.' : text;
	std::cout << std::setw(10) << std::right << result << '|';
}

void PhoneBook::displayAllContact() const
{
	const int width = 44;
	std::cout << std::setfill('_') << std::setw(width) << "" << std::setfill(' ') << '\n';
	displayColumn("Index");
	displayColumn("First Name");
	displayColumn("Last Name");
	displayColumn("Nickname");
	std::cout << '\n' << std::setfill('_') << std::setw(width) << "" << std::setfill(' ') << '\n';

	for (int i = 0; i < _currentSize; ++i)
	{
		std::cout << std::setw(10) << std::right << i + 1 << '|';
		displayColumn(_contacts[i].getFirstName());
		displayColumn(_contacts[i].getLastName());
		displayColumn(_contacts[i].getNickname());
		std::cout << '\n';
	}
}

void PhoneBook::clearScreen()
{
	std::cout << "\033[H\033[2J\033[3J" << std::endl;
}

void PhoneBook::search_contact()
{
	int	k;

	if (_currentSize == 0)
	{
		std::cout << "No entry for the moment...\n";
		return ;
	}
	clearScreen();
	displayAllContact();
	while (true)
	{
		std::cout << "\nEnter the index of your Search (1 = oldest): ";
		if (!(std::cin >> k))
		{
			if (std::cin.eof())
				return ;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid integer index.\n";
			continue ;
		}
		if (k <= 0 || k > _currentSize)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please, enter a correct index!\n";
			continue ;
		}
		break ;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	clearScreen();
	std::cout << "Perfect! Here is the information of this person\n";
	std::cout << std::setfill('_') << std::setw(30) << "" << std::setfill(' ') << '\n';
	const Contact &c = _contacts[k - 1];
	std::cout << "First name: " << c.getFirstName() << '\n' << "Last name: " << c.getLastName() << '\n' << "Nickname: " << c.getNickname() << '\n' << "Phone number: " << c.getPhoneNumber() << '\n' << "Secret: " << c.getSecret() << '\n';
}
