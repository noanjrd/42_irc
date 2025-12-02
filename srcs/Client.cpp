/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 17:06:26 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"


Client::Client(int fdclient, Server &server) : chanel(NULL), server(server),fd(fdclient), configured(0), authenticated(0) {}
Client::~Client() {}

bool Client::getConfigured() const
{
	return this->configured;
}

bool Client::getAuthenticated() const
{
	return this->authenticated;
}

Server& Client::getServer() const
{
	return this->server;
}

void Client::authentication(std::string& command)
{
	if (count_words(command) != 2)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string::iterator pos = std::find(command.begin(), command.end(), ' ');
	std::string onlycommand = command.substr(0,pos - command.begin());
	std::cout << "command : "  << onlycommand << std::endl;
	if (onlycommand != "PASS")
	{
		std::cerr << "Pas pass" << std::endl;
		return ;
	}
	else
	{
		int i = onlycommand.length();
		while (command[i] == ' ')
		{
			i++;
		}
		std::cout <<"command" << command << "^" << std::endl;
		std::string temp = command.substr(i, command.length() - i - 1);
		std::cout << "|" << temp << "|" << std::endl;
		if (temp == this->getServer().getPassword())
		{
			this->authenticated = 1;
			return ;
		}
		else
		{
			char buf[] = "Wrong pwd\n";
			send(this->fd, buf, strlen(buf),0);
		}
	}
		
	return ;
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
	if (nicknametemp.empty() || usernametemp.empty() || chaneltemp.empty() || usernameExist(*this, usernametemp) == true)
	{
		char buff[1024] = "Oops,try again to configure your account by entering your infos in this order : nickname username chanel\n";
		send(this->fd,buff, strlen(buff) ,0);
	}
	else
	{
		this->nickname = nicknametemp;
		this->username = usernametemp;
		this->server.getUsernames().push_back(this->username);
		this->JoinChanel(chaneltemp);
		this->configured = 1;
	}
	return ;
}

void Client::JoinChanel(std::string& chanelname)
{

	Chanel newChanel(chanelname);
	this->getServer().getChanels().push_back(newChanel);
	this->chanel = &newChanel;
	return ;
}

bool usernameExist(Client &client, std::string& username)
{
	std::vector<std::string> usernames = client.getServer().getUsernames();
	std::vector<std::string>::iterator it = std::find(usernames.begin(),usernames.end(), username);
	if (it == usernames.end())
		return false;
	return true;
}