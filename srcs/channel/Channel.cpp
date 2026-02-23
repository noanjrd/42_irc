/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2026/02/23 14:20:37 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

Channel::Channel(std::string name, Client &client) : name(name), userlimit(0), inviteOnly(false), topicProtected(false), hasPassword(false), hasAUserLimit(false)
{
	this->clients.push_back(std::pair<Client*,int>(&client , OPERATORS));
	std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@serverIRC JOIN #" + this->name +  "\r\n";
	client.sendToClientMessage(confirmation);
}

Channel::~Channel() {}

std::string Channel::getName()
{
	return this->name;
}

std::vector<std::pair<Client*, int> >& Channel::getClients()
{
	return this->clients;
}

void Channel::JoinChannel(Client &client)
{
	if (this->isUserInChannel(client) == true)
	{
		throw std::runtime_error("User already in channel");
	}
	else
	{
		std::cout << "Client joined" << std::endl;
		this->clients.push_back(std::pair<Client*, int>(&client, DEFAULT));
		std::string confirmation = ":" + client.getNickname() + "!" + client.getUsername()  + "@serverIRC JOIN #" + this->name + "\r\n";
		this->sendMessageToAll(client, true, confirmation);

	}
}

bool Channel::isUserOperator(Client &client) const
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

bool Channel::getTopicProtected() const
{
	return this->topicProtected;
}

void Channel::setTopic(std::string topicinput)
{
	this->topic = topicinput;
}

std::string Channel::getTopic()
{
	return (this->topic);
}

bool Channel::isUserInChannel(Client& client) const
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (client == *(this->clients[i].first))
			return true;
	}
	return false;
}

bool Channel::isUserInChannelByNick(const std::string& nick) const
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].first->getNickname() == nick)
            return true;
    }
    return false;
}

void Channel::sendMessageToAll(Client& client,bool includeClient, std::string& message) const
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

void Channel::removeClient(Client& client)
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

void Channel::setInviteOnly(bool value)
{
    inviteOnly = value;
}

bool Channel::isInviteOnly() const
{
    return inviteOnly;
}

bool Channel::isInvited(const std::string& nickName)
{
	if (invited.find(nickName) != invited.end())
		return (true);
	else
		return (false);
}

void Channel::removeInvite(const std::string& nickName)
{
	invited.erase(nickName);
}

void Channel::addInvite(const std::string& nickName)
{
    invited.insert(nickName);
}

void Channel::setTopicProtected(bool value)
{
    topicProtected= value;
}

bool Channel::isTopicProtected() const
{
    return topicProtected;
}

void Channel::sethasPassword(bool value)
{
	hasPassword = value;
}
    
bool Channel::isHasPassword() const
{
	return hasPassword;
}

void Channel::setPassword(std::string param)
{
	password = param;
}

bool Channel::checkPassword(std::string mypassword)
{
	if (password == mypassword)
		return (true);
	else
		return (false);
}

void Channel::sethasAUserLimit(bool value)
{
	hasAUserLimit = value;
}

bool Channel::ishasAUserLimit() const
{
	return hasAUserLimit;
}

void Channel::setUserLimit(int limit)
{
	userlimit = limit;
}

size_t Channel::getUserLimit() const
{
	return (userlimit);
}

bool Channel::channelHasOperator() const
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].second == OPERATORS)
			return (true);
	}
	return (false);
}

void Channel::giveOperator()
{
	if (clients.empty())
		return ;
	if (channelHasOperator() == true)
		return ;
	clients[0].second = OPERATORS;

	std::string message = ":serverIRC MODE #" + name + " +o " + clients[0].first->getNickname() + "\r\n";
	
	for (size_t i = 0; i < clients.size(); i++)
		clients[i].first->sendToClientMessage(message);
}
