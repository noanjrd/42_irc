/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/11 13:35:35 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void JOIN(Client &client, std::string &commands)
{
	int words = count_words(commands);
	if (words < 2)
	{
		std::string error = ":server 461 " + client.getNickname() + " JOIN :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	
	std::string chanelname = get_word(commands, 2);
	if (chanelname.empty() || chanelname[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + chanelname + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	chanelname = chanelname.substr(1);

	std::string password;
	if (words >= 3)
		password = get_word(commands, 3);

	Chanel * chaneltemp = strChaneltoChanelType(client.getServer(), chanelname);
	if (chaneltemp == NULL)
	{
		Chanel* newchannel = new Chanel(chanelname, client);
		if (!password.empty())
		{
			newchannel->sethasPassword(true);
			newchannel->setPassword(password);
		}
		client.getServer().getChanels().push_back(newchannel);
		client.getServer().getUChanelsName().push_back(chanelname);
		return ;
	}
	if ((chaneltemp->isInviteOnly() == true) && (chaneltemp->isInvited(client.getNickname()) == false))
	{
		std::string error = ":server 473 " + client.getNickname() + " #" + chanelname + " :Cannot join channel (+i)\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	if ((chaneltemp->isHasPassword() == true) && (chaneltemp->checkPassword(password) == false))
	{
		std::string error = ":server 475 " + client.getNickname() + " #" + chanelname + " :Cannot join channel (+k)\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return;
	}
	if (chaneltemp->ishasAUserLimit() == true)
	{
		if (chaneltemp->getClients().size() >= chaneltemp->getUserLimit())
		{
			std::string error = ":server 471 " + client.getNickname() + " #" + chanelname + " :Cannot join channel (+l)\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return;
		}
	}
	try
	{
		chaneltemp->JoinChanel(client);
		if (chaneltemp->isInvited(client.getNickname()))
			chaneltemp->removeInvite(client.getNickname());
	}
	catch (std::exception &e)
	{
		std::string error = ":server 400 " + client.getNickname() + " :Error joining channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
	}
}