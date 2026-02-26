/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessMessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:37:35 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

void splitMessage(std::string commands, Client &client)
{
	int i = 0;
	std::string line;
	if (commands.length() == 0)
		return ;
	line = client.getCommandLineCtrlD();
	if (line.length() > 0)
		client.setCommandLineCtrlD("");
	while (commands[i])
	{
		line+=commands[i];
		if (commands[i] ==  '\n' || commands[i] == '\r')
		{
			processMessage(line, client);
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
		client.setCommandLineCtrlD(line);
}

void processMessage(std::string commands, Client &client)
{
	std::cout << "splited  vector :" << std::endl;
	std::vector<std::string> commandsVector = convertToVector(commands);
	for (unsigned long i = 0; i < commandsVector.size() ;i++)
	{
		std::cout << commandsVector[i] << std::endl;
	}

	if (commands.empty() || commandsVector.size() < 1)
	{
		std::cerr << "Empty input" << std::endl;
		return ;
	}
	if (commandsVector[0] == "QUIT")
	{
		QUIT(client, commandsVector);
		return ;
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
	void (*functions[9])(Client&, std::vector<std::string>&) = {JOIN, KICK, PRIVMSG, NAMES, TOPIC, INVITE, PART, MODE, NAMES};
	std::string functions_name[9] = {"JOIN", "KICK", "PRIVMSG", "NAMES", "TOPIC", "INVITE", "PART", "MODE", "WHO"};
	for (int i = 0; i < 9; i++)
	{
		if (commandsVector[0] == functions_name[i])
		{
			(functions)[i](client, commandsVector);
			break;
		}
	}
	return ;
}