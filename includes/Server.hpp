/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 16:32:35 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Chanel.hpp"
#include "ClientConnexion.hpp"

class Client;

class Server
{
private:
	std::vector<std::string> usernames;
	std::vector<std::string> chanelsname;
	std::vector<Chanel*> chanels;
	std::vector<ClientConnexion*> client_connexions;
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
};

