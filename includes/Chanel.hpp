/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2026/02/13 14:18:04 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Client.hpp"

#include <set>

class Chanel
{
private:
	std::string name;
	std::string topic;
	std::vector<std::pair<Client*, int> > clients;
	std::string password;

	size_t		userlimit;

	bool 	inviteOnly; // i
	std::set<std::string> invited;

	bool 	topicProtected; // -t for MODE
	bool 	hasPassword; // -k
	bool 	hasAUserLimit; // -l
	

public:
	Chanel(std::string name, Client &client);
	~Chanel();

	std::string getName();
	std::vector<std::pair<Client*, int> >& getClients();
	bool getTopicProtected() const;
	
	
	void setTopic(std::string topic);
	std::string getTopic();
	
	void setPassword(std::string param);
	
	
	bool isUserOperator(Client &client) const;
	bool isUserInChanel(Client&) const;
	bool isUserInChannelByNick(const std::string& nick) const;
	void JoinChanel(Client &client);
	void sendMessageToAll(Client& client, std::string message) const;
	void sendMessageToAllQuit(Client& client, std::string quitMessage) const;
	void removeClient(Client& client);
	
	void setInviteOnly(bool value);
    bool isInviteOnly() const;
	bool isInvited(const std::string& nickName);
	void removeInvite(const std::string& nickName);
	void addInvite(const std::string& nickName);

	void setTopicProtected(bool value);
    bool isTopicProtected() const;

	void sethasPassword(bool value);
    bool isHasPassword() const;	
	bool checkPassword(std::string mypassword);
	
	void sethasAUserLimit(bool value);
    bool ishasAUserLimit() const;
	void setUserLimit(int limit);
	size_t getUserLimit() const;
	
	bool channelHasOperator() const;// voir sil y a un operator dasn le channel sinon il faut donner le mode operator au premier client de la liste du channel
	void giveOperator();
};