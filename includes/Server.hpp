/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 14:31:24 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Channel.hpp"
#include "ClientConnexion.hpp"
#include "IRC.h"

class Client;

class Server
{
	private:
		std::vector<std::string> usernames;
		std::vector<std::string> channelsName;
		std::vector<Channel*> channels;
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
		std::vector<std::string>& getUChannelsName();
		std::vector<Channel*>& getChannels();
		std::vector<ClientConnexion*>& getClient_connexions();
		std::string& getPassword();

		bool isUserInServer(Client& client);

		void removeClient(Client& client);
		bool isNicknameInServer(const std::string& nickname);
		bool isChannelExist(const std::string& channel);
		void removeChannel(Channel* channelName);
		Client* getClientByNick(const std::string& nickname);
};

