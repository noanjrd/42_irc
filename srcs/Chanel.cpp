/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 15:03:24 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Chanel.hpp"

Chanel::Chanel() {}


Chanel::Chanel(std::string name) : name(name) {}

Chanel::~Chanel() {}

std::string& Chanel::getName()
{
    return this->name;
}