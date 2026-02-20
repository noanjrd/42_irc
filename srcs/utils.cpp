/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 14:12:40 by njard            ###   ########.fr       */
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

Chanel* strChanneltoChannelType(Server& server, std::string& chanelname) // renvoie le Chanel utilisable correspodant au nom du chanel
{
	std::vector<std::string>::iterator it = find(server.getUChanelsName().begin(), server.getUChanelsName().end(), chanelname);
	if (it == server.getUChanelsName().end())
		return NULL;
	else
	{
		int i = it  - server.getUChanelsName().begin();
		return server.getChanels()[i];
	}
}
