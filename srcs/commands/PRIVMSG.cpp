/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:15:42 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 13:57:28 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// PRIVMSG <user or channel> <message>

static void PRIVMSGToServer(Client &client, std::string& destination, std::string& message )
{
	destination = destination.substr(1);
	Chanel *channel = strChanneltoChannelType(client.getServer(), destination);
	if (channel == NULL)
	{
		std::string error = ":server 403 " + client.getNickname() + " #" + destination + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	if (channel->isUserInChanel(client) == false)
	{
		std::string error = ":server 404 " + client.getNickname() + " #" + destination + " :Cannot send to channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	std::string entireMessage = ":" +  client.getNickname() + "!" + client.getUsername()+"@localhost PRIVMSG #"  + channel->getName() + " :" + message + "\r\n"; 
	channel->sendMessageToAll(client,false, entireMessage);
}

static void PRIVMSGtoClient(Client &client, std::string& destination, std::string& message)
{
	Client* receiver = client.getServer().getClientByNick(destination);
	if (receiver == NULL)
	{
		std::string error = ":server 401 " + client.getNickname() + " " + destination + " :No such nick/channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	std::string message_formatted = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost PRIVMSG " + receiver->getNickname() + " :"+ message + "\r\n";
	send(receiver->getFd(),message_formatted.c_str(),message_formatted.size(),0);
}

void PRIVMSG(Client &client, std::vector<std::string>& commands)
{
	std::cout << "coucou" << std::endl;
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " PRIVMSG :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	int i = 2;
	std::string message;
	while (i < countWords)
	{
		message+= " " + commands[i];
		i++;
	}
	if (message[1] != ':')
	{
		std::cerr << "Error syntax message" << std::endl; // chck si c ets le bon message
		return ;
	}
	message = message.substr(2);
	std::string destination = commands[1];
	if (destination[0] == '#')
		return PRIVMSGToServer(client, destination, message);
	else
	{
		return PRIVMSGtoClient(client, destination, message);
	}
}