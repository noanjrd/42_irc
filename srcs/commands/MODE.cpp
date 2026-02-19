/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:30:27 by naankour          #+#    #+#             */
/*   Updated: 2026/02/19 12:41:17 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// MODE #channel -mode param

void MODE(Client& client, std::vector<std::string>& commands)
{
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}

	std::string channelName = commands[1];
	if (channelName.empty() || channelName[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	channelName = channelName.substr(1);
	
	std::string modeT = commands[2];
	if (modeT.size() != 2)
	{
		std::string error = ":server 472 " + client.getNickname() + " " + std::string(1, modeT[0]) + " :is unknown mode char to me\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	if (modeT[0] != '+' && modeT[0] != '-')
	{
		std::string error = ":server 472 " + client.getNickname() + " " + std::string(1, modeT[0]) + " :is unknown mode char to me\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	char sign = modeT[0];
	char mode = modeT[1];
	
	if (mode != 'i' && mode != 't' && mode != 'k' && mode != 'l' && mode != 'o')
	{
		std::string error = ":server 472 " + client.getNickname() + " " + std::string(1, mode) + " :is unknown mode char to me\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}

	std::string param;
	if (mode == 'i' || mode == 't')
	{
		if (countWords > 3)
		{
			std::string error = ":server 461 " + client.getNickname() + " MODE :Too many parameters\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return;
		}
	}
	else if (mode == 'k' || mode == 'o' || mode == 'l')
	{	
		
		if (sign == '+')
		{
			if (countWords < 4)
			{
				std::string error = ":server 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return;
			}
		}
		if (countWords >= 4)
		{
			if (!param.empty() && param[0] == ':')
				param = param.substr(1);
		}
	}

	Chanel* channel = strChanneltoChannelType(client.getServer(), channelName);
	if (!channel)
	{
		std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	if (channel->isUserInChanel(client) == false)
	{
		std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	if (channel->isUserOperator(client) == false)
	{
		std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
    	return;
	}

	if (mode == 'i')
	{
		if (sign == '+')
			channel->setInviteOnly(true);
		else
			channel->setInviteOnly(false);
	}

	else if (mode == 't')
	{
		if (sign == '+')
			channel->setTopicProtected(true);
		else
			channel->setTopicProtected(false);
	}

	else if (mode == 'k')
	{
		if (sign == '+')
		{
			if (param.empty())
			{
				std::string error = ":server 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return;
			}
			channel->sethasPassword(true);
			channel->setPassword(param);
		}
		else
		{
			channel->sethasPassword(false);
			channel->setPassword("");
			param = "";
		}
	}
	
	else if (mode == 'o')
	{
		if (param.empty())
		{
			std::string error = ":server 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return;
		}

		if (channel->isUserInChannelByNick(param) == false)
		{
			std::string error = ":server 441 " + client.getNickname() + " " + param + " #" + channelName + " :They aren't on that channel\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return ;
		}

		std::vector<std::pair<Client*, int> >& users = channel->getClients();
		if (sign == '+')
		{
			for (size_t i = 0; i < users.size(); i++)
			{
				if (users[i].first->getNickname() == param)
				{
					users[i].second = OPERATORS;
					break ;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < users.size(); i++)
			{
				if (users[i].first->getNickname() == param)
				{
					users[i].second = DEFAULT;
					break ;
				}
			}
		}
	}
	
	else if (mode == 'l')
	{
		if (sign == '+')
		{
			if (param.empty())
			{
				std::string error = ":server 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return;
			}
			for (size_t i = 0; i < param.size(); i++)
			{
				if (!isdigit(param[i]))
				{
					std::string error = ":server 461 " + client.getNickname() + " MODE :Invalid limit parameter\r\n";
					send(client.getFd(), error.c_str(), error.size(), 0);
					return;
				}
			}

			int limit = atoi(param.c_str());
			if (limit <= 0)
			{
				std::string error = ":server 461 " + client.getNickname() + " MODE :Invalid limit parameter\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return;
			}
			channel->sethasAUserLimit(true);
			channel->setUserLimit(limit);
		}
		else
		{
			channel->sethasAUserLimit(false);
			param = "";
		}
			
	}
	
	std::string reply = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE #" + channelName + " " + sign + mode;
	if (!param.empty())
		reply += " " + param;
	reply += "\r\n";

	std::vector<std::pair<Client*, int> >& users = channel->getClients();
	for (size_t i = 0; i < users.size(); i++)
		send(users[i].first->getFd(), reply.c_str(), reply.size(), 0);
}