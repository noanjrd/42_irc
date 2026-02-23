/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/23 14:26:29 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

// JOIN <#channel> [password]

void JOIN(Client &client, std::vector<std::string> &commands)
{
	int countWords = commands.size();
	if (countWords < 2)
	{
		std::string errorMessage = ":serverIRC 461 " + client.getNickname() + " JOIN :Not enough parameters\r\n";
		client.sendToClientMessage(errorMessage);
		return ;
	}
	
	std::string channelName = commands[1];
	if (channelName[0] != '#' || channelName.length() < 2)
	{
		std::string errorMessage = ":serverIRC 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		client.sendToClientMessage(errorMessage);
		return ;
	}
	channelName = channelName.substr(1);

	std::string password;
	if (countWords >= 3)
		password = commands[2];

	bool isNewChannel = false;
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
		channeltemp = newchannel;
		isNewChannel = true;
	}
	if ((channeltemp->isInviteOnly() == true) && (channeltemp->isInvited(client.getNickname()) == false))
	{
		std::string errorMessage = ":serverIRC 473 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+i)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if ((channeltemp->isHasPassword() == true) && (channeltemp->checkPassword(password) == false))
	{
		std::string errorMessage = ":serverIRC 475 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+k)\r\n";
		client.sendToClientMessage(errorMessage);
		return;
	}
	if (channeltemp->ishasAUserLimit() == true)
	{
		if (channeltemp->getClients().size() >= channeltemp->getUserLimit())
		{
			std::string errorMessage = ":serverIRC 471 " + client.getNickname() + " #" + channelName + " :Cannot join channel (+l)\r\n";
			client.sendToClientMessage(errorMessage);
			return;
		}
	}
	try
	{
		if (!isNewChannel)
			channeltemp->JoinChannel(client);
		
		if (channeltemp->isInvited(client.getNickname()))
			channeltemp->removeInvite(client.getNickname());

		if (!channeltemp->getTopic().empty())
		{
			std::string topicMessage = ":serverIRC 332 " + client.getNickname() + " #" + channelName + " :" + channeltemp->getTopic() + "\r\n";
			client.sendToClientMessage(topicMessage);
		}
		else
		{
			std::string noTopicMessage = ":serverIRC 331 " + client.getNickname() + " #" + channelName + " :No topic is set\r\n";
			client.sendToClientMessage(noTopicMessage);
		}
		std::vector<std::string> namesCommands;
		namesCommands.push_back("NAMES");
		namesCommands.push_back('#' + channelName);
		NAMES(client, namesCommands);
	}
	catch (std::exception &e)
	{
		std::string errorMessage = ":serverIRC 400 " + client.getNickname() + " :Error joining channel : " + e.what() + "\r\n";
		
		client.sendToClientMessage(errorMessage);
	}
}
