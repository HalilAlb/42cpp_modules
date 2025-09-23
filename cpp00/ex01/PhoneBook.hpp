/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:42:20 by malbayra          #+#    #+#             */
/*   Updated: 2025/09/23 04:03:52 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Renk makroları
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"

class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();
    
    // Yeni kişi ekleme
    void add_contact();

    // Kişi arama ve gösterme
    void search_contact();

    // Sadece ilk kişinin adını döndürür (örnek amaçlı)
    std::string getName() const;

private:
    // Yardımcı gösterim fonksiyonları
    void displayColumn(const std::string &text) const;
    void displayContact(int index) const;
    void displayAllContact() const;
    void clearScreen();

    // 8 kişilik sabit kapasite
    Contact _contacts[8];
    int     _currentSize;
};

#endif
