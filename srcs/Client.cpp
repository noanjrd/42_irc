/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:41:18 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"


Client::Client(int fdclient, Server &serverr) : server(serverr),fd(fdclient), configured(0)
{
	char buff[1024] = "Hi, configure your account by entering your infos in this order : nickname username chanel\n\0";
	send(fdclient,buff, sizeof(buff) ,0);
}

Client::~Client() {}

bool Client::getConfigured() const
{
	return this->configured;
}

Server& Client::getServer() const
{
	return this->server;
}

void Client::configure(std::string message)
{
	int i = 0;
	std::cout << "mess : " << message << std::endl;
	(void)this->server;
	std::string nicknametemp ;
	std::string usernametemp;
	std::string chaneltemp;
	while(message[i] && message[i] == ' ')
		i++;
	while(message[i] and message[i] != ' ')
	{
		nicknametemp.push_back(message[i]);
		i++;
	}
	while(message[i] && message[i] == ' ')
		i++;
	while(message[i] and message[i] != ' ')
	{
		usernametemp.push_back(message[i]);
		i++;
	}
	while(message[i] && message[i] == ' ')
		i++;
	while(message[i] and message[i] != ' ')
	{
		chaneltemp.push_back(message[i]);
		i++;
	}
	std::cout << "test : " << nicknametemp << usernametemp << chaneltemp << std::endl;
	if (nicknametemp.empty() || usernametemp.empty() || chaneltemp.empty() || checkusernameexisting(*this, usernametemp) == true)
	{
		char buff[1024] = "Oops,try again to configure your account by entering your infos in this order : nickname username chanel\n";
		send(this->fd,buff, strlen(buff) ,0);
	}
	else
	{
		this->nickname = nicknametemp;
		this->username = usernametemp;
		this->chanel = chaneltemp;
		this->server.getUsernames().push_back(this->username);
		this->configured = 1;
	}
	return ;
}

bool checkusernameexisting(Client &client, std::string username)
{
	std::vector<std::string>::iterator it = std::find(client.getServer().getUsernames().begin(),client.getServer().getUsernames().end(), username);
	if (it == client.getServer().getUsernames().end())
		return false;
	return true;
}