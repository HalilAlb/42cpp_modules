/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:12 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/08 17:23:29 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
  public:
    Weapon();
	Weapon(const std::string &type);
	const std::string &getType() const;
	void setType(const std::string &newType);

  private:
	std::string _type;
};

#endif 
