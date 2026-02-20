/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 15:10:27 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// JOIN <#channel> [password]

void JOIN(Client &client, std::vector<std::string> &commands)
{
	int countWords = commands.size();
	if (countWords < 2)
	{
		std::string error = ":server 461 " + client.getNickname() + " JOIN :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	
	std::string channelName = commands[1];
	if (channelName[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	channelName = channelName.substr(1);

	std::string password;
	if (countWords >= 3)
		password = commands[2];

	Chanel * chaneltemp = strChanneltoChannelType(client.getServer(), channelName);
	if (chaneltemp == NULL)
	{
		Chanel* newchannel = new Chanel(channelName, client);
		if (!password.empty())
		{
			newchannel->sethasPassword(true);
			newchannel->setPassword(password);
		}
		client.getServer().getChanels().push_back(newchannel);
		client.getServer().getUChanelsName().push_back(channelName);
		return ;
	}
	if ((chaneltemp->isInviteOnly() == true) && (chaneltemp->isInvited(client.getNickname()) == false))
	{
		std::string error = ":server 473 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+i)\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	if ((chaneltemp->isHasPassword() == true) && (chaneltemp->checkPassword(password) == false))
	{
		std::string error = ":server 475 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+k)\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	if (chaneltemp->ishasAUserLimit() == true)
	{
		if (chaneltemp->getClients().size() >= chaneltemp->getUserLimit())
		{
			std::string error = ":server 471 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+l)\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return;
		}
	}
	try
	{
		chaneltemp->JoinChanel(client);
		if (chaneltemp->isInvited(client.getNickname()))
			chaneltemp->removeInvite(client.getNickname());
	}
	catch (std::exception &e)
	{
		std::string error = ":server 400 " + client.getNickname() + " :Error joining channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
	}
}