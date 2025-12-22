/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 16:17:02 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void KICK(Client& client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3 or words > 4)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string chanel = get_word(commands,2);
	if (chanel[0] != '#')
	{
		std::cerr << "Missing #" << std::endl;
		return ;
	}
	chanel = chanel.substr(1);
	std::string username = get_word(commands, 2);
	if (isUserInServer(client.getServer(), username) ==  false)
	{
		std::cerr << "User not in server" << std::endl;
		return ;
	}
	std::string reason;
	if (words == 4)
	{
		reason = get_word(commands, 4);
	}
	
	
	return ;
}