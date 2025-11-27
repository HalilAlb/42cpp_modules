/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:04 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/27 19:41:00 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string &type) : _type(type)
{
}

const std::string &Weapon::getType() const
{
	return (_type);
}

void Weapon::setType(const std::string &newType)
{
	_type = newType;
}
