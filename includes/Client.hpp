/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 12:12:50 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Server;
class Chanel;

class Client
{
private:
	std::string nickname;
	std::string username;
	std::string realname;
	std::string commandLineCtrlD;
	std::string bufferToReceive;
	Server &server;
	int fd;
	bool configured;
	bool authenticated;

public:
	Client(int fd, Server &server);
	~Client();

	bool getConfigured() const;
	bool getAuthenticated() const;
	Server& getServer() const;
	std::string& getUsername();
	std::string& getNickname();
	void setCommandLineCtrlD(std::string);
	std::string getCommandLineCtrlD(void) const;
	int getFd();
	bool isBufferToReceiveEmpty(void) const;
	std::string getBufferToReceive(void) const;
	void clearBufferToReceive(void);
	void setBufferToReceive(std::string);

	bool operator==(Client& cl) const;
	bool operator!=(Client& cl) const;

	void authentication(std::vector<std::string>& command);
	void configure(std::vector<std::string>& commands);
	void sendconnexionconfimation();
	void autoconfigure();
	void autoconfigure2();
	void sendToClientMessage(std::string);
};