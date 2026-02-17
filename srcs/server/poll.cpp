/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:08 by njard             #+#    #+#             */
/*   Updated: 2026/02/17 15:12:28 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void initpoll(Server &server)
{
	pollfd server_poll; // tableau de pollfd
	server_poll.fd = server.getFd(); //socket a surveiller donc notre server
	server_poll.events = POLLIN; // on veut savoir quan dun client se connecte, on dit au poll quel evenement ecouter, ici POLLIN
	// POLLIN = qqn veut m envoyer qqc

	while(g_running)
	{
		std::vector<pollfd> watched_socket; // vecteur dasn lequel on va mettre les sockets a surveiller
		watched_socket.push_back(server_poll);// on y ajouter le server

		for (size_t i = 0; i < server.getClient_connexions().size(); i++)
		{
			watched_socket.push_back(server.getClient_connexions()[i]->getPollfd());
		}// on ajoute le socket de chaque client connectes dans le vecter de sockets a surveiller 
		
		// poll retourne le nb de de sockets qui ont un evenement et prend en param, le tab de sockets a surveiller,
		// le nb delements dasn le tab, et -1 = attendre jusqua qu un event se produise
		int waiting_socket = poll(watched_socket.data(), watched_socket.size(), -1);

		if (waiting_socket < 0)
		{
			if (g_running == 0)
				break ;
			std::cout << "Error in poll()" << std::endl;
			continue;
		}
		//on necrit pas dasn revents, cest poll qui le met a jour, nous on va juste le lire 
		// watched_socket[0] socket du server qui ecoute les nvlles connexions
		//revents variable remplie par poll qui indique quels evts se sont produits sur ce socket
		//POLLIN type d events quon surveille: ici = il y a qqc a lire
		if (watched_socket[0].revents & POLLIN)  //revents c est quel revenement a reelement eu lieu
		{
			//nvlle connexion donc on appelle accept pour l'accepter 
			//une nvlle connexion sur le socket du server
			
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
		}

		for (long unsigned int i = 1; i < watched_socket.size(); i++)
		{
			if (!(watched_socket[i].revents & POLLIN))
				continue;

			std::string entiremessage = "";

			char buff[4000];
			//recv lit les donnees encoyees par le client sur le socket
			//buff buffer sur lequel on stocke ces donnes 
			int bytes = recv(watched_socket[i].fd, buff, sizeof(buff),0);
			
			if (bytes <= 0) // verifie si le il y a une erreur ou que le client est deconnecte
			{
				// je dois supprimer le client des du sevreur et chanels et fermer son fd
				// close(watched_socket[i].fd);
				server.removeClient(server.getClient_connexions()[i-1]->getClient());
				break;
			}
			
			buff[bytes] = 0;
			entiremessage += buff;
			split_message(entiremessage, server.getClient_connexions()[i-1]->getClient());
		}	
	}
	std::cout << "Serveur arrêté proprement.\n";
}
