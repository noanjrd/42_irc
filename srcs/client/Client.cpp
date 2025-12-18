/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 16:25:39 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Client::Client(int fdclient, Server &server) : server(server),fd(fdclient), configured(0), authenticated(0) {}

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

std::string& Client::getUsername()
{
	return this->username;
}

void Client::authentication(std::string& commands)
{
	if (count_words(commands) != 2)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string onlycommand = get_word(commands, 1);
	std::cout << "command : "  << onlycommand << std::endl;
	if (onlycommand != "PASS")
	{
		std::cerr << "Pas pass" << std::endl;
		return ;
	}
	else
	{
		std::string passwords = get_word(commands, 2);
		std::cout << "|" << passwords << "|" << std::endl;
		if (passwords == this->getServer().getPassword())
		{
			this->authenticated = 1;
			return ;
		}
		else
		{
			char buf[] = "ERROR :Password incorrect\n";
			send(this->fd, buf, strlen(buf),0);
		}
	}
	return ;
}

void Client::configure(std::string& commands)
{
	int words = count_words(commands);
	std::cout << "Words : " << words << std::endl;
	if (words < 2)
	{
		std::cerr << "Not enough words :(" << std::endl;
		return ;
	}
	std::string command = get_word(commands, 1);
	if (command == "NICK")
	{
		this->nickname = get_word(commands,2);
	}
	else if (command == "USER" && words >= 5)
	{
		std::string usernametemp = get_word(commands, 2);
		std::string mode = get_word(commands, 3);
		if (isstrdigit(mode) == false)
		{
			std::cerr << "Mode has to be a number" << std::endl;
			return ;
		}
		std::string realnametemp;
		int i = 5;
		while(i <= words)
		{
			realnametemp += get_word(commands, i);
			if (i != words)
				realnametemp += " ";
			i++;
		}
		if (realnametemp[0] != ':' || std::isspace(realnametemp[1]))
		{
			std::cerr << "Missing ':'"  << realnametemp << std::endl;
			return ;
		}
		realnametemp.erase(0, 1); 
		
		if (usernameExist(this->server, usernametemp) == false)
		{
			this->username = usernametemp;
			this->realname = realnametemp;
		}
	}
	else
	{
		std::cerr << "Need NICK or USER" << std::endl;
	}
	if (!this->nickname.empty() && !this->username.empty())
	{
		this->configured = true;
		this->sendconnexionconfimation();
	}
	return ;
}

void Client::sendconnexionconfimation() const
{
	std::string mess1 = ":ft_irc 001 " + this->nickname + " :Welcome to the IRC Network " + this->nickname + "!" + this->username + "@localhost\n";
	const char *buf1 = mess1.c_str();
	send(this->fd, buf1, strlen(buf1),0);

	std::string mess2 = ":ft_irc 002 " + this->nickname + " :Your host is ft_irc, running version 1.0\n";
	const char *buf2 = mess2.c_str();
	send(this->fd, buf2, strlen(buf2),0);

	std::string mess3 = ":ft_irc 003 " + this->nickname + " :This server was created 2025-03-04\n";
	const char *buf3= mess3.c_str();
	send(this->fd, buf3, strlen(buf3),0);

	std::string mess4 = ":ft_irc 004 " + this->nickname + " ft_irc 1.0 o o\n";
	const char *buf4= mess4.c_str();
	send(this->fd, buf4, strlen(buf4),0);
}


bool usernameExist(Server& server, std::string& username)
{
	std::vector<std::string> usernames = server.getUsernames();
	std::vector<std::string>::iterator it = std::find(usernames.begin(),usernames.end(), username);
	if (it == usernames.end())
		return false;
	return true;
}


int Client::getFd()
{
	return  this->fd;
}

std::string& Client::getNickname()
{
	return this->nickname;
}