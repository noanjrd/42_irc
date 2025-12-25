/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/25 14:40:15 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void split_message(std::string commands, Client &client)
{
	std::cout << "Entire command :" << commands << std::endl;
	int i = 0;
	std::string line;
	if (commands.length() == 0)
		return ;
	while (commands[i])
	{
		line+=commands[i];
		if (commands[i] ==  '\n' || commands[i] == '\r')
		{
			process_mess(line, client);
			while(commands[i] && (commands[i] ==  '\n' || commands[i] == '\r'))
			{
				if (!commands[i])
				{
					break;
				}
				i++;
			}
			line = "";
			continue;
		}
		i++;
	}
}

void process_mess(std::string commands, Client &client) // ici on pourra faire des pointeurs sur fonctions
{
	std::cout << "splited command :" << commands << std::endl;
	std::string command = get_word(commands, 1);
	if (command.empty())
	{
		std::cerr << "Empty input" << std::endl;
		return ;
	}
	if (command == "auto") // tu peux utiliser la commande auto ou auto2 pour pas avoir a faire la configuration du client
	{
		client.autoconfigure();
	}
	if (command == "auto2")
	{
		client.autoconfigure2();
	}
	if (client.getAuthenticated() == false)
	{
		client.authentication(commands);
		return ;
	}
	if (client.getConfigured() == false)
	{
		client.configure(commands);
		return ;
	}
	if (command == "JOIN")
	{
		JOIN(client, commands);
	}
	if (command == "NAMES")
	{
		NAMES(client, commands);
		return ;	
	}
	if (command == "KICK")
	{
		KICK(client, commands);
		return ;
	}
	if (command == "TOPIC")
	{
		TOPIC(client, commands);
		return ;
	}
	if (command == "PRIVMSG")
	{
		std::cout << "Here" << std::endl;
		PRIVMSG(client, commands);
		return ;
	}
	return ;
}