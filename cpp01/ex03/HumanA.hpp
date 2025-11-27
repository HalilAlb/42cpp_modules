/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:33 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/27 19:47:16 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA
{
  public:
	HumanA(const std::string &name, Weapon &weapon);
	void attack() const;

  private:
	std::string _name;
	Weapon &_weapon; // always has a weapon
};

#endif // HUMANA_HPP
