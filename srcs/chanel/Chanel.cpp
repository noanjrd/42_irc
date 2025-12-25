/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2025/12/25 14:44:01 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Chanel::Chanel(std::string name, Client &client) : name(name), userlimit(0),  topicForAll(false), InviteOnly(false), HasAUserLimit(false)
{
	this->clients.push_back(std::pair<Client*,int>(&client , OPERATORS));
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
			send(this->clients[i].first->getFd() , confirmation.c_str(),  confirmation.length(),0);
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

bool Chanel::getTopicForAll() const
{
	return this->topicForAll;
}

void Chanel::setTopic(std::string topicinput)
{
	this->topic = topicinput;
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

void Chanel::sendMessageToAll(Client& client, std::string message) const
{
	std::string entiremessage = ":" +  client.getNickname() + "!" + client.getUsername()+"@localhost PRIVMSG "  + this->name + " :" + message + "\r\n"; 
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (*(clients[i].first) != client)
		{
			send(clients[i].first->getFd(), entiremessage.c_str(), entiremessage.length(),0);
		}
	}
	return ;
}