/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 16:08:51 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "Server.hpp"
// #include "Chanel.hpp"
#include <iostream>

class Server;
class Chanel;

class Client
{
private:
	std::string nickname;
	std::string username;
	std::string password;
	std::string realname;
	Server &server;
	int fd;
	bool configured;
	bool authenticated;
	// bool administrators;

public:
	Client(int fd, Server &server);
	~Client();

	bool getConfigured() const;
	bool getAuthenticated() const;
	Server& getServer() const;
	std::string& getUsername();
	std::string& getNickname();
	int getFd();

	bool operator==(Client& cl);

	void authentication(std::string& command);
	void configure(std::string& commands);
	void JoinChanel(std::string& chaneltemp);
	void sendconnexionconfimation() const;
	void autoconfigure();
	void autoconfigure2();
};