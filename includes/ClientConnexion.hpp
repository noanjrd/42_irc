/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnexion.hpp                                :+:      :+:    :+:   */
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

class ClientConnexion
{
	private:
		Client client;
		pollfd pfd;

	public:
		ClientConnexion(Client client, pollfd pfd);
		~ClientConnexion();
		Client& getClient();
		pollfd& getPollfd();
};