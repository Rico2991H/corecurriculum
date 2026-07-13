/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:37:45 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/19 11:25:02 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
public:
    HumanA(std::string input1, const Weapon& tool);
    ~HumanA();
    void    attack() const;

private:
    const::Weapon& Tool;
    std::string name;
};

#endif