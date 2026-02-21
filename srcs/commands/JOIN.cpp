/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 15:11:09 by naankour         ###   ########.fr       */
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

	Channel * channeltemp = strChanneltoChannelType(client.getServer(), channelName);
	if (channeltemp == NULL)
	{
		Channel* newchannel = new Channel(channelName, client);
		if (!password.empty())
		{
			newchannel->sethasPassword(true);
			newchannel->setPassword(password);
		}
		client.getServer().getChannels().push_back(newchannel);
		client.getServer().getUChannelsName().push_back(channelName);
		return ;
	}
	if ((channeltemp->isInviteOnly() == true) && (channeltemp->isInvited(client.getNickname()) == false))
	{
		std::string errorMessage = ":server 473 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+i)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if ((channeltemp->isHasPassword() == true) && (channeltemp->checkPassword(password) == false))
	{
		std::string errorMessage = ":server 475 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+k)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if (channeltemp->ishasAUserLimit() == true)
	{
		if (channeltemp->getClients().size() >= channeltemp->getUserLimit())
		{
			std::string errorMessage = ":server 471 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+l)\r\n";
			client.sendToClientMessage(errorMessage);
			return;
		}
	}
	try
	{
		channeltemp->JoinChannel(client);
		if (channeltemp->isInvited(client.getNickname()))
			channeltemp->removeInvite(client.getNickname());
	}
	catch (std::exception &e)
	{
		std::string errorMessage = ":server 400 " + client.getNickname() + " :Error joining channel\r\n";
		client.sendToClientMessage(errorMessage);
	}
}
