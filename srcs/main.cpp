/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:04:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:35:07 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.hpp"

int main(int argc, char** argv)
{
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);
	signal(SIGPIPE, SIG_IGN);
	
	if (argc != 3)
	{
		std::cerr << "Wrong number of arguments." << std::endl;
		std::cerr << "Format: <port> <server_password>" << std::endl;
		return 1;
	}
	
	int port = atoi(argv[1]);
	if (port >= 0 && port <= 1023)
	{
		std::cerr << "This port is reserved to the system." << std::endl;
		std::cerr << "Please enter a port between 1023 and 65535." << std::endl;
		return 1;
	}
	if (port < 0 || port > 65535)
	{
		std::cerr << "Please enter a port between 1023 and 65535." << std::endl;
		return 1;
	}
	std::cout << "Server is being executed. Type Ctrl+C to stop it.\n";

	std::string password = argv[2];

	int serverFd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	int opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		close(serverFd);
		std::cerr << "Problem with setsockopt function, server exited successfully !" << std::endl;
		exit(1);
	}
	if (bind(serverFd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		close(serverFd);
		std::cerr << "Problem with bind function, server exited successfully !" << std::endl;
		exit(1);
	}
	if (listen(serverFd, 1) < 0) 
	{
		close (serverFd);
		std::cerr << "Problem with listen function, server exited successfully !" << std::endl;
		exit(1);
	}
	Server server(serverFd, port, password);
	pollLoop(server);
	return 0;
}