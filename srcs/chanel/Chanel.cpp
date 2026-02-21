/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 12:23:06 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Chanel::Chanel(std::string name, Client &client) : name(name), userlimit(0), inviteOnly(false), topicProtected(false), hasPassword(false), hasAUserLimit(false)
{
	
	this->clients.push_back(std::pair<Client*,int>(&client , OPERATORS));
	std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@host JOIN #" + this->name +  "\r\n";
	client.sendToClientMessage(confirmation);
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
	if (this->isUserInChanel(client) == true)
	{
		throw std::runtime_error("User already in chanel");
	}
	else
	{
		std::cout << "Client joined" << std::endl;
		this->clients.push_back(std::pair<Client*, int>(&client, DEFAULT));
		std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@host JOIN #" + this->name + "\r\n";
		for (size_t i = 0; i < this->clients.size(); i++)
		{
			client.sendToClientMessage(confirmation);
		}
	}
}

bool Chanel::isUserOperator(Client &client) const
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

bool Chanel::getTopicProtected() const
{
	return this->topicProtected;
}

void Chanel::setTopic(std::string topicinput)
{
	this->topic = topicinput;
}

std::string Chanel::getTopic()
{
	return (this->topic);
}

bool Chanel::isUserInChanel(Client& client) const
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (client == *(this->clients[i].first))
			return true;
	}
	return false;
}

bool Chanel::isUserInChannelByNick(const std::string& nick) const
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].first->getNickname() == nick)
            return true;
    }
    return false;
}

void Chanel::sendMessageToAll(Client& client,bool includeClient, std::string& message) const
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (includeClient == false && *(clients[i].first) != client)
		{
			clients[i].first->sendToClientMessage(message);
		}
		if (includeClient == true)
		{
			clients[i].first->sendToClientMessage(message);
		}
	}
	return ;
}

void Chanel::removeClient(Client& client)
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i].first == &client)
		{
			this->clients.erase(this->clients.begin() + i);
			return ;
		}
	}
}

void Chanel::setInviteOnly(bool value)
{
    inviteOnly = value;
}

bool Chanel::isInviteOnly() const
{
    return inviteOnly;
}

bool Chanel::isInvited(const std::string& nickName)
{
	if (invited.find(nickName) != invited.end())
		return (true);
	else
		return (false);
}

void Chanel::removeInvite(const std::string& nickName)
{
	invited.erase(nickName);
}

void Chanel::addInvite(const std::string& nickName)
{
    invited.insert(nickName);
}

void Chanel::setTopicProtected(bool value)
{
    topicProtected= value;
}

bool Chanel::isTopicProtected() const
{
    return topicProtected;
}

void Chanel::sethasPassword(bool value)
{
	hasPassword = value;
}
    
bool Chanel::isHasPassword() const
{
	return hasPassword;
}

void Chanel::setPassword(std::string param)
{
	password = param;
}

bool Chanel::checkPassword(std::string mypassword)
{
	if (password == mypassword)
		return (true);
	else
		return (false);
}

void Chanel::sethasAUserLimit(bool value)
{
	hasAUserLimit = value;
}

bool Chanel::ishasAUserLimit() const
{
	return hasAUserLimit;
}

void Chanel::setUserLimit(int limit)
{
	userlimit = limit;
}

size_t Chanel::getUserLimit() const
{
	return (userlimit);
}

bool Chanel::channelHasOperator() const
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].second == OPERATORS)
			return (true);
	}
	return (false);
}

void Chanel::giveOperator()
{
	if (clients.empty())
		return ;
	if (channelHasOperator() == true)
		return ;
	clients[0].second = OPERATORS;

	std::string message = ":server MODE #" + name + " +o" + clients[0].first->getNickname() + "\r\n";
	
	for (size_t i = 0; i < clients.size(); i++)
		clients[i].first->sendToClientMessage(message);
}