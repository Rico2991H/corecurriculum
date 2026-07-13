/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:34:48 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 15:46:52 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string str1) : type(str1)
{
}

Weapon::~Weapon()
{
}

const std::string& Weapon::getType() const {return (type);}

void        Weapon::setType(const std::string &input)
{
    type = input;
}
