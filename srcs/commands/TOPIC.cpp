/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:35:37 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 16:02:04 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void TOPIC(Client &client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string chanel;
	chanel = get_word(commands, 2);
	
	if (chanel[0] != '#')
	{
		std::cerr << "Missing #" << std::endl;
		return ;
	}
	int i = 3;
	std::string topic;
	topic = get_word(commands, 2);
	while (i <= words)
	{
		topic += get_word(commands,i);
		i++;
	}
	return;
}

