/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:53 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/07 18:13:37 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>
#include <iostream>

class HumanB
{
  public:
	HumanB(const std::string &name);
	void setWeapon(Weapon &weapon);
	void attack() const;

  private:
	std::string _name;
	Weapon *_weapon;
};

#endif
