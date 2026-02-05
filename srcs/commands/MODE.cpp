/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:30:27 by naankour          #+#    #+#             */
/*   Updated: 2026/02/05 14:57:23 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"
// MODE #channel -mode param
void MODE(Client& client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "461 MODE :Not enough parameters" << std::endl;
		return ;
	}

	std::string channelName = get_word(commands, 2);
	if (channelName.empty() || channelName[0] != '#')
	{
		std::cerr << "403 :'#' is missing" << std::endl;
		return ;
	}
	channelName = channelName.substr(1);
	
	std::string modeT = get_word(commands, 3);
	if (modeT.size() != 2)
	{
		std::cerr << "format mode must be '-' or '-' then a letter" << std::endl;
		return;
	}
	if (modeT[0] != '+' && modeT[0] != '-')
	{
		std::cerr << "472 :mode must start with '-' or '+'" << std::endl;
		return ;
	}
	char sign = modeT[0];
	char mode = modeT[1];
	
	if (mode != 'i' && mode != 't' && mode != 'k' && mode != 'l' && mode != 'o')
	{
		std::cerr << "472 :Unkwown mode" << std::endl;
		return;
	}

	std::string param;
	if (mode == 'i' || mode == 't')
	{
		if (words >= 4)
		{
			std::cerr << "461 : no param needed for this mode" <<std::endl;
			return;
		}
	}
	else
	{	
		if (words < 4)
		{
			std::cerr << "461 MODE :Not enough parameters" << std::endl;
			return;
		}

		size_t pos = commands.find(modeT);
		if (pos != std::string::npos)
		{
			pos += modeT.size();
			param = commands.substr(pos);

			while (!param.empty() && param[0] == ' ')
				param.erase(0, 1);
			if (!param.empty() && param[0] == ':')
				param = param.substr(1);
			else
				param = get_word(commands, 4);
		}
	}

	Chanel* channel = strChaneltoChanelType(client.getServer(), channelName);
	if (!channel)
	{
		std::cerr << "403 " << channelName << " :No such channel" << std::endl;
		return ;
	}
	if (channel->isUserInChanel(client) == false)
	{
		std::cerr << "442 " << channelName << " :You're not on that channel" << std::endl;
		return ;
	}
	if (channel->isUserOperator(client) == false)
	{
		std::cerr << "482 " << channelName << " :You're not channel operator" << std::endl;
    	return;
	}
	if (mode == 'i')
	{
		if (sign == '+')
			channel->setInviteOnly(true);
		else
			channel->setInviteOnly(false);
//:Nick!user@host MODE #channel +i
	}
	else if (mode == 't')
	{
		if (sign == '+')
			channel->setTopicProtected(true);
		else
			channel->setTopicProtected(false);
	}
	else if (mode == 'k')
	{
		if (sign == '+')
		{
			if (param.empty())
			{
				std::cerr << "461 MODE :password is empty";
				return;
			}
			channel->sethasPassword(true);
			channel->setPassword(param);
		}
		else
		{
			channel->sethasPassword(false);
			channel->setPassword("");
		}
	}
	else if (mode == 'l')
	{
		if (sign == '+')
		{
			if (param.empty())
			{
				std::cerr << "461 MODE :limit is empty";
				return;
			}
			for (size_t i = 0; i < param.size(); i++)
			{
				if (!isdigit(param[i]))
				{
					std::cerr << "461 MODE :limit must be a positive number" << std::endl;
					return;
				}
			}

			int limit = atoi(param.c_str());
			if (limit <= 0)
			{
				std::cerr << "461 MODE :limit must be greater than 0" << std::endl;
				return;
			}
			channel->sethasAUserLimit(true);
			channel->setUserLimit(limit);
		}
		else
			channel->sethasAUserLimit(false);
			
		std::string reply = ":localhost 324 " + client.getNickname() + " #" + channelName + " " + sign + mode;
		if (!param.empty())
			reply += " " + param;
		reply += "\r\n";

		send(client.getFd(), reply.c_str(), reply.length(), 0);
	}

	
	std::cout << "Channel: " << channelName << "\n";
	std::cout << "Mode: " << sign << mode << "\n";
	if (!param.empty())
		std::cout << "Param: " << param << "\n";
}