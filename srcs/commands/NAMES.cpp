/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:41:16 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 13:48:35 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// NAMES <channel>

void NAMES(Client& client, std::vector<std::string>& commands)
{
    int countWords = commands.size();
    if (countWords != 2)
    {
        std::string error = ":server 461 " + client.getNickname() + " NAMES :Not enough parameters\r\n";
        client.sendToClientMessage(error);
        return ;
    }

    std::string channelName = commands[1];
    if (channelName[0] != '#')
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        client.sendToClientMessage(error);
        return ;
    }
    channelName = channelName.substr(1);

    Channel* channel = strChanneltoChannelType(client.getServer(), channelName);
    if (channel == NULL)
    {
        std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
        client.sendToClientMessage(error);
        return ;
    }
    
    std::string message = ":server 353 " + client.getNickname() + " = #" + channelName + " :";
    
    std::vector<std::pair<Client *, int> >& users = channel->getClients();
    for (size_t index = 0; index < users.size(); index++)
    {
        std::string userNickname = "";
        if (index != 0)
            userNickname += " ";
        if (users[index].second == OPERATORS)
            userNickname += "@" + users[index].first->getNickname();
        else
            userNickname += users[index].first->getNickname();
        message += userNickname;
    }
    message += "\r\n";
    client.sendToClientMessage(message);

    std::string endMessage = ":server 366 " + client.getNickname() + " #" + channelName + " :End of /NAMES list\r\n"; // a verifier pour le \n avec le client test
    client.sendToClientMessage(endMessage);
}