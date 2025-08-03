/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 01:44:43 by malbayra          #+#    #+#             */
/*   Updated: 2025/08/03 17:24:04 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <cctype>

int main(int ac, char const **av)
{
    if (ac > 1)
    {
        for (int i = 1; av[i]; i++)
            for (int j= 0; av[i][j]; j++)
                std::cout << static_cast<char>(std::toupper(av[i][j])); 
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return 0;
}