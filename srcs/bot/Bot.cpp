/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:08:58 by naankour          #+#    #+#             */
/*   Updated: 2026/02/23 11:15:53 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		std::cerr << " Wrong number of arguments" << std::endl;
		return (1);
	}

	int botFd = socket(AF_INET, SOCK_STREAM, 0); //creer un socket IPv4 qui utilise TCP
	if (botFd < 0)
		return (1);

	sockaddr_in addr;// structure pour IPv4 qui contient une addr IP un port et un type de reseau
	std::memset(&addr, 0, sizeof(addr));//pour eviter des valeurs aleatoire on met tout a 0
	addr.sin_family = AF_INET; //correspond a IPv4
	addr.sin_port = htons(atoi(argv[2])); //definition du port du serveur // htons =Host TO Network Short
	
	if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0)
	{
		close(botFd);
    	return (1);
	}

	if (connect(botFd, (sockaddr*)&addr, sizeof(addr)) < 0) // pour que ce socket soit connecte a ce server, a cette adresse, et ce port
	{
		close(botFd);
		return (1);
	}	
	
	std::string pass = "PASS " + std::string(argv[3]) + "\r\n";
	std::string nick = "NICK bot\r\n";
	std::string user = "USER bot 0 * :bot\r\n";

	send(botFd, pass.c_str(), pass.size(), 0);
	send(botFd, nick.c_str(), nick.size(), 0);
	send(botFd, user.c_str(), user.size(), 0);

	char buffer[512];
	while(true)
	{
		std::memset(buffer, 0, sizeof(buffer));
		int bytes = recv(botFd, buffer, sizeof(buffer) - 1, 0);
		if (bytes <= 0)
			break;
		
		std::string message = buffer;
		std::cout << message << std::endl;

		if (message.find(" 001 ") != std::string::npos)
		{
			std::string join = "JOIN #test\r\n";
			send(botFd, join.c_str(), join.size(), 0);
		}
		if (message.find("PRIVMSG #test") != std::string::npos)
		{
			if (message.find("Hi bot") != std::string::npos)
			{
				std::string response = "PRIVMSG #test :Hi human\r\n";
				send(botFd, response.c_str(), response.size(), 0);
			}
		}
	}
	close(botFd);
	return (0);	
}