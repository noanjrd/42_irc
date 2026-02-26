/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:20:17 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Server;
class Channel;

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
		
		int getFd();
		Server& getServer() const;
		std::string& getUsername();
		std::string& getNickname();
		bool getConfigured() const;
		bool getAuthenticated() const;
		void clearBufferToReceive(void);
		void setCommandLineCtrlD(std::string);
		void setBufferToReceive(std::string);
		std::string getBufferToReceive(void) const;
		std::string getCommandLineCtrlD(void) const;
		
		bool operator==(Client& cl) const;
		bool operator!=(Client& cl) const;
		
		bool isBufferToReceiveEmpty(void) const;
		void authentication(std::vector<std::string>& command);
		void configure(std::vector<std::string>& commands);
		void sendconnexionconfimation();
		void autoconfigure();
		void sendToClientMessage(std::string);
};