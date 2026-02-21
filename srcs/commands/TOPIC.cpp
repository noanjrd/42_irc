/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:35:37 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 13:51:53 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// TOPIC <#channel> <:topic>

void TOPIC(Client &client, std::vector<std::string>& commands)
{
	int countWords = commands.size();
	if (countWords < 2)
	{
		std::string error = ":server 461 " + client.getNickname() + " TOPIC :Not enough parameters\r\n";
		client.sendToClientMessage(error);
		return ;
	}

	std::string channelName = commands[1];
	if (channelName[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	channelName = channelName.substr(1);

	Channel* channel = strChanneltoChannelType(client.getServer(), channelName);
	if (channel == NULL)
	{
		std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}

	if (channel->isUserInChannel(client) == false)
	{
		std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}

	if (countWords == 2)
	{
		std::string message;
		if (channel->getTopic().empty())
			message = ":server 331 " + client.getNickname() + " #" + channelName + " :No topic is set\r\n";
		else
			message = ":server 332 " + client.getNickname() + " #" + channelName + " :" + channel->getTopic() + "\r\n";

		client.sendToClientMessage(message);
		return;
	}
	
	if (channel->getTopicProtected() == true && channel->isUserOperator(client) == false)
	{
		std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
		client.sendToClientMessage(error);
		return;
	}
	std::string topic;
	for (int i = 2; i < countWords; i++)
	{
		if (!topic.empty())
			topic += " ";
		topic += commands[i];
	}
	if (!topic.empty() && topic[0] == ':')
		topic = topic.substr(1);

	channel->setTopic(topic);

 	std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost TOPIC #" + channelName + " :" + topic + "\r\n";
	channel->sendMessageToAll(client,true, finalMessage);
}

