/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:27:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/01 16:17:16 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <poll.h>
#include <algorithm>

#include "Client.hpp"
#include "Server.hpp"
#include "Chanel.hpp"

// SERVER

int process_mess(std::string message, Client &client);
void initpoll(Server &server);