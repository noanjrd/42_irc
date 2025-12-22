/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:27:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/22 15:56:06 by njard            ###   ########.fr       */
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
#include <cctype>
#include <poll.h>
#include <algorithm>
#include <map>

#include "Client.hpp"
#include "Server.hpp"
#include "Chanel.hpp"
#include "ClientConnexion.hpp"

// ROLE

#define DEFAULT 0
#define OPERATORS 1

// JOIN

#define USER_JOINED(nick, user, chanel) ":" +nick + "!" + user  + "@host JOIN #" + chanel



// SERVER

int process_mess(std::string message, Client &client);
void split_message(std::string commands, Client &client);
void initpoll(Server &server);


// UTILS

int count_words(const std::string& s);
std::string get_word(const std::string& s, int location);
bool isstrdigit(const std::string& str);
bool isUserInServer(Server& server, std::string& username);
Chanel* strChaneltoChanelType(Server& server, std::string& chanelname);

// COMMANDS

void JOIN(Client &client, std::string &commands);
void NAMES(Client& client, std::string& commands);
void KICK(Client& client, std::string& commands);