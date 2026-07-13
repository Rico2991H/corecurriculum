/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:26:21 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 15:47:12 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
public:
    HumanB(std::string input1);
    ~HumanB();
    void    setWeapon(const Weapon &tool);
    void    attack();

private:
    const Weapon* Tool2;
    std::string name;
};

#endif