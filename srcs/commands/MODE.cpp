/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:30:27 by naankour          #+#    #+#             */
/*   Updated: 2026/02/23 12:38:40 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

// MODE #channel -mode param

bool modeO(Client& client, Channel* channel, char sign, std::string& param, const std::string& channelName)
{
	if (param.empty())
	{
		std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
		client.sendToClientMessage(error);
		return false;
	}

	if (channel->isUserInChannelByNick(param) == false)
	{
		std::string error = ":serverIRC 441 " + client.getNickname() + " " + param + " #" + channelName + " :They aren't on that channel\r\n";
		client.sendToClientMessage(error);
		return false;
	}

	std::vector<std::pair<Client*, int> >& users = channel->getClients();
	
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i].first->getNickname() == param)
		{
			if (sign == '+')
				users[i].second = OPERATORS;
			else
				users[i].second = DEFAULT;
			return true;
		}
	}
	return false;
}

bool modeL(Client& client, Channel* channel, char sign, std::string& param)
{
	if (sign == '+')
	{
		if (param.empty())
		{
			std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
			client.sendToClientMessage(error);
			return false;
		}
		for (size_t i = 0; i < param.size(); i++)
		{
			if (!isdigit(param[i]))
			{
				std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Invalid limit parameter\r\n";
				client.sendToClientMessage(error);
				return false;
			}
		}

		int limit = atoi(param.c_str());
		if (limit <= 0)
		{
			std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Invalid limit parameter\r\n";
			client.sendToClientMessage(error);
			return false;
		}
		channel->sethasAUserLimit(true);
		channel->setUserLimit(limit);
	}
	else
	{
		channel->sethasAUserLimit(false);
		param = "";
	}
	return true;
}

bool parseMode(Client& client, std::vector<std::string>& commands, std::string& channelName, char& sign, char& mode, std::string& param)
{
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
		client.sendToClientMessage(error);
		return false ;
	}

	channelName = commands[1];
	if (channelName.empty() || channelName[0] != '#')
	{
		std::string error = ":serverIRC 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		client.sendToClientMessage(error);
		return false;
	}
	channelName = channelName.substr(1);
	
	std::string modeT = commands[2];
	if (modeT.size() != 2 || (modeT[0] != '+' && modeT[0] != '-'))
	{
		std::string error = ":serverIRC 472 " + client.getNickname() + " " + std::string(1, modeT[0]) + " :is unknown mode char to me\r\n";
		client.sendToClientMessage(error);
		return false;
	}
	sign = modeT[0];
	mode = modeT[1];
	
	if (mode != 'i' && mode != 't' && mode != 'k' && mode != 'l' && mode != 'o')
	{
		std::string error = ":serverIRC 472 " + client.getNickname() + " " + std::string(1, mode) + " :is unknown mode char to me\r\n";
		client.sendToClientMessage(error);
		return false;
	}

	if (mode == 'i' || mode == 't')
	{
		if (countWords > 3)
		{
			std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Too many parameters\r\n";
			client.sendToClientMessage(error);
			return false;
		}
	}
	else if (mode == 'k' || mode == 'o' || mode == 'l')
	{	
		if (sign == '+' && countWords < 4)
		{
			std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
			client.sendToClientMessage(error);
			return false;
		}
		if (sign == '-' && (mode == 'k' || mode == 'l') && countWords > 3)
		{
			std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Too many parameters\r\n";
			client.sendToClientMessage(error);
			return false;
		}
		if (countWords > 4)
		{
			if (mode == 'l' || mode == 'o')
			{
				std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Too many parameters\r\n";
				client.sendToClientMessage(error);
				return false;
			}
		}
		if (countWords == 4)
		{
			param = commands[3];
			if (!param.empty() && param[0] == ':')
				param = param.substr(1);
		}
		return true;
	}
	return true;
}

void MODE(Client& client, std::vector<std::string>& commands)
{
	std::string channelName, param;
    char sign, mode;
	
	if (parseMode(client, commands, channelName, sign, mode, param) == false)
        return;

	Channel* channel = strChanneltoChannelType(client.getServer(), channelName);
	if (!channel)
	{
		std::string error = ":serverIRC 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	if (channel->isUserInChannel(client) == false)
	{
		std::string error = ":serverIRC 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	if (channel->isUserOperator(client) == false)
	{
		std::string error = ":serverIRC 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
		client.sendToClientMessage(error);
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
				std::string error = ":serverIRC 461 " + client.getNickname() + " MODE :Not enough parameters\r\n";
				client.sendToClientMessage(error);
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
		if (modeO(client, channel, sign, param, channelName) == false)
			return ;
	}
	else if (mode == 'l')
	{
		if (modeL(client, channel, sign, param) == false)
			return ;
	}
	std::string reply = ":" + client.getNickname() + "!" + client.getUsername() + "@serverIRC MODE #" + channelName + " " + sign + mode;
	if (!param.empty())
		reply += " " + param;
	reply += "\r\n";

	channel->sendMessageToAll(client, true, reply);
}