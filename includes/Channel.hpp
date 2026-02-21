/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 14:32:29 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Client.hpp"

#include <set>

class Channel
{
	private:
		std::string name;
		std::string topic;
		std::vector<std::pair<Client*, int> > clients;
		std::string password;

		size_t		userlimit;

		bool 	inviteOnly;
		std::set<std::string> invited;

		bool 	topicProtected;
		bool 	hasPassword;
		bool 	hasAUserLimit;
		

	public:
		Channel(std::string name, Client &client);
		~Channel();

		std::string getName();
		std::vector<std::pair<Client*, int> >& getClients();
		bool getTopicProtected() const;
		
		
		void setTopic(std::string topic);
		std::string getTopic();
		
		void setPassword(std::string param);
		
		
		bool isUserOperator(Client &client) const;
		bool isUserInChannel(Client&) const;
		bool isUserInChannelByNick(const std::string& nick) const;
		void JoinChannel(Client &client);
		void sendMessageToAll(Client& client,bool includeClient, std::string& message) const;
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