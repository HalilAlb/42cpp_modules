/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 03:35:11 by malbayra          #+#    #+#             */
/*   Updated: 2025/09/23 04:04:26 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
public:
    Contact(const std::string &firstName,
            const std::string &lastName,
            const std::string &nickname,
            const std::string &phoneNumber,
            const std::string &secret);
    Contact();
    ~Contact();

    std::string getFirstName()   const;
    std::string getLastName()    const;
    std::string getNickname()    const;
    std::string getPhoneNumber() const;
    std::string getSecret()      const;

private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phoneNumber;
    std::string _secret;
};

#endif
