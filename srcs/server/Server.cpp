/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:42:16 by njard             #+#    #+#             */
/*   Updated: 2026/02/16 11:36:03 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() {}

Server::Server(int fd, int port, std::string pswd) : sevrer_fd(fd), port(port), password(pswd) {}

Server::~Server() {}

int Server::getFd() const
{
	return this->sevrer_fd;
}
int Server::getPort() const
{
	return this->port;
}

std::string& Server::getPassword()
{
	return this->password;
}

std::vector<std::string>& Server::getUsernames()
{
	return this->usernames;
}


std::vector<std::string>& Server::getUChanelsName()
{
	return this->chanelsname;
}

std::vector<Chanel*>& Server::getChanels()
{
	return this->chanels;
}

std::vector<ClientConnexion*>& Server::getClient_connexions()
{
	return this->client_connexions;
}

bool Server::isUserInServer(Client& client)
{
	for (size_t i = 0; i < this->client_connexions.size(); i++)
	{
		if (this->client_connexions[i]->getClient() == client)
			return true;
	}
	return false;
}

void Server::removeClient(Client& client)
{
    for (size_t i = 0; i < client_connexions.size(); i++)
    {
		Client* c = &client_connexions[i]->getClient();
        if (c == &client)
        {
			delete client_connexions[i];
            client_connexions.erase(client_connexions.begin() + i);
            return;
        }
    }
}

bool Server::isNicknameInServer(const std::string& nickname)
{
    for (size_t i = 0; i < this->client_connexions.size(); i++)
    {
        if (this->client_connexions[i]->getClient().getNickname() == nickname)
            return true;
    }
    return false;
}

bool Server::isChanelExist(const std::string& chanel)
{
	for (size_t i = 0; i < this->chanels.size(); (i++))
	{
		if(this->chanels[i]->getName() == chanel)
			return true;
	}
	return false;
}

void Server::removeChannel(Chanel* chanelName)
{
	for (size_t i = 0; i < chanels.size(); i++)
	{
		if (chanels[i] == chanelName)
		{
			this->chanels.erase(this->chanels.begin() + i);
			break ;
		}
	}
}

Client* Server::getClientByNick(const std::string& nickname)
{
    for (size_t i = 0; i < client_connexions.size(); i++)
    {
        Client* client = &client_connexions[i]->getClient();
        if (client->getNickname() == nickname)
            return client;
    }
    return NULL;
}