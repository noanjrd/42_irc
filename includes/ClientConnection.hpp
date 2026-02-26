/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:42:13 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 14:06:46 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <poll.h>

#include "Client.hpp"

class ClientConnection
{
	private:
		Client client;
		pollfd pfd;

	public:
		ClientConnection(Client client, pollfd pfd);
		~ClientConnection();
		Client& getClient();
		pollfd& getPollfd();
};