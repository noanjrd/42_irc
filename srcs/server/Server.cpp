/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:42:16 by njard             #+#    #+#             */
/*   Updated: 2025/12/04 11:26:12 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() {}

Server::Server(int fd, int port, std::string pswd) : sevrer_fd(fd), port(port), password(pswd) {}

Server::~Server() {}

int Server::getFd() const
{
	return this->sevrer_fd;
}
int Server::getPort() const
{
	return this->port;
}

std::string& Server::getPassword()
{
	return this->password;
}

std::vector<std::string>& Server::getUsernames()
{
	return this->usernames;
}

std::vector<Chanel>& Server::getChanels()
{
	return this->chanels;
}

std::vector<ClientConnexion>& Server::getClient_connexions()
{
	return this->client_connexions;
}