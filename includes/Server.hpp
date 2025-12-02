/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2025/12/02 16:21:19 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "Chanel.hpp"

class Server
{
private:
	std::vector<std::string> usernames;
	std::vector<Chanel> chanels;
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
	std::vector<Chanel>& getChanels();
	std::string& getPassword();
};

