/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:42:20 by naziha            #+#    #+#             */
/*   Updated: 2026/02/05 13:46:42 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

//INVITE <nickname> <#channel>

void INVITE(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words != 3)
    {
        std::cerr << "461 INVITE :3 Parameters are needed" << std::endl;
        return ;
    }

    std::string nick = get_word(commands, 2);
    if (client.getServer().isUserNameInServer(nick) == false)
    {
        std::cerr << "User not in server" << std::endl;
        return ;
    }

    std::string channelName = get_word(commands, 3);
    if (channelName[0] != '#')
    {
        std::cerr << "403 :Missing #" << std::endl;
        return ;
    }
    channelName = channelName.substr(1);

    Chanel* channel = strChaneltoChanelType(client.getServer(), channelName);
    if (!channel)
    {
        std::cerr << "403 " << channelName << " :No such channel" << std::endl;
        return ;
    }
    if (channel->isUserInChanel(client) == false)
    {
        std::cerr << "442 " << channelName << " :You're not on that channel" << std::endl;
        return;
    }
    if (channel->isInviteOnly() && (channel->isUserOperator(client) == false))
    {
        std::cerr << "482 " << channelName << " :You're not channel operator" << std::endl;
        return;
    }
    if (channel->isUserInChannelByNick(nick))
    {
        std::cerr << "443 " << nick << " #" << channelName << " :is already on channel" << std::endl;
        return;
    }

    Client* invitedClient = client.getServer().getClientByNick(nick);
    if (!invitedClient)
    {
        std::cerr << "401 " << nick << " :No such nick" << std::endl;
        return;
    }
    channel->addInvite(nick);

    //msg de messageUseration a celui qui invite avec send 
    //message au client incite avec send
    std::string messageUser = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost INVITE " + nick + " #" + channelName + "\r\n";
    send(client.getFd(), messageUser.c_str(), messageUser.length(), 0);
    
    std::string messageInvite = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost INVITE " + nick + " #" + channelName + "\r\n";
    send(invitedClient->getFd(), messageInvite.c_str(), messageInvite.length(), 0);

}