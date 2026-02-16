/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:42:20 by naziha            #+#    #+#             */
/*   Updated: 2026/02/16 11:41:24 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

//INVITE <nickname> <#channel>

void INVITE(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words != 3)
    {
        std::string error = ":server 461 " + client.getNickname() + " INVITE :Not enough parameters\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }

    std::string nick = get_word(commands, 2);
    if (client.getServer().isNicknameInServer(nick) == false)
    {
        std::string error = ":server 401 " + client.getNickname() + " " + nick + " :No such nick\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }

    std::string channelName = get_word(commands, 3);
    if (channelName.empty() || channelName[0] != '#')
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    channelName = channelName.substr(1);

    Chanel* channel = strChaneltoChanelType(client.getServer(), channelName);
    if (!channel)
    {
        std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    if (channel->isUserInChanel(client) == false)
    {
        std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    if (channel->isInviteOnly() && (channel->isUserOperator(client) == false))
    {
        std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    if (channel->isUserInChannelByNick(nick))
    {
        std::string error = ":server 443 " + client.getNickname() + " " + nick + " #" + channelName + " :is already on channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }

    Client* invitedClient = client.getServer().getClientByNick(nick);
    if (!invitedClient)
    {
        std::string error = ":server 401 " + client.getNickname() + " " + nick + " :No such nick\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    channel->addInvite(nick);


    std::string messageUser = ":server 341 " + client.getNickname() + " " + nick + " #" + channelName + "\r\n";
    send(client.getFd(), messageUser.c_str(), messageUser.size(), 0);

    std::string messageInvite = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost INVITE " + nick + " #" + channelName + "\r\n";
    send(invitedClient->getFd(), messageInvite.c_str(), messageInvite.length(), 0);
}