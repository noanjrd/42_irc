/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:08 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 16:36:43 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void initpoll(Server &server)
{
	pollfd server_poll;
	server_poll.fd = server.getFd();
	server_poll.events = POLLIN; // on dit au poll quelle evenement ecouter, ici POLLIN

	while(true)
	{
		std::vector<pollfd> watched_socket;
		watched_socket.push_back(server_poll);
		for (size_t i = 0; i < server.getClient_connexions().size(); i++)
		{
			watched_socket.push_back(server.getClient_connexions()[i]->getPollfd());
		}
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
			pollfd  pollclient;
			pollclient.fd = client_fd;
			pollclient.events = POLLIN;
			ClientConnexion* temp = new ClientConnexion(new_client, pollclient);
			server.getClient_connexions().push_back(temp);
			// watched_socket.push_back(pollclienttemp);
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
			// entiremessage += "|";
			// std::cout << entiremessage ;
			// try{
			split_message(entiremessage, server.getClient_connexions()[i-1]->getClient());
			// }
			// catch (std::exception& e)
			// {
			// 	std::cerr << "Error : " << e.what() << std::endl;
			// }
		}
		
	}
}
