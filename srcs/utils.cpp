/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 13:51:48 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"


std::string get_word(const std::string& s, int location) // location : index+1
{
	int words = 0;
	int i  = 0;
	bool letter = 0;
	int begin = -99;
	int end = -99;
	while(s[i])
	{
		if (!std::isspace(s[i]) && letter == 0)
		{
			
			words++;
			letter = 1;
			if (begin == -99 && words == location)
			{
				begin = i;
			}
		}
		if (std::isspace(s[i]))
		{
			if (begin != -99 and end == -99)
			{
				end = i;
			}
			letter = 0;
		}
		i++;
	}
	if (i >= 1 && !std::isspace(s[i-1]))
	{
		if (begin != -99 && end == -99)
		{
			end = i;
		}
		words++;
	}
	std::string news;
	if (begin != -99 && end != -99)
		news = s.substr(begin,end-begin);
	return news;
}

bool isstrdigit(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

bool isUserInServer(Server& server, std::string& username)
{
	std::vector<std::string>::iterator it = find(server.getUsernames().begin(), server.getUsernames().end(), username);
	if (it == server.getUsernames().end())
	{
		return false;
	}
	return true;
}

Chanel* strChanneltoChannelType(Server& server, std::string& chanelname) // renvoie le Chanel utilisable correspodant au nom du chanel
{
	std::vector<std::string>::iterator it = find(server.getUChanelsName().begin(), server.getUChanelsName().end(), chanelname);
	if (it == server.getUChanelsName().end())
	{
		return NULL;
	}
	else
	{
		int i = it  - server.getUChanelsName().begin();
		return server.getChanels()[i];
	}
}
