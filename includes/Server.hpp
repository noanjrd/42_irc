/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 14:16:41 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Chanel.hpp"
#include "ClientConnexion.hpp"
#include "IRC.h"

class Client;

class Server
{
private:
	std::vector<std::string> usernames;
	std::vector<std::string> chanelsname;
	std::vector<Chanel*> chanels;
	std::vector<ClientConnexion*> client_connexions; // Liste des clients
	int sevrer_fd;
	int port;
	std::string password;
public:
	Server();
	Server(int fd, int port, std::string pswd);
	~Server();

	int getFd() const;
	int getPort() const;
	std::vector<std::string>& getUsernames();
	std::vector<std::string>& getUChanelsName();
	std::vector<Chanel*>& getChanels();
	std::vector<ClientConnexion*>& getClient_connexions();
	std::string& getPassword();

	bool isUserInServer(Client& client);

	void removeClient(Client& client);
	bool isNicknameInServer(const std::string& nickname);
	bool isChanelExist(const std::string& chanel);
	void removeChannel(Chanel* chanelName);
	Client* getClientByNick(const std::string& nickname);
};

