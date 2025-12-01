/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:31:58 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <iostream>

class Client
{
private:
	std::string nickname;
	std::string username;
	std::string chanel;
	std::string password;
	Server &server;
	int fd;
	bool configured;
	// int authenticated;
	// bool administrators;

public:
	// Client();
	Client(int fd, Server &server);
	~Client();

	void configure(std::string mess);
	bool getConfigured() const;
	Server& getServer() const;
};

bool checkusernameexisting(Client &client, std::string username);