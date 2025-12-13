/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:12:02 by malbayra          #+#    #+#             */
/*   Updated: 2025/12/11 17:41:08 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Fixed_
# define _Fixed_

#include <iostream>

class Fixed
{
    public:
	Fixed();                            
	Fixed(const Fixed &other);      
	Fixed &operator=(const Fixed &other); 
	~Fixed();                            

	int getRawBits(void) const;
	void setRawBits(int const raw);

  private:
	int _rawBits;
	static const int _fractionalBits = 8;
};

#endif