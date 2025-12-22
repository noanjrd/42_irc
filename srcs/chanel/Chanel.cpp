/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 16:24:54 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// Chanel::Chanel() {}

Chanel::Chanel(std::string name, Client &client) : name(name)
{
	this->clients.push_back(std::pair<Client*,int>(&client , OPERATORS));
	this->clients_usernames.push_back(client.getUsername());
	std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@host JOIN #" + this->name +  "\r\n";
	send(client.getFd(), confirmation.c_str(),  confirmation.length(),0);
}

Chanel::~Chanel() {}

std::string Chanel::getName()
{
	return this->name;
}

std::vector<std::pair<Client*, int> >& Chanel::getClients()
{
	return this->clients;
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
		std::cout << "Client joined" << std::endl;
        this->clients.push_back(std::pair<Client*, int>(&client, DEFAULT));
        this->clients_usernames.push_back(client.getUsername());
        std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@host JOIN #" + this->name + "\r\n";
        for (size_t i = 0; i < this->clients.size(); i++)
        {
            send(this->clients[i].first->getFd() , confirmation.c_str(),  confirmation.length(),0);
        }
	}
}

bool Chanel::isUserOperator(Client &client)
{
	std::string username = client.getUsername();
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (*(this->clients[i].first) == client)
		{
			if (this->clients[i].second == OPERATORS)
				return true;
			else
				return false;
		}
	}
	return false;
}
