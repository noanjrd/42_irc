/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:35:37 by njard             #+#    #+#             */
/*   Updated: 2026/02/11 15:58:41 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// TOPIC #channel :topic
void TOPIC(Client &client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 2)
	{
		std::string error = ":server 461 " + client.getNickname() + " TOPIC :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}

	std::string channelName = get_word(commands, 2);
	if (channelName.empty() || channelName[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	channelName = channelName.substr(1);

	Chanel* channel = strChaneltoChanelType(client.getServer(), channelName);
	if (channel == NULL)
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

	if (words == 2)
	{
		std::string message;
		if (channel->getTopic().empty())
			message = ":server 331 " + client.getNickname() + " #" + channelName + " :No topic is set\r\n";
		else
			message = ":server 332 " + client.getNickname() + " #" + channelName + " :" + channel->getTopic() + "\r\n";

		send(client.getFd(), message.c_str(), message.size(), 0);
		return;
	}
	
	std::string topic;
	for (int i = 3; i <= words; i++)
	{
		if (!topic.empty())
			topic += " ";
		topic += get_word(commands,i);
	}
	if (!topic.empty() && topic[0] == ':')
		topic = topic.substr(1);

	if (channel->getTopicProtected() == true && channel->isUserOperator(client) == false)
	{
		std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	channel->setTopic(topic);

 	std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost TOPIC #" + channelName + " :" + topic + "\r\n";

	std::vector<std::pair<Client*, int> >& users = channel->getClients();
	for (size_t i = 0; i < users.size(); i++)
		send(users[i].first->getFd(), finalMessage.c_str(), finalMessage.size(), 0);
}

