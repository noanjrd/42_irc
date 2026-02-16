/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:15:42 by njard             #+#    #+#             */
/*   Updated: 2026/02/16 11:42:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void PRIVMSG(Client &client, std::string& commands)
{
	// std::cerr << "commands :" + commands << std::endl;
	int words = count_words(commands);
	if (words < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " PRIVMSG :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	int i = 3;
	std::string message = "";
	while (i <= words)
	{
		message+= " " + get_word(commands, i);
		i++;
	}
	if (message[1] != ':')
	{
		std::cerr << "Error syntax message" << std::endl;
		return ;
	}
	message = message.substr(2);
	std::string destination = get_word(commands, 2);
	if (destination[0] == '#')
	{
		destination = destination.substr(1);
		Chanel *chaneltemp = strChaneltoChanelType(client.getServer(), destination);
		if (chaneltemp == NULL)
		{
    		std::string error = ":server 403 " + client.getNickname() + " #" + destination + " :No such channel\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return ;
		}
		if (chaneltemp->isUserInChanel(client) == false)
		{
			std::string error = ":server 404 " + client.getNickname() + " #" + destination + " :Cannot send to channel\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return ;
		}
		chaneltemp->sendMessageToAll(client, message);
	}
	else
	{
		// std::cerr << "dest : " << destination << std::endl;
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
	// std::cout << "finished privmsg" << std::endl;
	return ;
}