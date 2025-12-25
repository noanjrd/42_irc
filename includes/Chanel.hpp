/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/12/25 14:25:12 by njard            ###   ########.fr       */
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
	std::string password;
	int userlimit;
	bool topicForAll; // -t for MODE
	bool InviteOnly; // -i for MODE
	bool PasswordSet; // -k
	bool HasAUserLimit; // -l
	
	

public:
	Chanel(std::string name, Client &client);
	~Chanel();

	std::string getName();
	std::vector<std::pair<Client*, int> >& getClients();
	bool getTopicForAll() const;

	void setTopic(std::string topic);

	bool isUserOperator(Client &client) const;
	bool isUserInChanel(Client&) const;
	void JoinChanel(Client &client);
	void sendMessageToAll(Client& client, std::string message) const;
};