/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 12:25:48 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// JOIN <#channel> [password]

void JOIN(Client &client, std::vector<std::string> &commands)
{
	int countWords = commands.size();
	if (countWords < 2)
	{
		std::string errorMessage = ":server 461 " + client.getNickname() + " JOIN :Not enough parameters\r\n";
		client.sendToClientMessage(errorMessage);
		return ;
	}
	
	std::string channelName = commands[1];
	if (channelName[0] != '#')
	{
		std::string errorMessage = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		client.sendToClientMessage(errorMessage);
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
		std::string errorMessage = ":server 473 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+i)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if ((chaneltemp->isHasPassword() == true) && (chaneltemp->checkPassword(password) == false))
	{
		std::string errorMessage = ":server 475 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+k)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if (chaneltemp->ishasAUserLimit() == true)
	{
		if (chaneltemp->getClients().size() >= chaneltemp->getUserLimit())
		{
			std::string errorMessage = ":server 471 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+l)\r\n";
			client.sendToClientMessage(errorMessage);
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
		std::string errorMessage = ":server 400 " + client.getNickname() + " :Error joining channel\r\n";
		client.sendToClientMessage(errorMessage);
	}
}