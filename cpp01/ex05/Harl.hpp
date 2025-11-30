/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:51:50 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/30 15:27:27 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Harl_
# define _Harl_

#include <iostream>

class Harl
{
  public:
	Harl();
	~Harl();
	void complain(std::string level);

  private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
};

#endif