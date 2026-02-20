/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:27:22 by njard             #+#    #+#             */
/*   Updated: 2026/02/20 13:52:01 by njard            ###   ########.fr       */
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
#include <signal.h>

#include "Client.hpp"
#include "Server.hpp"
#include "Chanel.hpp"
#include "ClientConnexion.hpp"

// SIGNALS

extern volatile sig_atomic_t g_running;
void handleSignal(int sig);

// ROLE

#define DEFAULT 0
#define OPERATORS 1

// SERVER

void process_mess(std::string message, Client &client);
void split_message(std::string commands, Client &client);
void initpoll(Server &server);


// UTILS

bool isstrdigit(const std::string& str);
Chanel* strChanneltoChannelType(Server& server, std::string& chanelname);

// COMMANDS

void JOIN(Client &client, std::vector<std::string> &commands);
void NAMES(Client& client, std::vector<std::string>& commands);
void KICK(Client& client, std::vector<std::string>& commands);
void TOPIC(Client &client, std::vector<std::string>& commands);
void PRIVMSG(Client &client, std::vector<std::string>& message);
void QUIT(Client &client, std::vector<std::string>& commands);
void PART(Client& client, std::vector<std::string>& commands);
void MODE(Client& client, std::vector<std::string>& commands);
void INVITE(Client& client, std::vector<std::string>& commands);