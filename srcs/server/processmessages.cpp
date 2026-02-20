/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 16:07:21 by njard            ###   ########.fr       */
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
	line = client.getCommandLineCtrlD();
	if (line.length() > 0)
	{
		line += " ";
		client.setCommandLineCtrlD("");
	}
	while (commands[i])
	{
		line+=commands[i];
		if (commands[i] ==  '\n' || commands[i] == '\r')
		{
			process_mess(line, client);
			while(commands[i] && (commands[i] ==  '\n' || commands[i] == '\r'))
			{
				i++;
			}
			line = "";
			continue;
		}
		i++;
	}
	if (line.length() > 0)
	{
		client.setCommandLineCtrlD(line);
	}
}

std::vector<std::string> convert_into_vector(const std::string& s)
{
	int i  = 0;
	bool letter = 0;
	int start = -99;
	std::vector<std::string> result;
	while(s[i])
	{
		if (!std::isspace(s[i]) && letter == 0)
		{
			letter = 1;
			start = i;
		}
		if (std::isspace(s[i]) && letter == 1)
		{
			result.push_back(s.substr(start, i-start));
			letter = 0;
		}
		i++;
	}
	if (i >= 1 && !std::isspace(s[i-1]) && letter == 1)
	{
		result.push_back(s.substr(start,i-start));
	}
	return result;
}

void process_mess(std::string commands, Client &client)
{
	std::cout << "splited  vector :" << std::endl;
	std::vector<std::string> commandsVector = convert_into_vector(commands);
	for (unsigned long i = 0; i < commandsVector.size() ;i++)
	{
		std::cout << commandsVector[i] << std::endl;
	}

	if (commands.empty() || commandsVector.size() < 1)
	{
		std::cerr << "Empty input" << std::endl;
		return ;
	}
	if (commandsVector[0] == "auto") // tu peux utiliser la commande auto ou auto2 pour pas avoir a faire la configuration du client
	{
		client.autoconfigure();
	}
	if (commandsVector[0]  == "auto2")
	{
		client.autoconfigure2();
	}
	if (client.getAuthenticated() == false)
	{
		client.authentication(commandsVector);
		return ;
	}
	if (client.getConfigured() == false)
	{
		client.configure(commandsVector);
		return ;
	}
	if (commandsVector[0] == "WHO")
	{
		NAMES(client, commandsVector);
		return ;
	}
	void (*functions[10])(Client&, std::vector<std::string>&) = {JOIN, KICK, PRIVMSG, NAMES, TOPIC, INVITE, PART, QUIT, MODE, PING};
	std::string functions_name[10] = {"JOIN", "KICK", "PRIVMSG", "NAMES", "TOPIC", "INVITE", "PART", "QUIT", "MODE", "PING"};
	for (int i = 0; i < 10; i++)
	{
		if (commandsVector[0] == functions_name[i])
		{
			(functions)[i](client, commandsVector);
			break;
		}
	}
	return ;
}