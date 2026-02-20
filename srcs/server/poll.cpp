/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:08 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 16:20:38 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void initpoll(Server &server)
{
	pollfd server_poll; // tableau de pollfd
	server_poll.fd = server.getFd(); //socket a surveiller donc notre server
	server_poll.events = POLLIN; // on veut savoir quan dun client se connecte, on dit au poll quel evenement ecouter, ici POLLIN
	// events c ets ce qu on dedmande a poll de surveiller
	// POLLIN = lire des donnes
	// POLLOUT  =  envoyer/ecrire des donnes

	while(g_running)
	{
		std::vector<pollfd> watchedSockets; // vecteur dasn lequel on va mettre les sockets a surveiller
		watchedSockets.push_back(server_poll);// on y ajouter le server

		for (size_t i = 0; i < server.getClient_connexions().size(); i++)
		{
			ClientConnexion* clientTemp = server.getClient_connexions()[i];
			clientTemp->getPollfd().events = POLLIN;

			if (clientTemp->getClient().isBufferToReceiveEmpty() == false)
			{
				clientTemp->getPollfd().events |= POLLOUT;
			}
			watchedSockets.push_back(clientTemp->getPollfd());
			
		}// on ajoute le socket de chaque client connectes dans le vecter de sockets a surveiller 
		
		// poll retourne le nb de de sockets qui ont un evenement et prend en param, le tab de sockets a surveiller,
		// le nb delements dasn le tab, et -1 = attendre jusqua qu un event se produise
		// sans poll le recv d en dessou trounerai indefiniment
		// si poll en recoit rien la suite du code n est pas executé
		// c est poll qui modifie les .revents en focntion de ce quui le pollfd a dans events et de l espoire memoir
		int waiting_socket = poll(watchedSockets.data(), watchedSockets.size(), -1);
		
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
		if (watchedSockets[0].revents & POLLIN)  //revents c est quel revenement a reelement eu lieu
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
			new_client.setBufferToReceive("PING :irc.server\r\n");
			pollfd  pollclient;
			pollclient.fd = client_fd;
			pollclient.events = POLLIN;
			ClientConnexion* temp = new ClientConnexion(new_client, pollclient);
			server.getClient_connexions().push_back(temp);
		}

		for (long unsigned int i = 1; i < watchedSockets.size(); i++)
		{
			if (!(watchedSockets[i].revents & POLLIN))
				continue;

			std::string entiremessage = "";

			char buff[4000];
			//recv lit les donnees encoyees par le client sur le socket
			//buff buffer sur lequel on stocke ces donnes 
			int bytes = recv(watchedSockets[i].fd, buff, sizeof(buff),0);
			
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
		for (long unsigned int i = 1; i < watchedSockets.size(); i++)
		{
			if (!(watchedSockets[i].revents & POLLOUT))
				continue;
			
			Client& receiver = server.getClient_connexions()[i-1]->getClient();
			int sent = send(receiver.getFd(),receiver.getBufferToReceive().c_str(),receiver.getBufferToReceive().length(),0 );
			if (sent > 0)
			{
				receiver.clearBufferToReceive();
			}
		}
	}
	std::cout << "Serveur arrêté proprement.\n";
}
