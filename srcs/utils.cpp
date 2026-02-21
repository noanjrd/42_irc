/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 13:55:28 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"


bool isstrdigit(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

bool isUserInServer(Server& server, std::string& username)
{
	std::vector<std::string>::iterator it = find(server.getUsernames().begin(), server.getUsernames().end(), username);
	if (it == server.getUsernames().end())
		return false;
	return true;
}

Channel* strChanneltoChannelType(Server& server, std::string& channelname) // renvoie le Channel utilisable correspodant au nom du channel
{
	std::vector<std::string>::iterator it = find(server.getUChannelsName().begin(), server.getUChannelsName().end(), channelname);
	if (it == server.getUChannelsName().end())
		return NULL;
	else
	{
		int i = it  - server.getUChannelsName().begin();
		return server.getChannels()[i];
	}
}
