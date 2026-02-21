/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 14:32:54 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// KICK <#channel> <user> [reason]

bool parseKick(Client &client, std::vector<std::string>& commands, std::string& channelName, std::string& nickname, std::string& reason)
{
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string errorMessage = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		client.sendToClientMessage(errorMessage);
		return false;
	}

	channelName = commands[1];
	if (channelName[0] != '#')
	{
		std::string errorMessage = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		client.sendToClientMessage(errorMessage);
		return false ;
	}
	channelName = channelName.substr(1);
	
	nickname = commands[2];
	if (nickname.empty())
	{
		std::string errorMessage = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		client.sendToClientMessage(errorMessage);
		return false ;
	}

	if (countWords > 3)
	{
		for (int i = 3; i < countWords; i++)
			reason +=  " " + commands[i];
		reason = reason.substr(2);	
	}
	else
		reason = "No reason";
	reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
	reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());
	return true;
}

void KICK(Client& client, std::vector<std::string>& commands)
{
	std::string channelName, nickname, reason;
	
	if (parseKick(client, commands, channelName, nickname, reason) == false)
        return;
		
	std::vector<Channel*>& allChannels = client.getServer().getChannels();
	for (size_t i = 0; i < allChannels.size(); i++)
	{
		if (allChannels[i]->getName() == channelName)
		{
			if (allChannels[i]->isUserInChannel(client) == false)
			{
				std::string errorMessage = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
				client.sendToClientMessage(errorMessage);
				return ;
			}
			if (allChannels[i]->isUserOperator(client) == false)
			{
				std::string errorMessage = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
				client.sendToClientMessage(errorMessage);
				return ;
			}
		
			std::vector<std::pair<Client*, int> >& clientsInChannel = allChannels[i]->getClients();
			for (size_t j = 0; j < clientsInChannel.size(); j++)
			{
				if (clientsInChannel[j].first->getNickname() == nickname)
				{
					std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " KICK #" + channelName + " " + nickname + " :" + reason + "\r\n";
					allChannels[i]->sendMessageToAll(client, false,finalMessage);
					allChannels[i]->removeClient(*(clientsInChannel[j].first));
					if (allChannels[i]->getClients().empty())
						client.getServer().removeChannel(allChannels[i]);
					return ;
				}
			}	
			std::string errorMessage = ":server 441 " + client.getNickname() + " " + nickname + " #" + channelName + " :They aren't on that channel\r\n";
			client.sendToClientMessage(errorMessage);
			return ;
		}
	}
	std::string errorMessage = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
	client.sendToClientMessage(errorMessage);
}