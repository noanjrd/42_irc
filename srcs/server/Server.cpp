/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:42:16 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 13:57:48 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() {}

Server::Server(int fd, int port, std::string pswd) : sevrer_fd(fd), port(port), password(pswd) {}

Server::~Server() 
{
	for (size_t i = 0; i < channels.size(); i++)
		delete channels[i];
	
	for (size_t i = 0; i < client_connexions.size(); i++)
		delete client_connexions[i];
}

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


std::vector<std::string>& Server::getUChannelsName()
{
	return this->channelsName;
}

std::vector<Channel*>& Server::getChannels()
{
	return this->channels;
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
	for (size_t i = 0; i < channels.size(); i++)
    {
        channels[i]->removeClient(client);
    }
	
    for (size_t i = 0; i < client_connexions.size(); i++)
    {
		Client* c = &client_connexions[i]->getClient();
        if (c == &client)
        {
			close(c->getFd());
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

bool Server::isChannelExist(const std::string& channel)
{
	for (size_t i = 0; i < this->channels.size(); (i++))
	{
		if(this->channels[i]->getName() == channel)
			return true;
	}
	return false;
}

void Server::removeChannel(Channel* channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i] == channelName)
		{
			this->channels.erase(this->channels.begin() + i);
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