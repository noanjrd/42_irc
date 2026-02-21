/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 14:13:52 by naankour         ###   ########.fr       */
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

// PASS <pswd>
void Client::authentication(std::vector<std::string>& commands)
{
	int countWords = commands.size();
	if (countWords != 2)
	{
		std::string errorMessage = ":server 461 " + this->getNickname() + " "+ commands[0] + " :Not enough parameters\r\n";
		this->sendToClientMessage(errorMessage);
		return ;
	}
	std::string command = commands[0];
	if (command != "PASS")
	{
		std::cerr << "Command PASS not found" << std::endl;
		return ;
	}
	else
	{
		std::string passwordEntered = commands[1];
		std::cout << "|" << passwordEntered << "|" << std::endl;
		if (passwordEntered != this->server.getPassword())
		{
			std::string error_message = ":server 464 * :Password incorrect\r\n";
			send(this->fd, error_message.c_str(),error_message.size(),0);
			std::vector<std::string> quit_message;
			quit_message.push_back("QUIT");
			QUIT(*this, quit_message);
		}
		this->authenticated = true;
		std::cout << "Passwd entered" << std::endl;
	}
	return ;
}

// USER <u>sername> 0 * :<real name>
void Client::configure(std::vector<std::string>& commands)
{
	int countWords =commands.size();
	if (countWords < 2)
	{
		std::string errorMessage = ":server 461 " + this->getNickname() + " "+ commands[0] + " :Not enough parameters\r\n";
		this->sendToClientMessage(errorMessage);
		return ;
	}
	std::string command = commands[0];
	if (command == "NICK" && countWords == 2)
	{
		std::string nickname = commands[1];
		Client* temp = this->server.getClientByNick(nickname);
		if (temp == NULL)
		{
			this->nickname = nickname;
		}
		else
		{
			std::string errorMessage = ":localhost 433 * "+ nickname+ ":Nickname is already in use\r\n";
			this->sendToClientMessage(errorMessage);
		}
	}
	else if (command == "USER" && countWords >= 5)
	{
		std::string usernameEntered = commands[1];
		std::string mode = commands[2];
		if (isstrdigit(mode) == false)
		{
			std::cerr << "Mode has to be a number" << std::endl;
			return ;
		}
		std::string realNameEntered;
		int i = 4;
		while(i < countWords)
		{
			realNameEntered += commands[i];
			if (i != countWords-1)
				realNameEntered += " ";
			i++;
		}
		if (realNameEntered.length() < 2 || realNameEntered[0] != ':' || std::isspace(realNameEntered[1]))
		{
			std::cerr << "Missing ':'"  << realNameEntered << std::endl;
			return ;
		}
		realNameEntered.substr(1); 
		std::cout << "Username and realname changed" << std::endl;
		this->realname = realNameEntered;
		this->username = usernameEntered;
	}
	else
	{
		std::cerr << "Need NICK or USER" << std::endl;
	}
	if (!this->nickname.empty() && !this->username.empty() 
		 && this->authenticated == 1)
	{
		this->configured = true;
		this->sendconnexionconfimation();
	}
	return ;
}

void Client::sendconnexionconfimation()
{
	std::string mess1 = ":localhost 001 " + this->nickname + " :Welcome to the Internet Relay Network " + this->nickname + "!" + this->username + "@localhost\r\n";
	this->sendToClientMessage(mess1);

	std::string mess2 = ":localhost 002 " + this->nickname + " :Your host is localhost, running version 1.0\r\n";
	this->sendToClientMessage(mess2);

	std::string mess3 = ":localhost 003 " + this->nickname + " :This server was created 2025-03-04\r\n";
	this->sendToClientMessage(mess3);

	std::string mess4 = ":localhost 004 " + this->nickname + " localhost 1.0 iow ikl\r\n";
	this->sendToClientMessage(mess4);

	std::string mess5 = ":localhost 005 " + this->nickname + " CHANTYPES=# PREFIX=(o)@ :are supported by this server\r\n";
	this->sendToClientMessage(mess5);
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

bool Client::operator!=(Client& cl) const
{
	if (cl.getUsername() != this->username)
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


void Client::setCommandLineCtrlD(std::string command)
{
	this->commandLineCtrlD = command;
}


std::string Client::getCommandLineCtrlD(void) const
{
	return this->commandLineCtrlD;
}


bool Client::isBufferToReceiveEmpty(void) const
{
	if (this->bufferToReceive.length() > 0)
	{
		return false;
	}
	return true;
}

std::string Client::getBufferToReceive(void) const
{
	return this->bufferToReceive;
}

void Client::clearBufferToReceive(void)
{
	this->bufferToReceive = "";
}

void Client::setBufferToReceive(std::string buffer)
{
	this->bufferToReceive = buffer;
}

void Client::sendToClientMessage(std::string message)
{
	this->setBufferToReceive(message);
}