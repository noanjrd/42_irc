/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:41:16 by njard             #+#    #+#             */
/*   Updated: 2025/12/18 16:56:41 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void NAMES(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words != 2)
    {
        std::cerr << "Not enough words" << std::endl;
    }
    std::string channelname = get_word(commands, 2);
    for (std::vector<Chanel>::iterator it ; it != client.getServer().getChanels().end(); it++)
    {
        if ((*it).getName() == channelname)
        {
        }
    }
}