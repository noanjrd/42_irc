/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:04:17 by njard             #+#    #+#             */
/*   Updated: 2025/11/27 15:27:12 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>

// AF_INET --> IPv4
// SOCK_STREAM --> TCP
// INADDR_ANY --> accepte la connexion depuis n importe quel adresse ip

#include "../includes/Client.hpp"


int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	(void)argv;
	int port = atoi(argv[1]);
	std::string passwd = argv[2];
	int server_fd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in address; // definition adresse du serveur
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	bind(server_fd, (struct sockaddr*)&address, sizeof(address)); // associce le socket a l adrsse
	listen(server_fd, 99); //socket ouvert pret a ecouter, 3 est le nb max de connections avant la file d attente
	int addrlen = sizeof(address);
	int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen); // accepte bloque le programme jusqu a ce qu un client se connecte 
	// socket retourner par accept pour communiquer avec le client connecter precis

	char message[] = "Hello client!\n";
    send(new_socket, message, strlen(message), 0);

	sleep(2);
    close(new_socket);
    close(server_fd);
	return 0;
}
