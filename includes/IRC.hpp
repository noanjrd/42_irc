/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:25:15 by njard             #+#    #+#             */
/*   Updated: 2026/02/26 14:42:07 by njard            ###   ########.fr       */
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
#include "Channel.hpp"
#include "ClientConnection.hpp"

// SIGNALS

extern volatile sig_atomic_t g_running;
void handleSignal(int sig);

// ROLE

#define DEFAULT 0
#define OPERATORS 1

// SERVER

void processMessage(std::string message, Client &client);
void splitMessage(std::string commands, Client &client);
void pollLoop(Server &server);

// UTILS

bool 		isstrdigit(const std::string& str);
Channel* 	strChanneltoChannelType(Server& server, std::string& channelName);
std::vector<std::string> convertToVector(const std::string&);

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