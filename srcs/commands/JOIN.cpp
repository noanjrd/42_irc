/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 15:57:46 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void JOIN(Client &client, std::string &commands)
{
	int words = count_words(commands);
	if (words != 2)
	{
		std::cerr << "Not enough words" << std::endl;
	}
	else
	{
		std::string chanelname = get_word(commands,2);
		if (chanelname[0] != '#')
		{
			std::cerr << "Missing #";
			return ;
		}
		chanelname = chanelname.substr(1);
		Chanel * chaneltemp = strChaneltoChanelType(client.getServer() ,chanelname);
		if (chaneltemp == NULL)
		{
			Chanel* newchannel = new Chanel(chanelname, client);
			client.getServer().getChanels().push_back(newchannel);
			client.getServer().getUChanelsName().push_back(chanelname);
		}
		else
		{
			try
			{
				chaneltemp->JoinChanel(client);
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	return ;
}