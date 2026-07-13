/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:16:58 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:56:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>

void    replace(std::string name, std::string oldstr, std::string newstr)
{
    if (oldstr.empty())
        return;
    std::string og_text;
    std::string line;
    int         len = oldstr.length();
    std::string::size_type start = 0;
    std::ifstream MyReadFile(name.c_str()); //since older ifstream expects a char we use c.str() to return a pointer
    if (!MyReadFile.is_open())
    {
        std::cerr << "Error opening file\n";
        return;
    }
    while (getline(MyReadFile, line))
        og_text += line + '\n';
    while ((start = og_text.find(oldstr, start)) != std::string::npos) // searches for startpos of word
    {
        og_text.erase(start, len);
        og_text.insert(start, newstr);
        start += newstr.length();
    }
    std::ofstream MyFile(name + ".replace.txt"); // creates a newfile
    MyFile << og_text;
}

int main()
{
    replace("File1.txt", "old", "lovely");
    return (0);
}