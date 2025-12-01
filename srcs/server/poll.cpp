/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:08 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:04:18 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void initpoll(Server &server)
{
	std::vector<pollfd> watched_socket;
	pollfd server_poll;
	server_poll.fd = server.getFd();
	server_poll.events = POLLIN; // on dit au poll quelle evenement ecouter, ici POLLIN
	watched_socket.push_back(server_poll);
	std::vector<Client> clients;

	while(true)
	{
		int waiting_socket = poll(watched_socket.data(), watched_socket.size(), -1);
		if (waiting_socket < 0)
		{
			std::cout << "Error" << std::endl;
			continue;
		}
		if (watched_socket[0].revents & POLLIN)  // revents c est quel revenement a reelement eu lieu
		{
			int client_fd = accept(server.getFd(), NULL, NULL);
			if (client_fd < -1)
			{
				std::cout << "error" << std::endl;
				continue;
			}
			Client new_client(client_fd, server);
			clients.push_back(new_client);
			pollfd  clienttemp;
			clienttemp.fd = client_fd;
			clienttemp.events = POLLIN;
			watched_socket.push_back(clienttemp);
		}
		for (long unsigned int i = 1; i < watched_socket.size(); i++)
		{
			if (!(watched_socket[i].revents & POLLIN))
				continue;
			std::string entiremessage = "";
			char buff[4000];
			int bytes = recv(watched_socket[i].fd,buff,sizeof(buff),0);
			if (bytes <= 0) // verifie si le il y a une erreur ou que le client est deconnecte
			{
				// je dois supprimer le client des listes et fermer son fd
				break;
			}
			buff[bytes] = 0;
			entiremessage += buff;
			std::cout << entiremessage;
			process_mess(entiremessage, clients[i-1]);
		}
		
	}
}
