/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:32:00 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:17:30 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
    private:
        std::string name;

    public:
        void        announce(void) const;
                    Zombie();
        std::string getName() const;
        void        setName(std::string input);
                    ~Zombie();

};

Zombie *ZombieHorde(std::string name, int N);

#endif
