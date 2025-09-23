/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:34:22 by malbayra          #+#    #+#             */
/*   Updated: 2025/09/23 04:06:54 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(const std::string &firstName,
                 const std::string &lastName,
                 const std::string &nickname,
                 const std::string &phoneNumber,
                 const std::string &secret)
    : _firstName(firstName),
      _lastName(lastName),
      _nickname(nickname),
      _phoneNumber(phoneNumber),
      _secret(secret)
{}

Contact::Contact()
    : _firstName(""),
      _lastName(""),
      _nickname(""),
      _phoneNumber(""),
      _secret("")
{}

Contact::~Contact() {}

std::string Contact::getFirstName() const { return _firstName; }
std::string Contact::getLastName()  const { return _lastName;  }
std::string Contact::getNickname()  const { return _nickname;  }
std::string Contact::getPhoneNumber() const { return _phoneNumber; }
std::string Contact::getSecret()    const { return _secret;    }
