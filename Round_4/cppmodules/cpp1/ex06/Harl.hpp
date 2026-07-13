/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:59:00 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/19 14:59:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>
#include <iostream>

class Harl
{
    public:
        Harl();
        ~Harl();
        void    complain(std::string level);
        
    private:
        void    debug(void);
        void    info(void);
        void    warning(void);
        void    error(void);
};

#endif
