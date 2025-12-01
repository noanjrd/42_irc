/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:04:17 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:40:07 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"

// AF_INET --> IPv4
// SOCK_STREAM --> TCP
// INADDR_ANY --> accepte la connexion depuis n importe quel adresse ip
// POLLIN --> constante de valeur 0b000001 qui veut dire que il y a des données disponibles à lire sur le socket

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	(void)argv;
	int port = atoi(argv[1]);
	std::string password = argv[2];
	int server_fd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in address; // definition adresse du serveur
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	bind(server_fd, (struct sockaddr*)&address, sizeof(address)); // associce le socket a l adrsse
	listen(server_fd, 99); //socket ouvert pret a ecouter, 99 est le nb max de connections avant la file d attente
	Server server(server_fd, port, password);

	initpoll(server);

	// close()
	return 0;
}
