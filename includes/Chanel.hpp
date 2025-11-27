/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/11/27 15:31:53 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Chanel
{
private:
    std::string name;
    int user_limit;
    std::string password;
    int id;
public:
    Chanel();
    ~Chanel();
};