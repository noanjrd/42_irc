/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/25 12:15:02 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.hpp"


bool isstrdigit(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

bool isUserInServer(Server& server, std::string& nickname)
{
	std::vector<ClientConnexion *>& clients = server.getClient_connexions();
	for (std::vector<ClientConnexion *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if ((*it)->getClient().getNickname() == nickname)
		{
			return true;
		}
	}
	return false;
}

Channel* strChanneltoChannelType(Server& server, std::string& channelName)
{
	std::vector<Channel*>& channels = server.getChannels();
	for(std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*it)->getName() == channelName)
		{
			return *it;
		}
	}
	return NULL;
}
