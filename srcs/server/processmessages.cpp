/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 12:38:24 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

int process_mess(std::string commands, Client &client)
{
	if (client.getAuthenticated() == false)
	{
		client.authentication(commands);
		return 0;
	}
	if (client.getConfigured() == false)
	{
		client.configure(commands);
		return 0;
	}
	std::string command = get_word(commands, 1);
	if (command.empty())
	{
		std::cerr << "Empty input" << std::endl;
		return 0;
	}
	if (command == "JOIN")
	{
		JOIN(client, commands);
		return 0;	
	}
	if (command == "PRIVMSG")
	{
		
	}
	std::cout << "Configured" << std::endl;
	
	return 0;
}