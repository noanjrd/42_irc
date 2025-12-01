/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:39:18 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "IRC.h"
#include <iostream>
#include <vector>

class Server
{
private:
	std::vector<std::string> usernames;
	int sevrer_fd;
	int port;
	std::string password;
public:
	Server();
	Server(int fd, int port, std::string pswd);
	~Server();

	int getFd() const;
	int getPort() const;
	std::vector<std::string> getUsernames() const;
	std::string& getPassword();
};

