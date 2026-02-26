/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:42:07 by njard            ###   ########.fr       */
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
	std::vector<ClientConnection *>& clients = server.getClient_connexions();
	for (std::vector<ClientConnection *>::iterator it = clients.begin(); it != clients.end(); it++)
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

std::vector<std::string> convertToVector(const std::string& s)
{
	int i  = 0;
	bool letter = 0;
	int start = -99;
	std::vector<std::string> result;
	while(s[i])
	{
		if (!std::isspace(s[i]) && letter == 0)
		{
			letter = 1;
			start = i;
		}
		if (std::isspace(s[i]) && letter == 1)
		{
			result.push_back(s.substr(start, i-start));
			letter = 0;
		}
		i++;
	}
	if (i >= 1 && !std::isspace(s[i-1]) && letter == 1)
	{
		result.push_back(s.substr(start,i-start));
	}
	return result;
}
