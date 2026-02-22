/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:42:20 by naziha            #+#    #+#             */
/*   Updated: 2026/02/22 14:48:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

//INVITE <nickname> <#channel>

void INVITE(Client& client, std::vector<std::string>& commands)
{
    int countWords = commands.size();
    if (countWords != 3)
    {
        std::string errorMessage = ":serverIRC 461 " + client.getNickname() + " INVITE :Not enough parameters\r\n";
        client.sendToClientMessage(errorMessage);
        return ;
    }

    std::string nickname = commands[1];
    if (client.getServer().isNicknameInServer(nickname) == false)
    {
        std::string errorMessage = ":serverIRC 401 " + client.getNickname() + " " + nickname + " :No such nick\r\n";
        client.sendToClientMessage(errorMessage);
        return;
    }

    std::string channelName = commands[2];
    if (channelName[0] != '#')
    {
        std::string errorMessage = ":serverIRC 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        client.sendToClientMessage(errorMessage);
        return ;
    }
    channelName = channelName.substr(1);

    Channel* channel = strChanneltoChannelType(client.getServer(), channelName);
    if (!channel)
    {
        std::string errorMessage = ":serverIRC 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
        client.sendToClientMessage(errorMessage);
        return ;
    }
    if (!channel->isUserInChannel(client))
    {
        std::string errorMessage = ":serverIRC 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
        client.sendToClientMessage(errorMessage);
        return;
    }
    if (channel->isInviteOnly() && !channel->isUserOperator(client))
    {
        std::string errorMessage = ":serverIRC 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
        client.sendToClientMessage(errorMessage);
        return;
    }
    if (channel->isUserInChannelByNick(nickname))
    {
        std::string errorMessage = ":serverIRC 443 " + client.getNickname() + " " + nickname + " #" + channelName + " :is already on channel\r\n";
        client.sendToClientMessage(errorMessage);
        return;
    }

    Client* invitedClient = client.getServer().getClientByNick(nickname);
    if (!invitedClient)
    {
        std::string errorMessage = ":serverIRC 401 " + client.getNickname() + " " + nickname + " :No such nick\r\n";
        client.sendToClientMessage(errorMessage);
        return;
    }
    channel->addInvite(nickname);


    std::string messageUser = ":serverIRC 341 " + client.getNickname() + " " + nickname + " #" + channelName + "\r\n";
    client.sendToClientMessage(messageUser);

    std::string messageInvite = ":" + client.getNickname() + "!" + client.getUsername() + "@serverIRC INVITE " + nickname + " #" + channelName + "\r\n";
    invitedClient->sendToClientMessage(messageInvite);
}
