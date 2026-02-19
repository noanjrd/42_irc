/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2026/02/19 12:01:16 by njard            ###   ########.fr       */
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
		if (std::isspace(s[i]))
		{
			result.push_back(s.substr(start, i-start));
			letter = 0;
		}
		i++;
	}
	if (i >= 1 && !std::isspace(s[i-1]))
	{
		if (start != -99)
		{
			result.push_back(s.substr(start,i-start));
		}
	}
	return result;
}

void process_mess(std::string commands, Client &client) // ici on pourra faire des pointeurs sur fonctions
{
	std::cout << "splited  vector :" << std::endl;
	std::vector<std::string> commands_vector = convert_into_vector(commands);
	for (unsigned long i = 0; i < commands_vector.size() ;i++)
	{
		std::cout << commands_vector[i] << std::endl;
	}
	std::cout << "end\n";
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
	void (*functions[9])(Client&, std::vector<std::string>&) = {JOIN, KICK, PRIVMSG, NAMES, TOPIC, INVITE, PART, QUIT, MODE};
	std::string functions_name[9] = {"JOIN", "KICK", "PRIVMSG", "NAMES", "TOPIC", "INVITE", "PART", "QUIT", "MODE"};
	for (int i = 0; i < 9; i++)
	{
		if (command == functions_name[i])
		{
			(functions)[i](client, commands_vector);
			break;
		}
	}
	return ;
}