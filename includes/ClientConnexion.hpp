/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnexion.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:42:13 by njard             #+#    #+#             */
/*   Updated: 2025/12/04 11:14:59 by njard            ###   ########.fr       */
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