/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 16:31:59 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Chanel::Chanel() {}

Chanel::Chanel(std::string name, Client &client) : name(name)
{
    this->clients.push_back(client);
    this->operators.push_back(client);
    this->clients_usernames.push_back(client.getUsername());
    std::string confirmation = ":" + client.getUsername() + "!" + client.getNickname()  + "@host JOIN #" + this->name;
    send(client.getFd(), confirmation.c_str(),  confirmation.length(),0);
}

Chanel::~Chanel() {}

std::string Chanel::getName()
{
    return this->name;
}

void Chanel::JoinChanel(Client &client)
{
    std::vector<std::string>::iterator it = find(this->clients_usernames.begin(), this->clients_usernames.end(), client.getUsername());
    if (it != this->clients_usernames.end())
    {
        throw std::runtime_error("User already in chanel");
    }
    else
    {
        this->clients.push_back(client);
        this->clients_usernames.push_back(client.getUsername());
        std::string confirmation = ":" + client.getUsername() + "!" + client.getNickname()  + "@host JOIN #" + this->name;
        for (size_t i = 0; i < this->clients.size(); i++)
        {
            send(this->clients[i].getFd(), confirmation.c_str(),  confirmation.length(),0);
        }
    }
}
