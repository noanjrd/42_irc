/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 16:39:03 by njard            ###   ########.fr       */
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
		std::vector<std::string> chanels_list_name = client.getServer().getUChanelsName();
		std::vector<std::string>::iterator it = find(chanels_list_name.begin(), chanels_list_name.end(), chanelname);
		if (it == chanels_list_name.end())
		{
			Chanel newchannel(chanelname, client);
			client.getServer().getChanels().push_back(newchannel);
			client.getServer().getUChanelsName().push_back(chanelname);
		}
		else
		{
			int index = it - chanels_list_name.begin();
			try
			{
				client.getServer().getChanels()[index].JoinChanel(client);
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	return ;
}