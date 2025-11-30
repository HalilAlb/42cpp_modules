/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:51:26 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/30 18:02:52 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(){
    Harl software;
    
    std::string level[] = {"DEBUG","INFO","WARNING","ERROR"};
    
    for(int i = 0; i < 4; i++)
    {
        std::cout << level[i] << std::endl;
        software.complain(level[i]);
        std::cout << std::endl;
    }
    return 0;
}