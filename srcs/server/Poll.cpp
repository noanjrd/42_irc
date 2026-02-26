/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:55:08 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:42:07 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

void pollLoop(Server &server)
{
	pollfd server_poll;
	server_poll.fd = server.getFd();
	server_poll.events = POLLIN; 

	std::vector<pollfd> watchedSockets;
	watchedSockets.push_back(server_poll);
	while(g_running)
	{
		for (size_t i = 0; i < server.getClient_connexions().size(); i++)
		{
			if (server.getClient_connexions()[i]->getClient().isBufferToReceiveEmpty() == false)
			{
				watchedSockets[i+1].events |= POLLOUT;
			}
		}
		
		int numFdsReady = poll(watchedSockets.data(), watchedSockets.size(), -1);
		if (numFdsReady < 0)
		{
			if (g_running == 0)
				break ;
			std::cout << "Error in poll()" << std::endl;
			continue;
		}

		for (long unsigned int i = 1; i < watchedSockets.size(); i++)
		{
			if (!(watchedSockets[i].revents & POLLIN))
				continue;

			char buff[4000];
			int bytes = recv(watchedSockets[i].fd, buff, sizeof(buff),0);
			if (bytes <= 0) 
			{
				watchedSockets.erase(watchedSockets.begin() + i);
				server.removeClient(server.getClient_connexions()[i-1]->getClient(), true);
				break;
			}
			
			buff[bytes] = 0;
			std::string messageToProcess = buff;
			splitMessage(messageToProcess, server.getClient_connexions()[i-1]->getClient());
		}

		for (long unsigned int i = 1; i < watchedSockets.size(); i++)
		{
			if (!(watchedSockets[i].revents & POLLOUT))
				continue;
			
			Client& receiver = server.getClient_connexions()[i-1]->getClient();
			if (receiver.getBufferToReceive() == "The client quit")
			{
				watchedSockets.erase(watchedSockets.begin() + i);
				server.removeClient(server.getClient_connexions()[i-1]->getClient(), true);
				break;
			}

			int sent = send(receiver.getFd(),receiver.getBufferToReceive().c_str(),receiver.getBufferToReceive().length(),0 );
			if (sent < 0)
			{
				watchedSockets.erase(watchedSockets.begin() + i);
				server.removeClient(server.getClient_connexions()[i-1]->getClient(), true);
				std::cerr << " Failed to send the message." << std::endl;
				break;
			}
			if (sent > 0)
			{
				receiver.clearBufferToReceive();
				watchedSockets[i].events = POLLIN;
			}
		}

		if (watchedSockets[0].revents & POLLIN)
		{
			
			int fdClient = accept(server.getFd(), NULL, NULL);
			if (fdClient < -1)
			{
				std::cout << "error" << std::endl;
				continue;
			}

			Client new_client(fdClient, server);
			pollfd  pollclient;
			pollclient.fd = fdClient;
			pollclient.events = POLLIN;
			ClientConnection* temp = new ClientConnection(new_client, pollclient);
			server.getClient_connexions().push_back(temp);
			watchedSockets.push_back(temp->getPollfd());
		}
	}
	std::cout << "Server stopped properly.\n";
}
