/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 15:56:23 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Client::Client(int fdclient, Server &server) : server(server),fd(fdclient), configured(false), authenticated(false) {}

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
		std::cerr << "Wrong number of words" << std::endl;
		return ;
	}
	std::string onlycommand = get_word(commands, 1);
	std::cout << "command : "  << onlycommand << std::endl;
	if (onlycommand != "PASS")
	{
		std::cerr << "Command PASS not found" << std::endl;
		return ;
	}
	else
	{
		std::string passwordtemp = get_word(commands, 2);
		std::cout << "|" << passwordtemp << "|" << std::endl;
		this->password = passwordtemp;
		this->authenticated = true;
		// this.get
		// if (passwords == this->getServer().getPassword())
		// {
		// 	this->authenticated = 1;
		// 	return ;
		// }
		// else
		// {
		// 	char buf[] = "ERROR :Password incorrect\n";
		// 	send(this->fd, buf, strlen(buf),0);
		// 	// ici on doit deco le client
		// }
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
		
		if (isUserInServer(this->server, usernametemp) == false)
		{
			this->username = usernametemp;
			this->realname = realnametemp;
		}
	}
	else
	{
		std::cerr << "Need NICK or USER" << std::endl;
	}
	if (!this->nickname.empty() && !this->username.empty() 
		&& !this->password.empty() && this->authenticated == 1)
	{
		if (this->password != this->server.getPassword())
		{
			std::string wreongpswd = "464 " + this->nickname + " :Password incorrect\r\n";
			// quitter le serveur ici
			return ;	
		}
		this->configured = true;
		this->sendconnexionconfimation();
	}
	return ;
}

void Client::sendconnexionconfimation() const
{
	std::string mess1 = ":localhost 001 " + this->nickname + " :Welcome to the Internet Relay Network " + this->nickname + "!" + this->username + "@localhost\r\n";
	const char *buf1 = mess1.c_str();
	send(this->fd, buf1, strlen(buf1),0);

	std::string mess2 = ":localhost 002 " + this->nickname + " :Your host is localhost, running version 1.0\r\n";
	const char *buf2 = mess2.c_str();
	send(this->fd, buf2, strlen(buf2),0);

	std::string mess3 = ":localhost 003 " + this->nickname + " :This server was created 2025-03-04\r\n";
	const char *buf3= mess3.c_str();
	send(this->fd, buf3, strlen(buf3),0);

	std::string mess4 = ":localhost 004 " + this->nickname + " localhost 1.0 iow ikl\r\n";
	const char *buf4= mess4.c_str();
	send(this->fd, buf4, strlen(buf4),0);

	std::string mess5 = ":localhost 005 " + this->nickname + " CHANTYPES=# PREFIX=(o)@ :are supported by this server\r\n";
	const char *buf5= mess5.c_str();
	send(this->fd, buf5, strlen(buf5),0);
}

int Client::getFd()
{
	return  this->fd;
}

std::string& Client::getNickname()
{
	return this->nickname;
}

bool Client::operator==(Client& cl) const
{
	if (cl.getUsername() == this->username)
	{
		return true;
	}
	return false;
}

void Client::autoconfigure()
{
	this->username = "Noan";
	this->nickname = "nono";
	this->realname = "Noan Jard";
	this->configured = 1;
	this->authenticated = 1;
	
	this->sendconnexionconfimation();
}


void Client::autoconfigure2()
{
	this->username = "Naziha";
	this->nickname = "nana";
	this->realname = "Naziha Aankour";
	this->configured = 1;
	this->authenticated = 1;
	
	this->sendconnexionconfimation();
}