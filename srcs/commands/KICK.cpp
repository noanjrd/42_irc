/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/05 14:43:51 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// KICK <#channel> <user> [<reason>]

void KICK(Client& client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}

	std::string chanel = get_word(commands, 2);
	if (chanel[0] != '#')
	{
		std::cerr << "Missing #" << std::endl;
		return ;
	}
	chanel = chanel.substr(1);
	
	std::string username = get_word(commands, 3);
	
	std::string reason;
	size_t pos = commands.find(':');
	if (pos != std::string::npos)
		reason = commands.substr(pos + 1);
	else
		reason = "No reason";
	reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
	reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());

	// if ((client.getServer().isChanelExist(chanel) == false))
	// {
	// 	std::cerr << "Chanel does not exist" << std::endl;
	// 	return ;
	// }

	// if (client.getServer().isUserNameInServer(username) ==  false)
	// {
	// 	std::cerr << "User not in server" << std::endl;
	// 	return ;
	// }

	std::vector<Chanel*>& allChannels = client.getServer().getChanels();
	for (size_t i = 0; i < allChannels.size(); i++)
	{
		if (allChannels[i]->getName() == chanel)
		{
			if (allChannels[i]->isUserInChanel(client) == false)
			{
				std::cerr << "You are not in the channel" << std::endl;
				return ;
			}
			if (allChannels[i]->isUserOperator(client) == false)
			{
				std::cerr << "You are not operator" << std::endl;
				return ;
			}
		
			std::vector<std::pair<Client*, int> >& clientsInChannel = allChannels[i]->getClients();
			for (size_t j = 0; j < clientsInChannel.size(); j++)
			{
				if (clientsInChannel[j].first->getNickname() == username)
				{
					std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " KICK #" + chanel + " " + username + " :" + reason + "\r\n";
					allChannels[i]->sendMessageToAllQuit(client, finalMessage);
					allChannels[i]->removeClient(*(clientsInChannel[j].first));
					return ;
				}
			}	
			std::cerr << "User not in channel" << std::endl;
			return ;
		}
	}
}