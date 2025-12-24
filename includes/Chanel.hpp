/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 15:55:38 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Client.hpp"



class Chanel
{
private:
	std::string name;
	std::string topic;
	std::vector<std::pair<Client*, int> > clients;
	std::vector<std::string> clients_usernames;
	// int user_limit;
	std::string password;
	bool topicForAll;
	// int id;
	// Client tabclient[];

public:
	// Chanel();
	Chanel(std::string name, Client &client);
	~Chanel();

	std::string getName();
	std::vector<std::pair<Client*, int> >& getClients();
	bool getTopicForAll() const;

	bool isUserOperator(Client &client) const;
	void JoinChanel(Client &client);
};