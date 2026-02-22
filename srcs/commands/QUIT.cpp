/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:31:18 by naziha            #+#    #+#             */
/*   Updated: 2026/02/22 15:50:54 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

// QUIT \r\n
// QUIT :<message>\r\n
// QUIT mot\r\n

void QUIT(Client &client, std::vector<std::string> &commands)
{
    // int fd = client.getFd();
    int countWords = commands.size();

    std::string quitMessage;

    if (countWords > 1)
    {
        for (int i = 1 ; i < countWords; i++)
        {
            quitMessage += " " + commands[i];
        }
        quitMessage = quitMessage.substr(2);
    }
    else
        quitMessage = "Client Quit";

    quitMessage.erase(std::remove(quitMessage.begin(), quitMessage.end(), '\n'), quitMessage.end());
    quitMessage.erase(std::remove(quitMessage.begin(), quitMessage.end(), '\r'), quitMessage.end());

    if (client.getConfigured())
    {
        std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@serverIRC" + " QUIT :" + quitMessage + "\r\n";
        
        std::vector<Channel*> toRemove;
        std::vector<Channel*>& allChannels = client.getServer().getChannels();
        
        for (size_t i = 0; i < allChannels.size(); i++)
        {
            Channel* channel = allChannels[i];
            if (channel->isUserInChannel(client))
            {
                channel->sendMessageToAll(client, false, finalMessage);
                channel->removeClient(client);
                
                if (!channel->getClients().empty())
                {
                    if (channel->channelHasOperator() == false)
                        channel->giveOperator();
                }
                else
                    toRemove.push_back(channel);
            }
        }
        for (size_t i = 0; i < toRemove.size(); i++)
            client.getServer().removeChannel(toRemove[i]);
    }
    client.sendToClientMessage("The client quit");
    // close(fd);
}
