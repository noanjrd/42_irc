/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 16:31:31 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Client.hpp"



class Chanel
{
private:
	std::string name;
	std::string topic;
	std::vector<Client> clients;
	std::vector<std::string> clients_usernames;
	std::vector<Client> operators;
	// int user_limit;
	std::string password;
	// int id;
	// Client tabclient[];

public:
	Chanel();
	Chanel(std::string name, Client &client);
	~Chanel();

	void JoinChanel(Client &client);
	std::string getName();
};