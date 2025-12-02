/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 16:16:20 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Chanel.hpp"
#include <iostream>

class Client
{
private:
	std::string nickname;
	std::string username;
	std::string password;
	Chanel *chanel;
	Server &server;
	int fd;
	bool configured;
	bool authenticated;
	// bool administrators;

public:
	// Client();
	Client(int fd, Server &server);
	~Client();

	void configure(std::string mess);
	bool getConfigured() const;
	bool getAuthenticated() const;
	Server& getServer() const;

	void authentication(std::string& command);
	void JoinChanel(std::string& chaneltemp);
};

bool usernameExist(Client &client, std::string& username);