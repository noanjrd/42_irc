/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:15:42 by njard             #+#    #+#             */
/*   Updated: 2026/02/23 13:12:53 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

// PRIVMSG <user or channel> <message>

static void PRIVMSGToServer(Client &client, std::string& destination, std::string& message )
{
	destination = destination.substr(1);
	Channel *channel = strChanneltoChannelType(client.getServer(), destination);
	if (channel == NULL)
	{
		std::string error = ":serverIRC 403 " + client.getNickname() + " #" + destination + " :No such channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	if (channel->isUserInChannel(client) == false)
	{
		std::string error = ":serverIRC 404 " + client.getNickname() + " #" + destination + " :Cannot send to channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	std::string entireMessage = ":" +  client.getNickname() + "!" + client.getUsername()+"@serverIRC PRIVMSG #"  + channel->getName() + " :" + message + "\r\n"; 
	channel->sendMessageToAll(client,false, entireMessage);
}

static void PRIVMSGtoClient(Client &client, std::string& destination, std::string& message)
{
	Client* receiver = client.getServer().getClientByNick(destination);
	if (receiver == NULL)
	{
		std::string error = ":server 401 " + client.getNickname() + " " + destination + " :No such nick/channel\r\n";
		client.sendToClientMessage(error);
		return ;
	}
	std::string entireMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@serverIRC PRIVMSG " + receiver->getNickname() + " :"+ message + "\r\n";
	receiver->sendToClientMessage(entireMessage);
}

void PRIVMSG(Client &client, std::vector<std::string>& commands)
{
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":serverIRC 461 " + client.getNickname() + " PRIVMSG :Not enough parameters\r\n";
		client.sendToClientMessage(error);
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