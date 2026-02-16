/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:41:16 by njard             #+#    #+#             */
/*   Updated: 2026/02/16 11:42:56 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void NAMES(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words != 2)
    {
        std::string error = ":server 461 " + client.getNickname() + " NAMES :Not enough parameters\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }

    std::string channelName = get_word(commands, 2);
    if (channelName.empty() || channelName[0] != '#')
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    channelName = channelName.substr(1);

    Chanel* channel = strChaneltoChanelType(client.getServer(), channelName);
    if (channel == NULL)
    {
        std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    
    std::string message = ":server 353 " + client.getNickname() + " = #" + channelName + " :";
    
    std::vector<std::pair<Client *, int> >& users = channel->getClients();
    for (size_t index = 0; index < users.size(); index++)
    {
        std::string nametemp = "";
        if (index != 0)
            nametemp += " ";
        if (users[index].second == OPERATORS)
            nametemp += "@" + users[index].first->getNickname();
        else
            nametemp += users[index].first->getNickname();
        message += nametemp;
    }
    message += "\r\n";
    send(client.getFd(), message.c_str(), message.length(), 0);

    std::string endMessage = ":server 366 " + client.getNickname() + " #" + channelName + " :End of /NAMES list\r\n"; // a verifier pour le \n avec le client test
    
    send(client.getFd(), endMessage.c_str(), endMessage.length(), 0);
}

// :irc.localhost 335 user = #chaneelname : @
// :irc.localhost 366 user #chanelname